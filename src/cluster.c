#include "../hdr/cluster.h"

void checkNeighbours(int **pixels, int **clusters, int x, int y);
int checkPixel(int **pixels, int **clusters, int x, int y);

static int currentLabel;
static int w;
static int h;

void getClusters(int **pixels, int **clusters, int width, int height)
{
    pix = pixels;

    w = width;
    h = height;

    currentLabel = 1;

    for (int i = 0; i < width; ++i)
        for (int j = 0; j < height; ++j)
            if (checkPixel(pixels, clusters, i, j))
            {
                clusters[i][j] = currentLabel;
                checkNeighbours(pixels, clusters, i, j);
                currentLabel++:
            }
}

void checkNeighbours(int **pixels, int **clusters, int x, int y)
{
    for (int i = x - 1; i < x + 2; ++i)
        for (int j = y - 1; j < y + 2; ++j)
            if (checkPixel(clusters, i, j))
            {
                clusters[i][j] = currentLabel;
                checkNeighbours(pixels, clusters, i, j);
            }
}

int checkPixel(int **pixels, int **clusters, int x, int y)
{
    if (x < 0 || x >= w || y < 0 || y >= h)
        return 0;

    return pixels[x][y] && !clusters[x][y];
}