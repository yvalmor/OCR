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

/**
 * @authors Eliott Beguet
 * @param neuron, to add desired value
 * @param len_weight, number of weight in neuron
 * @param weight, weights to assign
 * @param biais, biais to assign
 */
void SetNeuron(Neuron *neuron, int l_w, double *weight, int biais)
{
    for (int i = 0; i < l_w; i ++)
        neuron->weights[i] = weight[i];

    neuron->biais = biais;
}

//return neuron initialised randomly
/**
 * @authors Eliott Beguet
 * @param neuron, neuron to apply modifications
 * @param len_weight, number of weight to create for this neuron
 */
void rndNeuron(Neuron *neuron, int len_weight)
{
    double *weights = calloc(len_weight, sizeof(double));

    if (neuron == NULL || weights == NULL)
        errx(1, "*neuron or *weights is NULL at rndNeuron.\n");

    for (int i = 0; i < len_weight; i++)
        *(weights + i) = rdmDouble(-1.5, 1.5);

    (*neuron).delta = 0;
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
void create_layer(Layer *layer, int size, Layer *prev, int poss_lenW)
{
    Neuron *neuron = calloc(size, sizeof(Neuron));

    if (neuron == NULL || layer == NULL)
        errx(1, "*neuron or *layer is NULL at create_layer.\n");

    int l = (prev == NULL) ? poss_lenW : prev->len_neurons;
    //if to check if not in input cuz input does not has weights etc
    //nber of weights in neuron == nber of neurons in previous layer

    
    for (int i = 0; i < size; i++)
    {
        rndNeuron(neuron + i, l);
        neuron[i].biais = rdmDouble(-1, 1);
    }

    (*layer).neurons = neuron;
    (*layer).len_neurons = size;
    (*layer).PreviousLayer = prev;
}


//len is the nber of layer to create (so not including the input)
/**
 * @authors Eliott Beguet
 * @param len, number of layer for this network (including input and output)
 * @param layer, pointer to the input layer
 * @param nbNeurons, number of neurons wanted for the hidden layers
 * @param outputNbneurons, number of neurons wanted for the ouptut layer
 * @return new Network fully operational
 */
void create_network(Network *net, int nbLayers, int nbNeurons, int inputNbNeurons, int outputNbneurons)
{
    int len = nbLayers;

    //allocate memory for the input
    Layer *inp = calloc(len, sizeof(Layer));
    create_layer(inp, inputNbNeurons, NULL, 0);

    Layer *currentLayer = inp;
    Layer *previousLayer = NULL;

    for (int i = 1; i < len - 1; i++)
    {
        previousLayer = currentLayer;
        currentLayer = inp + i;
        previousLayer->NextLayer = currentLayer;

        create_layer(currentLayer, nbNeurons, previousLayer, 0);
    }

    previousLayer = currentLayer;
    currentLayer = inp + len - 1;
    previousLayer->NextLayer = currentLayer;

    create_layer(currentLayer, outputNbneurons, previousLayer, 0);
    currentLayer->NextLayer = NULL;

    (*net).nbLayers = nbLayers;
    (*net).layers = inp;
    (*net).input = inp;
    (*net).output = currentLayer;

    for (int i = 0; i < inputNbNeurons; i++)
        net->input->neurons[i].biais = 0;
}

/**
 * @authors Eliott Beguet
 * @param network to apply the feed forward
 */
void feedForward(Network *net, int *value, int len)
{
    if (len != net->input->len_neurons)
        errx(1, "Different length for input of net and given values.");
    
    for (int i = 0; i < len; i++)
        net->input->neurons[i].activated = (double) value[i];

    propagation_layer((*net).layers + 1);
}

char get_answer(Network *net)
{
    int max = net->output->neurons[0].activated;
    int pos = 0;

    for (int i = 0; i < net->output->len_neurons; i++)
    {
        if (net->output->neurons[i].activated > max)
        {
            max = net->output->neurons[i].activated;
            pos = i;
        }
    }

    if (pos >= 0 && pos < 10) //number
        return '0' + (char) pos;

    else if (pos >= 10 && pos < 36) //caps
        return 'A' + (char) pos - 10;

    else if (pos >= 36 && pos < 63) //alpha
        return 'a' + (char) pos - 36;

    return '?';
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
        {
            double net = tmp->neurons[i].biais;
            
            for (int j = 0; j < tmp->neurons[i].len_weight; j++)
                net += tmp->neurons[i].weights[j] * tmp->PreviousLayer->neurons[j].activated;

            double out = sigmoid(net);

            tmp->neurons[i].value = net;
            tmp->neurons[i].activated = out;
        }
            //sumNeuron((*tmp).neurons + i, (*tmp).PreviousLayer->neurons + i,
              //  tmp->NextLayer == NULL);

        tmp = tmp->NextLayer;
    }
}

