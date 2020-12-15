#include <json-c/json.h>
#include <stdio.h>
#include <string.h>

#include "../hdr/network.h"

void write_neuron(Neuron *neuron, int index, int index_max, FILE *fp)
{
    int n = neuron->len_weight;

    char *str = calloc(256, sizeof(char));
    strcat(str, "\t\t\t\t{\n\t\t\t\t\t\"len_weight\" : %d,\n\t\t\t\t\t\"biais\"");
    strcat(str, " : %f,\n\t\t\t\t\t\"delta\" : %f,\n\t\t\t\t\t\"value\" : %f,\n");
    strcat(str, "\t\t\t\t\t\"activated\" : %f,\n\t\t\t\t\t\"weights\" : [\n");

    fprintf(fp, str, n, neuron->biais, neuron->delta,
            neuron->value, neuron->activated);

    free(str);

    for(int i = 0; i < n-1; i++)
        fprintf(fp, "\t\t\t\t\t\t%f,\n", neuron->weights[i]);

    fprintf(fp, "\t\t\t\t\t\t%f\n", neuron->weights[n-1]);

    if (index != index_max)
        fprintf(fp, "\t\t\t\t\t]\n\t\t\t\t},\n");
    else
        fprintf(fp, "\t\t\t\t\t]\n\t\t\t\t}\n\t\t\t]\n");
}

void write_layer(Layer *layer, int index, int index_max, FILE *fp)
{
    int n = layer->len_neurons;

    fprintf(fp, "\t\t{\n\t\t\t\"len_neurons\" : %d,\n\t\t\t\"neurons\" : [\n", n);

    for(int i = 0; i < n; i++)
        write_neuron(&layer->neurons[i], i, n-1, fp);

    if (index != index_max)
        fprintf(fp, "\t\t},\n");
    else
        fprintf(fp, "\t\t}\n\t]\n");
}

void write_network(Network *network, char *filename)
{
    int n = network->nbLayers;
    FILE *fp = fopen(filename, "w");

    if(!fp)
    {
        fprintf(stderr, "write_network() error: file open failed '%s'.\n",
                filename);
        return;
    }

    fprintf(fp, "{\"network\" : {\n\t\"nbLayers\" : %d,\n\t\"layers\" : [\n", n);

    for(int i = 0; i < n; i++)
        write_layer(&network->layers[i], i, n-1, fp);

    fprintf(fp, "}}");
    fclose(fp);
}

struct json_object *parse_network(char *filename)
{
    char *buffer = "";
    unsigned long length;
    FILE *fp = fopen(filename, "r");

    if(fp)
    {
        fseek(fp, 0, SEEK_END);
        length = ftell(fp);
        fseek(fp, 0, SEEK_SET);
        buffer = malloc(length + 1);
        if(buffer)
            if (fread(buffer, 1, length, fp) != length)
                printf("error parsing file!");
        fclose(fp);
    }

    if(buffer)
    {
        struct json_object *new_obj;
        new_obj = json_tokener_parse(buffer);
        struct json_object *network;
        json_object_object_get_ex(new_obj, "network", &network);
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
    struct json_object *biais;
    struct json_object *delta;

    json_object_object_get_ex(neuron_object, "weights", &weights);
    json_object_object_get_ex(neuron_object, "len_weight", &len_weight);
    json_object_object_get_ex(neuron_object, "value", &value);
    json_object_object_get_ex(neuron_object, "activated", &activated);
    json_object_object_get_ex(neuron_object, "biais", &biais);
    json_object_object_get_ex(neuron_object, "delta", &delta);

    int len = json_object_get_int(len_weight);

    neuron->len_weight = json_object_get_int(len_weight);
    neuron->biais = json_object_get_int(biais);
    neuron->value = json_object_get_double(value);
    neuron->activated = json_object_get_double(activated);
    neuron->delta = json_object_get_double(delta);
    if (len > 1)
        neuron->weights = calloc(len, sizeof(double));
    else
        neuron->weights = malloc(sizeof(double));

    for(int i = 0; i < len; i++)
        neuron->weights[i] = json_object_get_double(json_object_array_get_idx(weights, i));
}

void parse_layer_from_file(struct json_object *layer_object, Layer *layer)
{
    struct json_object *len_neurons;
    struct json_object *neurons;
    layer->NextLayer = NULL;
    layer->PreviousLayer = NULL;

    json_object_object_get_ex(layer_object, "len_neurons", &len_neurons);
    layer->len_neurons = json_object_get_int(len_neurons);

    layer->neurons = calloc(layer->len_neurons, sizeof(Neuron));

    json_object_object_get_ex(layer_object, "neurons", &neurons);

    for(int i = 0; i < json_object_get_int(len_neurons); i++)
        parse_neuron_from_file(json_object_array_get_idx(neurons, i),
                               &layer->neurons[i]);

}

void parse_network_from_file(char *filename, Network *network)
{
    struct json_object *network_object = parse_network(filename);
    struct json_object *layers;
    struct json_object *nbLayers;

    json_object_object_get_ex(network_object, "nbLayers", &nbLayers);
    json_object_object_get_ex(network_object, "layers", &layers);
    network->nbLayers = json_object_get_int(nbLayers);

    network->layers = calloc(network->nbLayers, sizeof(Layer));

    int nbLayers_val = json_object_get_int(nbLayers);

    for(int i = 0; i < nbLayers_val; i++)
    {
        struct json_object *layer_val;
        layer_val = json_object_array_get_idx(layers, i);
        parse_layer_from_file(layer_val, &network->layers[i]);
        if(i > 0)
        {
            network->layers[i].PreviousLayer = &network->layers[i-1];
            network->layers[i-1].NextLayer = &network->layers[i];
        }
    }

    network->input = network->layers;
    network->output = &network->layers[nbLayers_val - 1];
}

