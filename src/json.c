#include <stdio.h>
#include "../hdr/network.h"
#include <json-c/json.h>

void write_neuron(Neuron *neuron, int index, int index_max, FILE *fp)
{
    int n = neuron->len_weight;

    fprintf(fp, " \"neuron%d\" : {\n\"len_weight\" : %d,\n\"biais\" : %d,\n\"value\" : %f,\n\"activated\" : %f,\n\"error\" : %f,\n\"weights\" : [\n", 
            index, n, neuron->biais, neuron->value, neuron->activated, neuron->error);

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

    for(int i = 0; i < n; i++)
        write_neuron(&layer->neurons[i], i, n-1, fp);

    if (index != index_max)
        fprintf(fp, " \n}, ");
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

struct json_object *parse_network(char *filename)
{
    char *buffer = 0;
    long length;
    FILE *fp = fopen(filename, "r");

    if(fp)
    {
        fseek(fp, 0, SEEK_END);
        length = ftell(fp);
        fseek(fp, 0, SEEK_SET);
        buffer = malloc(length + 1);
        if(buffer)
            fread(buffer, 1, length, fp);
    }

    if(buffer)
    {
        struct json_object *network = json_tokener_parse(buffer);
        return network;
    }
    printf("Couldn't read %s", filename);
    return NULL;
}

void parse_neuron_from_file(struct json_object *neuron_object, Neuron *neuron)
{
    struct json_object *weights;
    struct json_object *len_weight;
    struct json_object *value;
    struct json_object *activated;
    struct json_object *error;
    struct json_object *biais;

    json_object_object_get_ex(neuron_object, "weights", &weights);
    json_object_object_get_ex(neuron_object, "len_weight", &len_weight);
    json_object_object_get_ex(neuron_object, "value", &value);
    json_object_object_get_ex(neuron_object, "activated", &activated);
    json_object_object_get_ex(neuron_object, "error", &error);
    json_object_object_get_ex(neuron_object, "biais", &biais);

    neuron->len_weight = json_object_get_int(len_weight); 
    neuron->biais = json_object_get_int(biais);
    neuron->error = json_object_get_double(error);
    neuron->value = json_object_get_double(value);
    neuron->activated = json_object_get_double(activated);
    neuron->weights = calloc(neuron->len_weight, sizeof(double));

    for(int i = 0; i < neuron->len_weight; i++)
        neuron->weights[i] = json_object_get_double(json_object_array_get_idx(weights, i));
}

void parse_layer_from_file(struct json_object *layer_object, Layer *layer)
{
    struct json_object *len_neurons;
    struct json_object *neurons;
    layer->NextLayer = NULL;
    layer->PreviousLayer = NULL;
    layer->neurons = calloc(layer->len_neurons, sizeof(Neuron));

    json_object_object_get_ex(layer_object, "len_neurons", &len_neurons);
    json_object_object_get_ex(layer_object, "neurons", &neurons);

    for(int i = 0; i < json_object_get_int(len_neurons); i++)
        parse_neuron_from_file(json_object_array_get_idx(neurons, i), &layer->neurons[i]);

}

Network *parse_network_from_file(char *filename)
{
    Network *network = malloc(sizeof(Network));
    struct json_object *network_object = parse_network(filename);
    struct json_object *layers;
    struct json_object *nbLayers;

    json_object_object_get_ex(network_object, "nbLayers", &nbLayers);
    json_object_object_get_ex(network_object, "layers", &layers);
    network->nbLayers = json_object_get_int(nbLayers);

    network->layers = calloc(network->nbLayers, sizeof(Layer));
    for(int i = 0; i < json_object_get_int(nbLayers); i++)
    {
        parse_layer_from_file(json_object_array_get_idx(layers, i), &network->layers[i]);
        if(i > 0)
        {
            network->layers[i].PreviousLayer = &network->layers[i-1];
            network->layers[i-1].NextLayer = &network->layers[i];
        }
    }

    return network;
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
   create_network(network, 4, 4, 2, 2);
   write_network(network, "network.json");
   Network *network2 = parse_network_from_file("network.json");
   write_network(network2, "network2.json");
}
