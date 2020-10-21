#ifndef NETWORK_H
#define NETWORK_H

#include <time.h>
#include <stdlib.h>
#include <stdio.h>


typedef struct Neuron
{
	double *weights; //those arriving
	int len_weight;
	int biais;

	double value;
	double activated;
//	double *delta_weight;
//	int len_delta_weight; need to see if it can be usefull for backp
} Neuron;


typedef struct Layer 
{
	Neuron *neurons;	 	//list of neurons
	int len_neurons; 		 //size for the list
	struct Layer *PreviousLayer; 	 //pointer to the previous layer
	struct Layer *NextLayer;	 //pointer to the next layer
} Layer;


typedef struct Network
{
	Layer *layers; // /!\ first hidden layer, input handled before
	int nbLayers;
	char *Path;
} Network;



const double training_data[4][2] = {
		{0, 0},
		{0, 1},
		{1, 0},
		{1, 1}
};

const double expected_res[4][1] = { {0}, {1}, {1}, {0}};

Neuron* rndNeuron(int len_weight);
Neuron* initNeuron(int len_weight, double *weight, int biais, double wtedValue, double wtedA);
double sigmoid(double x);
double rdmDouble(double min, double max);

Layer* create_layer(int size, Layer *prev, Layer *Next);
void propagation(Layer *current);
void backpropagation();
void freeNeuron(Neuron *neuron);
void freeLayer(Layer *layer);
void freeNetwork(Network *network);
void sumNeuron(Neuron *neuron, Neuron *neededForA);
void handleInput(double *input,int len_input, Network *net);

#endif
