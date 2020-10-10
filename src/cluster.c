#include "../hdr/cluster.h"

void checkNeighbours(void *_pixels, void *_clusters, int x, int y);
int checkPixel(void *_pixels, void *_clusters, int x, int y);

static int currentLabel;
static int w;
static int h;

void getClusters(void *_pixels, void *_clusters, int width, int height)
{
    int (*_pixels)[height] = _pixels;
    int (*_clusters)[height] = _clusters;

    w = width;
    h = height;

    currentLabel = 1;

    for (int i = 0; i < width; ++i)
        for (int j = 0; j < height; ++j)
            if (checkPixel(pixels, clusters, i, j))
            {
                clusters[i][j] = currentLabel;
                checkNeighbours(pixels, clusters, i, j);
                currentLabel++;
            }
}

void checkNeighbours(void *_pixels, void *_clusters, int x, int y)
{
    int (*_pixels)[height] = _pixels;
    int (*_clusters)[height] = _clusters;

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
    int (*_pixels)[height] = _pixels;
    int (*_clusters)[height] = _clusters;

    if (x < 0 || x >= w || y < 0 || y >= h)
        return 0;

    return pixels[x][y] && !clusters[x][y];
}