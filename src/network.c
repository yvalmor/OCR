#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <err.h>
#include "../hdr/network.h"

/**
 * @authors Eliott Beguet
 * @param x, value to get sigmoid on
 */
double sigmoid(double x)
{
    return 1 / (1 + exp(-x));
}

double sigmoid_prime(double x)
{
    return x * (1.0 - x);
}

double rdmDouble(double min, double max)
{
    return (max - min) * (double) rand() / (double) (RAND_MAX);
}


//NN functions

//return neuron initialised randomly
/**
 * @authors Eliott Beguet
 * @param neuron, neuron to apply modifications
 * @param len_weight, number of weight to create for this neuron
 */
void rndNeuron(Neuron *neuron, int len_weight)
{
    double *weights = malloc(sizeof(double) * len_weight);

    if (neuron == NULL || weights == NULL)
        errx(1, "*neuron or *weights is NULL at rndNeuron.\n");

    for (int i = 0; i < len_weight; i++)
        *(weights + i) = rdmDouble(-1.5, 1.5);
    
    (*neuron).error = 0;
    (*neuron).biais = rdmDouble(-1.5, 1.5);
    (*neuron).weights = weights;
    (*neuron).len_weight = len_weight;
}


//return a layer of size neurons linked to previous and next layer
/**
 * @authors Eliott Beguet
 * @param layer, layer to apply modification
 * @param size, number of neurons for this layer
 * @param prev, pointer for the previous layer
 * @param next, pointer for the next layer
 * @param poss_lenW, useless param which will be removed soon
 */
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


//len is the nber of layer to create (so not including the input)
/**
 * @authors Eliott Beguet
 * @param len, number of layer for this network (DO NOT count the input layer in)
 * @param layer, pointer to the input layer
 * @param nbNeurons, number of neurons wanted for the hidden layers
 * @param outputNbneurons, number of neurons wanted for the ouptut layer
 * @return new Network fully operational
 */
Network *create_network(int len, Layer *layer, int nbNeurons, int outputNbneurons)
{
    Network *net = malloc(sizeof(Network));
    Layer *allLayers = malloc(sizeof(Layer) * (1 +len));

    allLayers = layer;
    
    for (int i = 1; i < len; i++)
    {
        Layer *prev = allLayers + i - 1;
        Layer *next = (i < len - 1) ? allLayers + i + 1 : NULL;
        int number = (i < len - 1) ? nbNeurons : outputNbneurons;

        create_layer(allLayers + i, number, prev, next, 0);
    }

    Layer *i = allLayers;
    i->NextLayer = i + 1;

    (*net).layers = allLayers;
    (*net).nbLayers = len + 1;

    return net;
}

/**
 * @authors Eliott Beguet
 * @param network to apply the feed forward
 */
void feedForward(Network *net)
{
    propagation_layer((*net).layers + 1);
}

/**
 * Be carefull not to launch it on input layer.
 * @authors Eliott Beguet
 * @param current, layer where we want the propagation to starts
 */
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

/**
 * @authors Eliott Beguet
 * @param neuron, neuron where we wanna update it value and activation
 * with the weighted sum
 * @param prevNeurons, previous neuron usefull to get the previous activation
 */
void sumNeuron(Neuron *neuron, Neuron *prevNeurons)
{
    double sum = neuron->biais;

    for (int i = 0; i < neuron->len_weight; i++)
        sum += (neuron->weights[i]) * (prevNeurons + i)->activated;

    (*neuron).value = sum;
    (*neuron).activated = sigmoid(sum);
}

//for backpropagation now
/**
 * @authors Eliott Beguet
 * @param a, b, value to return the square of.
 */
double sqr(double a, double b)
{
    return a * b;
}

/**
 * @authors Eliott Beguet
 * @param ouptut, the value we got thanks to the feed forward
 * @param expected, the value we expected output to be
 * @return the cost of one output's neuron
 */
double mse(double expected, double output)
{
    return sqr(expected - output, expected - output);
}

/**
 * @authors Eliott Beguet
 * @param *output, the layer we need to calculate it cost
 * @param *expected, the array of expected value
 * @return the tocal cost of the output layer
 */
double ErrorOutput(Layer *output, double *expected)
{
    double total = 0;
    for (int i = 0; i < output->len_neurons; i++)
    {
        output->neurons[i].error = output->neurons[i].activated - expected[i];
        total += mse(expected[i], output->neurons[i].activated);
    }
    return total / 2;
}

/**
 * @authors Eliott Beguet
 * @param net, network to calculate the cost
 * @return double error
 */
double totalErrorOutput(Network *net, double *expected)
{
    int pos = net->nbLayers - 1;
    return ErrorOutput((*net).layers + pos, expected);
}

