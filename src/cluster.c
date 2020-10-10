#include "../hdr/cluster.h"

void checkNeighbours(void *_pixels, void *_clusters, int x, int y);
int checkPixel(void *_pixels, void *_clusters, int x, int y);

static int currentLabel;
static int h;
static int w;

void tagClusters(void *_pixels, void *_clusters, int height, int width)
{
    int (*pixels)[width] = _pixels;
    int (*clusters)[width] = _clusters;

    h = height;
    w = width;

    currentLabel = 1;

    for (int i = 0; i < height; ++i)
        for (int j = 0; j < width; ++j)
            if (checkPixel(pixels, clusters, i, j))
            {
                clusters[i][j] = currentLabel;
                checkNeighbours(pixels, clusters, i, j);
                currentLabel++;
            }
}

void checkNeighbours(void *_pixels, void *_clusters, int x, int y)
{
    int (*pixels)[h] = _pixels;
    int (*clusters)[h] = _clusters;

    for (int i = x - 1; i < x + 2; ++i)
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