/**
 * @authors Eliott Beguet
 * @param neuron, neuron where we wanna update it value and activation
 * with the weighted sum
 * @param prevNeurons, previous neuron usefull to get the previous activation
 */
void sumNeuron(Neuron *neuron, Neuron *prevNeurons, int isOutput)
{
    double sum = neuron->biais;

    for (int i = 0; i < neuron->len_weight; i++)
        sum += (neuron->weights[i]) * (prevNeurons + i)->activated;

    double out = sigmoid(sum);

    (*neuron).value = sum;
    (*neuron).activated = out;
    if (!isOutput)
        (*neuron).delta = out * (1 - out) * sum;
}

//for backpropagation now
/**
 * @authors Eliott Beguet
 * @param ouptut, the value we got thanks to the feed forward
 * @param expected, the value we expected output to be
 * @return the cost of one output's neuron
 */
double mse(double expected, double output)
{
    return (expected - output) * (expected - output);
}

/**
 * on this case we assume and need len(output) = len(expected)
 * @authors Eliott Beguet
 * @param *output, the layer we need to calculate it cost
 * @param *expected, the array of expected value
 * @return the tocal cost of the output layer
 */
double ErrorTotal(Layer *output, double *expected)
{
    double total = 0;

    for (int i = 0; i < output->len_neurons; i++)
    {
        output->neurons[i].delta = expected[i] - output->neurons[i].activated;

        total += mse(expected[i], output->neurons[i].activated);
    }
    return total * 0.5;
}

/**
  @authors Eliott Beguet
  @param *n, network to apply backpropagation
  @param *expected, the expected output for the given input
  */
double backpropagation(Network *n, double *expected, double lR)
{
    // compute delta for each output neuron and return total error of net
    double error = ErrorTotal(n->output, expected);

   // now we update the weight of the outputLayer
    for (int i = 0; i < n->output->len_neurons; i++)
    {
        double delta_n = n->output->neurons[i].delta;

        for (int j = 0; j < n->output->neurons[i].len_weight; j++)
        {
            double out_actu = n->output->neurons[i].activated;
            double out_prev = n->output->PreviousLayer->neurons[j].activated;

            n->output->neurons[i].weights[j] += lR * delta_n * out_actu * out_prev;
        }
    }

    // now the same with the weights of the hidden layer

    for (int l = n->nbLayers - 2; l > 0; l--)
        delta_hidden(n->layers + l);
    
    for (int i = n->nbLayers - 2; i > 0; i--)
        update_weights_layer(n->layers + i, lR);

    return error;
}


/**
 * @authors Eliott Beguet
 * @param layer, layer to compute the delta for each neuron
 */
void delta_hidden(Layer *layer)
{
    int limit_next_layer = layer->NextLayer->len_neurons;

    for (int i = 0; i < layer->len_neurons; i++)
    {
        // delta for neuron[i]
        double delta_i = 0;

        // compute sum of error *
        // out(neuronNextLayer) * (1 - out(neuronNextLayer)) *
        // w_i le poids liant les 2 neurons

        for (int j = 0; j < limit_next_layer; j++)
        {
            double error_next = layer->NextLayer->neurons[j].delta;
            double d_out_next = layer->NextLayer->neurons[j].activated *
                (1 - layer->NextLayer->neurons[j].activated);
            double w_i = layer->NextLayer->neurons[j].weights[i];

            delta_i += error_next * d_out_next * w_i;
        }

        layer->neurons[i].delta = delta_i;
    }
}

/**
 * @authors Eliott Beguet
 * @param layer, layer to update its weight
 * @lR, learning rate
 */
void update_weights_layer(Layer *layer, double lR)
{
    for (int i = 0; i < layer->len_neurons; i++)
    {
        //on each neuron we will update his weights thx to his delta
        double delta_c = layer->neurons[i].delta;

        for(int j = 0; j < layer->neurons[i].len_weight; j++)
        {
            // i index of neuron is to find the prevNeurons connected with the
            // j weight

            // then compute new_w -= learningRate * (
            // delta_c * out(neuronPrevLayer.active) (1 - out) * out)
            double out = layer->PreviousLayer->neurons[j].activated;

            layer->neurons[i].weights[j] -= lR * delta_c * out * (1 - out) * out;
        }
    }
}

