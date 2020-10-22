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
Neuron *rndNeuron(int len_weight)
{
	Neuron *neuron = malloc(sizeof(Neuron));

	double *weights = malloc(sizeof(double) * len_weight);

	if (neuron == NULL || weights == NULL)
		errx(1, "*neuron or *weights is NULL at rndNeuron.\n");

	for (int i = 0; i < len_weight; i++)
		*(weights + i) = rdmDouble(-2.0, 2.0);
	
	(*neuron).biais = rdmDouble(-2.0, 2.0);
	(*neuron).weights = weights;
	(*neuron).len_weight = len_weight;
	return neuron;
}


//return a neuron with the wanted initialised value
Neuron *initNeuron(int len_weight, double *wtedWeights, int wtdBiais, double wtedValue, double wtedA)
{
	
	Neuron *neuron = malloc(sizeof(Neuron));

	double *weights = malloc(sizeof(double) * len_weight);

	if (len_weight != 0 && (neuron == NULL || weights == NULL))	
		errx(1, "*neuron or *weights is NULL at initNeuron.\n");

	(*neuron).biais = wtdBiais;
	(*neuron).weights = wtedWeights;
	(*neuron).len_weight = len_weight;
	(*neuron).value = wtedValue;
	(*neuron).activated = wtedA;
	return neuron;
}


//return a layer of size neurons linked to previous and next layer
Layer *create_layer(int size, Layer *prev, Layer *next)
{
	Layer *layer = malloc(sizeof(Layer));
	
	Neuron *neuron = malloc(sizeof(Neuron));

	if (neuron == NULL || layer == NULL)	
		errx(1, "*neuron or *layer is NULL at create_layer.\n");

	
	//if to check if not in input cuz input does not has weights etc
	if (prev != NULL)
	{
		//nber of weights in neuron == nber of neurons in previous layer
		for (int i = 0; i < size; i++)
			(neuron + i) = rndNeuron((*prev).len_neurons);
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
	Layer *temp = current;

	while (temp->NextLayer != NULL)
	{
		printf("current layer's len : %d and adress is : %p", (*temp).len_neurons, &temp);
		
		for (int i = 0; i < current->len_neurons; i++)
			sumNeuron( &(temp->neurons[i]), current->PreviousLayer->neurons);

		temp = temp->NextLayer;
	}
}


void sumNeuron(Neuron *neuron, Neuron *prevNeurons)
{
	double sum = neuron->biais;

	for (int i = 0; i < neuron->len_weight; i++)
		sum += *((neuron + i)->weights) * (prevNeurons + i)->activated;

	(*neuron).value = sum;
	(*neuron).activated = sigmoid(sum);
}

//*input needed to integrate in *net (in layers0 which is first hidden layer)
void handleInput(double *input, int len_input,  Network *net)
{
	Neuron *inputNeurons = malloc(sizeof(Neuron) * len_input);
	Neuron *tmp = inputNeurons;
	double t[1] = {1};

	for (int i = 0; i < len_input; i++)
		(tmp + i) = initNeuron(1 , t, 0, input[i], sigmoid(input[i]));

	sumNeuron(net->layers->neurons, inputNeurons);
}	

//need to create a main.c lazy :c
int main()
{
	//:%s/foo/bar/gc
	srand((unsigned int) time (NULL));

	return 0;
}


