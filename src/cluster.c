#include "../hdr/cluster.h"

void checkNeighbours(int **clusters, int x, int y, int currentLabel);
int checkPixel(int **clusters, int x, int y);

static int pix[][];

static int w;
static int h;

void getClusters(int **pixels, int **clusters, int width, int height)
{
    pix = pixels;

    w = width;
    h = height;

    int currentLabel = 1;

    for (int i = 0; i < width; ++i)
        for (int j = 0; j < height; ++j)
            if (checkPixel(clusters, i, j))
            {
                clusters[i][j] = currentLabel;
                checkNeighbours(clusters, i, j, currentLabel);
                currentLabel++:
            }
}

void checkNeighbours(int **clusters, int x, int y, int currentLabel)
{
    for (int i = x - 1; i < x + 2; ++i)
        for (int j = y - 1; j < y + 2; ++j)
            if (checkPixel(clusters, i, j))
            {
                clusters[i][j] = currentLabel;
                checkNeighbours(clusters, i, j, currentLabel);
            }
}

int checkPixel(int **clusters, int x, int y)
{
    if (x < 0 || x >= w || y < 0 || y >= h)
        return 0;

    return pix[x][y] && !clusters[x][y];
}