/**
 * @authors Eliott Beguet
 * @param *n, neuron to calculate the error
 * @param *lWeight, layer to pick corresponding weight
 * @param posi, position of *n in layer to pick the right weight in nextLayer
 * @return the error of this neuron and store it
 */
double errorHiddenLayer(Neuron *n, Layer *lWeight, int posi)
{
     double res = 0;
     posi += 0;
    
     for (int i = 0; i < lWeight->len_neurons; i++)
        res += (lWeight->neurons[i].error * lWeight->neurons[i].weights[posi]);

    //to check
    double err = res * sigmoid_prime(n->value);
    //end check
    return err;
}

/**
 * @authors Eliott Beguet
 * @param *l, layer to calculate error of neurons in
 ** @see errorHiddenLayer
 */
double totalErrorHidden(Layer *l)
{
    double err = 0;

    for (int i = 0; i < l->len_neurons; i++)
        err += errorHiddenLayer((*l).neurons + i, l->NextLayer, i);

    return err;
}

/**
  @authors Eliott Beguet
  @param *n, network to apply backpropagation
  @param *expected, the expected output for the given input
  */
double backpropagation(Network *n, double *expected)
{
    double error = 0;

    for (int i = n->nbLayers - 1; i > 0; i--)
    {
        if (i == n->nbLayers - 1)
        {
            error += totalErrorOutput(n, expected);
        }

        else
        {
            error += totalErrorHidden(n->layers + i);
        }
        //modify weight, bias with 2fctions

    }

    return error;
}

void trainNetwork(Network *net, double lRate, int epoch, double *expected)
{
    lRate++;
    double err = 0;
    
    for (int i = 0; i < epoch; i++)
    {
        propagation(net);
        err += backpropagation(net, expected);
    }

    err *= (1.0 / epoch);
    printf("Error: %f\n", err);
}

 
/*
double deltaw = l_rate * actu->err[actun] * done->out[donen];
                actu->w[i] += deltaw + 0.1 * actu->previous_dw[i];
                actu->previous_dw[i] = deltaw
*/
void updateWeightsNeuron(Neuron *neuron, Neuron *prev, double lR, double desired)
{
    double deltaW = prev->activated *sigmoid_prime(neuron->value) * 2 * (neuron->activated - desired);
    double deltaB = sigmoid_prime(neuron->value) * 2 * (neuron->activated - desired);

    for (int i = 0; i < neuron->len_weight; i++)
       neuron->weights[i] = -(lR * deltaW) + (neuron->weights[i]); 

    (*neuron).biais = neuron->biais - (lR * deltaB);
}

void updateLayer(Layer *layer, double lR)
{
    for (int i = 0; i < layer->len_neurons; i++)
    {
        //change desired not 1.2
        updateWeightsNeuron((*layer).neurons + i, (*layer).PreviousLayer->neurons + i, lR, 1.2);
    }
}

/**
 * @authors Eliott Beguet
 * @param ?, whatever struct to be free'd
 */
void freeNeuron(Neuron *n)
{
    free(n->weights);
    free(n);
}

/**
 * @see freeNeuron
 */
void freeLayer(Layer *l)
{
    for (int i = 0; i < l->len_neurons; i++)
        freeNeuron((*l).neurons + i);

    //free(l->PreviousLayer);
    //free(l->NextLayer);
    free(l);
}

/**
 * @see freeNeuron
 */
void freeNetwork(Network *n)
{
    for (int i = 0; i < n->nbLayers; i++)
        freeLayer((*n).layers + i);

    //free(n->layers);
    free(n);
}




// ALL FCTIONS BELOW ARE FOR TEST ONLY
/**
 * @authors Eliott Beguet
 * @param ?, whatever we wanna print to see what we have
 */
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

/**
 * @see printNeuron
 */
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


/**
 * @see printNeuron
 */
void testNET(Network *n)
{
    Layer *l = n->layers;
    for (int i = 0; i < n->nbLayers; i++)
    {
        printf("n->layers[%d]: %p\n", i, n->layers + i);
        printf("| layer[%d]->next: %p\n", i, l->NextLayer);
        printf("| layer[%d]->prev: %p\n\n", i, l->PreviousLayer);

        l = l->NextLayer;
    }
}


//need to create a main.c lazy :c
int main()
{
    //:%s/foo/bar/gc
    srand((unsigned int) time (NULL));

    Layer *input = malloc(sizeof(Layer));
    create_layer(input, 2, NULL, NULL, 0);

    Neuron *a = input->neurons;
    Neuron *b = a + 1;
    a->activated = 0;
    b->activated = 1;
    
    Network *net = create_network(3, input, 3, 2);
    feedForward(net);

    free(net);
    free(input);
    //freeNetwork(net); 
    return 0;
} 
