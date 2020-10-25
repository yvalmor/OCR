#ifndef NETWORK_H
#define NETWORK_H

#include <time.h>
#include <stdlib.h>
#include <stdio.h>


typedef struct Neuron
{
    double *weights;                //those arriving
    int len_weight;
    int biais;

    double value;
    double activated;
    double *delta_weight;
    int len_delta_weight;
} Neuron;


typedef struct Layer 
{
    Neuron *neurons;                //list of neurons
    int len_neurons;                //size for the list
    struct Layer *PreviousLayer;    //pointer to the previous layer
    struct Layer *NextLayer;        //pointer to the next layer
} Layer;


typedef struct Network
{
    Layer *layers;                  //list of all layers
    int nbLayers;
} Network;



const double training_data[4][2] = 
{
    {0, 0},
    {0, 1},
    {1, 0},
    {1, 1}
};

const double expected_res[4][1] = { {0}, {1}, {1}, {0}};

void rndNeuron(Neuron *neuron, int len_weight);
void initNeuron(Neuron *neuron, int len_weight, double *weight, int biais, double wtedValue, double wtedA);
double sigmoid(double x);
double rdmDouble(double min, double max);

void create_layer(Layer *layer, int size, Layer *prev, Layer *Next, int poss_lenW);
void propagation(Network *net);
void propagation_layer(Layer *layer);
Network *create_network(int nbLayers, Layer *input, int neuronsPerLayer, int outputNbneurons);

void backpropagation(Network *net, double *expected);
void sumNeuron(Neuron *neuron, Neuron *neededForA);

double sqr(double a, double b);
double mse(double expctd, double output);
double totalErrorOutput(Layer *layer, double *expected);
double totalError(Network *net, double *expected);
void updateWeightsNeuron(Neuron *n, double LearningRate);
void updateLayer(Layer *l, double LearningRate);

void freeNetwork(Network *net);
void freeLayer(Layer *l);

#endif
