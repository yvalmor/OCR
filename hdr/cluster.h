#ifndef OCR_CLUSTER_H
#define OCR_CLUSTER_H

typedef struct tagLABEL
{
    int value;
    struct tagLABEL *next;
} LABELS;

void tagClusters(void *_pixels, void *_clusters, int width, int height);

#endif //OCR_CLUSTER_H
