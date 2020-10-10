#include <stdlib.h>
#include <stdio.h>

#include "../hdr/cluster.h"

void checkNeighbours(void *_pixels, void *_clusters, int x, int y);
int checkPixel(void *_pixels, void *_clusters, int x, int y);

int contains(int arr[], int length, int val);
void pushLabel(LABELS *head, int label);
void pushCluster(CLUSTER *head, int dimensions[4]);

static int currentLabel;
static int w;
static int h;

LABELS *firstLabel;
CLUSTER *firstCluster;

CLUSTER *setClusters(void *_clusters)
{
    firstCluster = malloc(sizeof(CLUSTER));

    int (*clusters)[h] = _clusters;

    LABELS *current = firstLabel;

    int dimensions[4];

    while (current != NULL)
    {
        for (int i = 0; i < 4; ++i)
            dimensions[i] = -1;

        for (int i = 0; i < w; ++i)
        {
            for (int j = 0; j < h; ++j)
            {
                if (clusters[i][j] == current -> value)
                    if (i < dimensions[0] || dimensions[0] == -1)
                        dimensions[0] = i;
                    if (i > dimensions[1] || dimensions[1] == -1)
                        dimensions[1] = i;
                    if (j < dimensions[2] || dimensions[2] == -1)
                        dimensions[2] = j;
                    if (j > dimensions[3] || dimensions[3] == -1)
                        dimensions[3]; = j;
            }
        }

        if (firstCluster -> up == -1)
        {
            firstCluster -> up = dimensions[0];
            firstCluster -> down = dimensions[1];
            firstCluster -> left = dimensions[2];
            firstCluster -> right = dimensions[3];
        }
        else
            pushCluster(firstCluster, dimensions);

        current = current -> next;
    }

    return firstCluster;
}

void tagClusters(void *_pixels, void *_clusters, int width, int height)
{
    firstLabel = malloc(sizeof(LABELS));

    int (*pixels)[height] = _pixels;
    int (*clusters)[height] = _clusters;

    w = width;
    h = height;

    currentLabel = 1;

    for (int i = 0; i < width; ++i)
    {
        for (int j = 0; j < height; ++j)
            if (checkPixel(pixels, clusters, i, j))
            {
                clusters[i][j] = currentLabel;
                checkNeighbours(pixels, clusters, i, j);

                if (firstLabel -> value == 0)
                    firstLabel -> value = currentLabel;
                else
                    pushLabel(firstLabel, currentLabel);

                currentLabel++;
            }
    }

    setClusters(clusters);
}

void checkNeighbours(void *_pixels, void *_clusters, int x, int y)
{
    int (*pixels)[h] = _pixels;
    int (*clusters)[h] = _clusters;

    for (int i = x - 3; i < x + 5; ++i)
        for (int j = y - 1; j < y + 2; ++j)
            if (checkPixel(pixels, clusters, i, j))
            {
                clusters[i][j] = currentLabel;
                checkNeighbours(pixels, clusters, i, j);
            }
}

int checkPixel(void *_pixels, void *_clusters, int x, int y)
{
    int (*pixels)[h] = _pixels;
    int (*clusters)[h] = _clusters;

    if (x < 0 || x >= w || y < 0 || y >= h)
        return 0;

    return pixels[x][y] && !clusters[x][y];
}

int contains(int arr[], int length, int val)
{
    for (int i = 0; i < length; ++i)
        if (arr[i] == val)
            return 1;
    return 0;
}

void pushLabel(LABELS *head, int label)
{
    LABELS *current = head;
    while (current -> next != NULL)
        current = current -> next;

    LABELS *new = malloc(sizeof(LABELS));
    new -> value = label;
    new -> next = NULL;

    current -> next = new;
}

void pushCluster(CLUSTER *head, int dimensions[4])
{
    CLUSTER *current = head;
    while (current -> next != NULL)
        current = current -> next;

    CLUSTER *new = malloc(sizeof(CLUSTER));
    new -> up = dimensions[0];
    new -> down = dimensions[1];
    new -> left = dimensions[2];
    new -> right = dimensions[3];
    new -> next = NULL;

    current -> next = new;
}