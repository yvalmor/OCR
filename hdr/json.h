#ifndef JSON_H
#define JSON_H

void write_network(Network *network, char *filename);
void parse_network_from_file(char *filename, Network *network);

#endif
