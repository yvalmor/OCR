#include <stdio.h>
#include "../hdr/network.h"
#include <json-c/json.h>

void write_neuron(Neuron *neuron, int index, int index_max, FILE *fp)
{
    int n = neuron->len_weight;

    fprintf(fp, " \"neuron%d\" : {\n\"len_weight\" : %d,\n\"biais\" : %d,\n\"value\" : %f,\n\"activated\" : %f,\n\"weights\" : [\n", 
            index, n, neuron->biais, neuron->value, neuron->activated);

    for(int i = 0; i < n-1; i++)
        fprintf(fp, " %f,\n", neuron->weights[i]);

    fprintf(fp, " %f\n", neuron->weights[n-1]);

    if (index != index_max)
        fprintf(fp, " ]\n}, ");
    else
        fprintf(fp, " ]\n]} ");
}

void write_layer(Layer *layer, int index, int index_max, FILE *fp)
{
    int n = layer->len_neurons;

    fprintf(fp, " \"layer%d\" : {\n\"len_neurons\" : %d,\n\"neurons\" : [\n", index, n);

    for(int i = 0; i < n-1; i++)
        write_neuron(&layer->neurons[i], i, n-1, fp);
    
    if (index != index_max)
        fprintf(fp, " ]\n}, ");
    else
        fprintf(fp, " ]\n} ");
}

void write_network(Network *network, char *filename)
{
    int n = network->nbLayers;
    FILE *fp = fopen(filename, "a");

    if(!fp)
    {
        fprintf(stderr, "write_network() error: file open failed '%s'.\n", filename);
        return;
    }

    fprintf(fp, "{\"network\" : {\n\"nbLayers\" : %d,\n\"layers\" : [\n", n);

    for(int i = 0; i < n; i++)
        write_layer(&network->layers[i], i, n-1, fp);

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
   Network *network = malloc(sizeof(network));
   network->nbLayers = 4;
   create_network(network, 4, 2, 2);

   write_network(network, "network.json");
}
