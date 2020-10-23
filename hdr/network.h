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
	int sizePath;
} Network;



const double training_data[4][2] = {
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

void create_network(Network *net, int n, char *path, int sizePath);
void create_layer(Layer *layer, int size, Layer *prev, Layer *Next, int poss_lenW);
void propagation(Network *net);
void propagation_layer(Layer *layer);
void propagate_layer(Layer *layer);

void backpropagation();
void sumNeuron(Neuron *neuron, Neuron *neededForA);
void handleInput(double *input,int len_input, Network *net);

double sqr(double a, double b);
double cost(double expctd, double output);
double totalCostO(Layer *layer, double *expected);


#endif
