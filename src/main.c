#include <stdio.h>
#include <stdlib.h>

#include "../hdr/cluster.h"

void initClusters(void *_clusters, int width, int height);

int main()
{
    const int width = 20;
    const int height = 20;

    int placeholder[20][20] = {
            {1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0},
            {0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0},
            {0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0},
            {0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0},
            {0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0},
            {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0}
    };

    int pixels[width][height];
    for (int i = 0; i < width; ++i)
        for (int j = 0; j < height; ++j)
            pixels[i][j] = placeholder[i][j];

    int clusters[width][height];

    initClusters(clusters, width, height);

    tagClusters(pixels, clusters, width, height);

    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            printf("%d", clusters[i][j]);
        }
        printf("\n");
    }
}

void initClusters(void *_clusters, int width, int height)
{
    int (*clusters)[height] = _clusters;

    for (int i = 0; i < width; ++i)
        for (int j = 0; j < height; ++j)
            clusters[i][j] = 0;
}