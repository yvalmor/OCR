#ifndef JSON_H
#define JSON_H

#include <stdio.h>


/**
 * Writes the neuron in argument in the opened file "fp", its index is also in
 * argument as well as the size of the neuron array
 *
 * @author Souleymane Sentici
 */
void write_neuron(Neuron *neuron, int index, int index_max, FILE *fp);


/**
 * Writes the layer in argument in the opened file "fp", its index is also in
 * argument as well as the size of the layer array
 *
 * @author Souleymane Sentici
 */
void write_layer(Layer *layer, int index, int index_max, FILE *fp);


/**
 * Writes the network in argument in the "filename" json file,
 * which is created if needed
 *
 * @author Souleymane Sentici
 */
void write_network(Network *network, char *filename);


/**
 * Generates a json_object structure from the content of the "filename" json
 * file
 *
 * @author Souleymane Sentici
 * @return A json_object struct containing the whole json file
 */
struct json_object *parse_network(char *filename);


/**
 * Fills the components of the neuron given in argument with the content of the
 * json_object
 *
 * @author Souleymane Sentici
 */
void parse_neuron_from_file(struct json_object *neuron_object, Neuron *neuron);


/**
 * Fille the components of the layer given in argument with the content of the
 * json_object
 *
 * @author Souleymane Sentici
 */
void parse_layer_from_file(struct json_object *layer_object, Layer *layer);


/**
 * Recovers the network in the "filename" file and parses it into "network"
 *
 * @author Souleymane Sentici
 */
void parse_network_from_file(char *filename, Network *network);

#endif