void trainNetwork(Network *net, double lRate, int epoch, double *expected)
{
    double err = 0;

    for (int i = 0; i < epoch; i++)
    {
        if (lRate > 1.1 && i % 100 == 0)
            lRate--;

        propagation_layer(net->layers + 1);
        double e = backpropagation(net, expected, lRate);
        err += e;
    }

    err *= (1.0 / epoch);
    printf("Error: %f\n", err);
}


/**
 * @authors Eliott Beguet
 * @param ?, whatever struct to be free'd
 */
void freeNeuron(Neuron *n)
{
    free(n->weights);
}

/**
 * @see freeNeuron
 */
void freeLayer(Layer *l)
{
    int len = l->len_neurons;

    for (int i = len - 1; i >= 0; i--)
        freeNeuron((*l).neurons + i);
}

/**
 * @see freeNeuron
 */
void freeNetwork(Network *n)
{
    int len = n->nbLayers;

    for (int i = len - 1; i >= 0; i--)
        freeLayer((*n).layers + i);
}

// ALL FCTIONS BELOW ARE FOR TEST ONLY
/**
 * @authors Eliott Beguet
 * @param ?, whatever we wanna print to see what we have
 */
void printNeuron(Neuron *neuron, int i)
{
    printf("Neurons at pos i: %d\n.", i);
    printf("biais: %f\n", neuron->biais);
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
        printNeuron((*layer).neurons + i, i);

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
/*
    Network *NET = malloc(sizeof(Network));
    create_network(NET, 3, 2, 2, 2);
    
    NET->input->neurons[0].activated = 0.05;
    NET->input->neurons[1].activated = 0.10;

    NET->layers[1].neurons[0].weights[0] = 0.15;
    NET->layers[1].neurons[0].weights[1] = 0.20;
    NET->layers[1].neurons[0].biais = 0.35;

    NET->layers[1].neurons[1].weights[0] = 0.25;
    NET->layers[1].neurons[1].weights[1] = 0.30;
    NET->layers[1].neurons[1].biais = 0.35;

    NET->output->neurons[0].weights[0] = 0.40;
    NET->output->neurons[0].weights[1] = 0.45;
    NET->output->neurons[0].biais = 0.60;

    NET->output->neurons[1].weights[0] = 0.50;
    NET->output->neurons[1].weights[1] = 0.55;
    NET->output->neurons[1].biais = 0.60;

    double exxx[2] = {0.01, 0.99};
    double err = 0;

    for (int i = 0; i < 10000; i++)
    {
        propagation_layer(NET->layers + 1);
        err += backpropagation(NET, exxx, 0.5);
    }
    
    printf("Error: %f\n", err / 10000);
    printf("out1 = %f | out2 = %f\n", NET->output->neurons[0].activated, NET->output->neurons[1].activated);
*/



    int INPUT [4][2] = { {0, 0}, {1, 1}, {0, 1}, {1, 0} };
    double EXPECTED [4][1] = { {0}, {1}, {1}, {1} }; 

    //:%s/foo/bar/gc
    srand((unsigned int) time (NULL));

    //allocate memory for whole Network
    Network *net = malloc(sizeof(Network));
    
    create_network(net, 4, 4, 2, 1);

    double er = 0;
    double l = 1;
    int limit = 400;
    for (int i = 0; i < limit; i++)
    {
        if (i == 10)
            l = 0.1;

        int pos = rand() % 4;
        printf("[%d] In: {%d, %d} |-> ", i, INPUT [pos][0], INPUT [pos][1]);
        
        double e = 0;
        for (int p = 0; p < 80; p++)
        {
            feedForward(net, INPUT[pos], 2);
            e = backpropagation(net, EXPECTED[pos], l); 
        }
        er += e;

        //printf("%f and %f\n", net->output->neurons[0].activated, net->output->neurons[1].activated);
        printf("%f\n", net->output->neurons[0].activated);
        printf("ERROR: %f\n=================================\n", e);
    }
    
    er *= (1.0 / limit);
    printf("AND ERROR = %f\n", er);
    printf("FNISHED\n");

    freeNetwork(net);
    free(net);

    return 0;
}
