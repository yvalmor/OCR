#ifndef NETWORK_H
#define NETWORK_H

#include <time.h>
#include <stdlib.h>
#include <stdio.h>


typedef struct Neuron
{
    double *weights;                //those arriving
    int len_weight;                 //nber of weight
    int biais;                      //corresponging bias

    double *old_weights;
    double error;                   //error stored
    double value;                   //weighted sum
    double activated;               //sigmoid value
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
    Layer *input;
    Layer *output;
    int nbLayers;                   //nbers of layers
} Network;


void rndNeuron(Neuron *neuron, int len_weight);
void initNeuron(Neuron *neuron, int len_weight, double *weight, int biais, double wtedValue, double wtedA);
double sigmoid(double x);
double sigmoid_prime(double x);
double rdmDouble(double min, double max);

void create_layer(Layer *layer, int size, Layer *prev, int poss_lenW);
void feedForward(Network *net, int *input_to_add, int len_value);
void propagation_layer(Layer *layer);
void create_network(Network *net, int nbLayer,int neuronsPerLayer, int inputNbNeurons, int outputNbneurons);

double backpropagation(Network *net, double *expected, double learningRate);
void sumNeuron(Neuron *neuron, Neuron *neededForA);
void trainNetwork(Network *n, double lrate, int epoch, double *expected);

double mse(double expctd, double output);
double ErrorOutput(Layer *layer, double *expected);
double totalErrorOutput(Network *net, double *expected);
void updateWeightsNeuron(Neuron *n, Neuron *previousN, double LearningRate, double desired);
void updateLayer(Layer *l, double LearningRate);

double errorHiddenLayer(Neuron *neuronCalculateErr, Layer *toSearchWeight, int posW);
double totalErrorHidden(Layer *toCalculateError);

void delta_network(Network *network);
void update_network(Network *network)

void freeNetwork(Network *net);
void freeLayer(Layer *l);

#endif
