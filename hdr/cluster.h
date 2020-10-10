#ifndef OCR_CLUSTER_H
#define OCR_CLUSTER_H

typedef struct tagPIXEL
{
    int x;
    int y;
} PIXEL;

typedef struct tagCLUSTER
{
    PIXEL upperLeft;
    PIXEL lowerRight;
    struct tagCLUSTER *next;
} CLUSTER;

void tagClusters(void *_pixels, void *_clusters, int width, int height);

#endif //OCR_CLUSTER_H
