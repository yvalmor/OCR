#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <err.h>
#include "network.h"

//maths functions
double sigmoid(double x)
{
    return 1 / (1 + exp(-x));
}

double rdmDouble(double min, double max)
{
    return (max - min) * (double) rand() / (double) (RAND_MAX);
}


//NN functions

//return neuron initialised randomly
void rndNeuron(Neuron *neuron, int len_weight)
{
    double *weights = malloc(sizeof(double) * len_weight);

    if (neuron == NULL || weights == NULL)
        errx(1, "*neuron or *weights is NULL at rndNeuron.\n");

    for (int i = 0; i < len_weight; i++)
        *(weights + i) = rdmDouble(-1.5, 1.5);
    
    (*neuron).biais = rdmDouble(-1.5, 1.5);
    (*neuron).weights = weights;
    (*neuron).len_weight = len_weight;
}


//return a neuron with the wanted initialised value
void initNeuron(Neuron *neuron, int len_weight, double *wtedWeights, int wtdBiais, double wtedValue, double wtedA)
{
    double *weights = malloc(sizeof(double) * len_weight);

    if (len_weight != 0 && (neuron == NULL || weights == NULL))    
        errx(1, "*neuron or *weights is NULL at initNeuron.\n");

    (*neuron).biais = wtdBiais;
    (*neuron).weights = wtedWeights;
    (*neuron).len_weight = len_weight;
    (*neuron).value = wtedValue;
    (*neuron).activated = wtedA;
}


//return a layer of size neurons linked to previous and next layer
void create_layer(Layer *layer, int size, Layer *prev, Layer *next, int poss_lenW)
{
    Neuron *neuron = malloc(sizeof(Neuron) * size);

    if (neuron == NULL || layer == NULL)    
        errx(1, "*neuron or *layer is NULL at create_layer.\n");

    int l = (prev == NULL) ? poss_lenW : prev->len_neurons;    
    //if to check if not in input cuz input does not has weights etc

    //nber of weights in neuron == nber of neurons in previous layer
    for (int i = 0; i < size; i++)
        rndNeuron(neuron + i, l);

    (*layer).neurons = neuron;
    (*layer).len_neurons = size;
    (*layer).PreviousLayer = prev;
    (*layer).NextLayer = next;
}



Network *create_network(int len, Layer *layer, int nbNeurons, int outputNbneurons)
{
    Network *net = malloc(sizeof(Network));

    Layer *next = layer->NextLayer;
    Layer *prev = layer;
    
    Layer *temp;

    for (int i = 0; i < len - 2; i++)
    {
        temp = malloc(sizeof(Layer));
        create_layer(temp, nbNeurons, prev, next, 0);        

        temp->PreviousLayer = prev;
        temp->NextLayer = next;

        next = temp->NextLayer;
        prev = temp;
    }

    Layer *output = malloc(sizeof(Layer));
    create_layer(output, outputNbneurons, prev, next, 0);

    //output to link, link layer to next and in for link +=also prev

    (*net).layers = layer;
    (*net).nbLayers = len;

    return net;
}

void link2layers(Layer *head, Layer *newHead, int sizeNewHead)
{
    head->NextLayer = newHead;
    create_layer(newHead, sizeNewHead, head, NULL, 0);
}

void feedForward(Network *net)
{
    propagation_layer((*net).layers);
}

//the weights == coming to neurons (not leaving it)
//need to use it on first hidden layer (not input one)
void propagation_layer(Layer *current)
{
    Layer *tmp = current;

    while (tmp != NULL)
    {
        for (int i = 0; i < tmp->len_neurons; i++)
            sumNeuron((*tmp).neurons + i, (*tmp).PreviousLayer->neurons + i);

        tmp = tmp->NextLayer;
    }
}


void sumNeuron(Neuron *neuron, Neuron *prevNeurons)
{
    double sum = neuron->biais;

    for (int i = 0; i < neuron->len_weight; i++)
        sum += (neuron->weights[i]) * (prevNeurons + i)->activated;

    (*neuron).value = sum;
    (*neuron).activated = sigmoid(sum);
}

//for backpropagation now
// cost function
double sqr(double a, double b)
{
    return a * b;
}

double cost(double expected, double output)
{
    return sqr(output - expected, output - expected);
}

double totalCostO(Layer *output, double *expected)
{
    double total = 0;
    for (int i = 0; i < output->len_neurons; i++)
        total += cost(expected[i], output->neurons[i].activated);

    return total;
}


void printNeuron(Neuron *neuron)
{
    printf("biais: %d\n", neuron->biais);
    printf("value: %f\n", neuron->value);
    printf("activated: %f\n", neuron->activated);
    printf("weights: \n");

    for (int i = 0; i < neuron->len_weight; i++)
        printf("| %f\n", neuron->weights[i]);

    printf("\n");
}

void printLayer(Layer *layer, int rec)
{
    printf("\nbegining print of neuron at: %p\n", &layer);

    for (int i = 0; i < layer->len_neurons; i++)
        printNeuron((*layer).neurons + i);

    printf("=================================\n");

    if (rec)
    {
        if (layer->NextLayer != NULL)
        {
            printf("NextLayer: ");
            printLayer(layer->NextLayer, 0);
        }
        if (layer->PreviousLayer != NULL)
        {
            printf("PreviousLayer: ");
            printLayer(layer->PreviousLayer, 0);
        }
    }
}

//need to create a main.c lazy :c
int main()
{
    //:%s/foo/bar/gc
    srand((unsigned int) time (NULL));

    Layer *input = malloc(sizeof(Layer));
    //Layer *hidden = malloc(sizeof(Layer));
    //Layer *output = malloc(sizeof(Layer));

    create_layer(input, 2, NULL, NULL, 0);
    //create_layer(hidden, 4, input, output, 0);
    //create_layer(output, 2, hidden, NULL, 0);

    /*printLayer(output, 0);
    propagation_layer(hidden);
    printf("Done.\n");
    printLayer(output, 0);*/



    Network *net = create_network(3, input, 4, 2);
    feedForward(net);

    free(net);
    free(input);
    //free(hidden);
    //free(output);
    return 0;
} 
