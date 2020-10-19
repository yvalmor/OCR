#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <err.h>
#include "../hdr/network.h"

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
void freeNeuron(Neuron *neuron)
{
	free((*neuron).weights);
	free(neuron);
}

//return neuron initialised randomly
Neuron* rndNeuron(int len_weight)
{
	Neuron *neuron = malloc(sizeof(Neuron));

	double *weights = malloc(sizeof(double) * len_weight);

	if (neuron == NULL || weights == NULL)
		errx(1, "*neuron or *weights is NULL at rdmNeuron.\n");

	for (int i = 0; i < len_weight; i++)
		*(weights + i) = rdmDouble(-2.0, 2.0);
	
	(*neuron).biais = rdmDouble(-2.0, 2.0);
	(*neuron).weights = weights;
	(*neuron).len_weight = len_weight;
	return neuron;
}


//return a neuron with the wanted initialised value
Neuron* initNeuron(int len_weight, double *wtedWeights, int wtdBiais)
{
	
	Neuron *neuron = malloc(sizeof(double*) + sizeof(int) * 2);	

	double *weights = malloc(sizeof(double) * len_weight);

	if (neuron == NULL || weights == NULL)	
		errx(1, "*neuron or *weights is NULL at rdmNeuron.\n");

	(*neuron).biais = wtdBiais;
	(*neuron).weights = wtedWeights;
	(*neuron).len_weight = len_weight;
	return neuron;
}


//return a layer of size neurons linked to previous and next layer
Layer* create_layer(int size, Layer *prev, Layer *next)
{
	Layer *layer = malloc(sizeof(Neuron*) + sizeof(int) + sizeof(Layer*) * 2);

	Neuron *neuron = malloc(sizeof(Neuron));

	if (neuron == NULL || layer == NULL)	
		errx(1, "*neuron or *weights is NULL at rdmNeuron.\n");

	
	//if to check if not in input cuz input does not has weights etc
	if (prev != NULL)
	{
		//nber of weights in neuron == nber of neurons in previous layer
		for (int i = 0; i < size; i++)
			neuron[i] = rndNeuron((*prev).len_neurons); 
			//*(neuron + i) = rndNeuron((*prev).len_neurons); 
	}

	(*layer).neurons = neuron;
	(*layer).len_neurons = size;
	(*layer).PreviousLayer = prev;
	(*layer).NextLayer = next;
	return layer;
}


//the weights == coming to neurons (not leaving it)
void propagation(Layer *current)
{
	while ((*current).NextLayer != NULL)
	{
		//*(current) = *(current.NextLayer);
		printf("current layer's len : %d and adress is : %p", (*current).len_neurons, &current);
		
		for (; (*current).neurons; (*current).neurons++)
			sumNeuron(*(current -> neurons));

		current = current->NextLayer;
	}


}

void handleInput(double *input, Network net)
{
	printf("%ld", sizeof(input) + sizeof(net));
}	

//need to create a main.c lazy :c
int main()
{
	//:%s/foo/bar/gc
	srand((unsigned int) time (NULL));

	return 0;
}


