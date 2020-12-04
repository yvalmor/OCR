#include <stdio.h>
#include "network.h"
#include <json-c/json.h>

void write_neuron(Neuron *neuron, int index, FILE *fp)
{
    int n = neuron->len_weight;

    fprintf(fp, " \"neuron%d\" : {\n\"len_weight\" : %d,\n\"biais\" : %d,\n\"value\" : %f,\n\"activated\" : %f,\n\"weights\" : [\n", 
            index, n, neuron->biais, neuron->value, neuron->activated);

    for(int i = 0; i < n; i++)
        fprintf(fp, " %f,\n", weights[i]);

    fprintf(fp, " ]\n}");
}

void write_layer(Layer *layer, int index, FILE *fp)
{
    int n = layer->len_neurons;

    fprintf(fp, " \"layer%d\" : {\n\"len_neurons\" : %d,\n\"neurons\" : [\n", index, n);

    for(int i = 0; i < n; i++)
        write_neuron(&layer->neurons[i], i, fp);

    fprintf(fp, " ]\n}");
}

void write_network(Network *network, char *filename)
{
    int n = newtork->nbLayers;
    FILE *fp = fopen(filename, "a");

    if(!fp)
        fprintf(stderr, "write_network() error: file open failed '%s'.\n", fname);
    return;

    fprintf(fp, "{\"network\" : {\n\"nbLayers\" : %d,\n\"layers\" : [\n", n);

    for(int i = 0; i < n; i++)
        write_layer(&network->layers[i], i, fp);

    fprintf(fp, " ]\n}");
    fclose(fp);
}
/*
Network *parse_network(char *filename)
{
    json_tokener *tok = json_tokener_new();

    FILE *fp = fopen(filename, "r");

    if(fp == NULL)
    {
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }

    json_object *jobj = NULL;
    const char *mystring = NULL;
    int stringlen = 0;

    enum json_tokener_error jerr;

    do{
        mystring = 
    }
}*/

int main()
{
    
}
