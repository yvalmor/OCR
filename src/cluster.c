#include <stdlib.h>
#include <stdio.h>

#include "../hdr/cluster.h"

void checkNeighbours(void *_pixels, void *_clusters, int x, int y);
int checkPixel(void *_pixels, void *_clusters, int x, int y);

int contains(int arr[], int length, int val);
void pushLabel(LABELS *head, int label);

static int currentLabel;
static int w;
static int h;

LABELS *firstLabel;
CLUSTER *firstCluster;

void setClusters(void *_clusters)
{
    int (*clusters)[h] = _clusters;

    LABELS *current = firstLabel;

    int left = -1;
    int right = -1;
    int up = -1;
    int down = -1;

    while (current != NULL)
    {
        for (int i = 0; i < w; ++i) {
            for (int j = 0; j < h; ++j) {
                if (clusters[i][j] == current -> value)
                    printf("%d i, %d j", i, j);
            }
        }
    }
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
        for (int j = 0; j < height; ++j)
            if (checkPixel(pixels, clusters, i, j))
            {
                pushLabel(firstLabel, currentLabel);
                clusters[i][j] = currentLabel;
                checkNeighbours(pixels, clusters, i, j);
                currentLabel++;
            }
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