#include <stdlib.h>

#include "../hdr/rlsa.h"


void vertical_rlsa(int rows, int cols, int *matrix, int *vert, int threshold)
{
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            if (*(matrix + i * rows + j) == 1)
                *(vert + i * rows + j) = 1;
            else
            {
                int sum = 0;
                for (int k = -threshold; k <= threshold && j + k < cols; k++)
                    if (j + k >= 0)
                        sum += *(matrix + i * rows + j + k);
                if (sum >= threshold)
                    *(vert + i * rows + j) = 1;
            }
}

void horizontal_rlsa(int rows, int cols, int *matrix, int *hori, int threshold)
{
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            if (*(matrix + i * rows + j) == 1)
                *(hori + i * rows + j) = 1;
            else
            {
                int sum = 0;
                for (int k = -threshold; k <= threshold && j + k < cols; k++)
                    if (j + k >= 0)
                        sum += *(matrix + i * rows + j + k);
                if (sum >= threshold)
                    *(hori + i * rows + j) = 1;
            }
}

int mcl()
{
    return 2;
}

int mtld()
{
    return 2;
}

void rlsa(int rows, int cols, int *matrix, int *rlsa_mat)
{
    int *vert = calloc(rows * cols, sizeof(int));
    int *hori = calloc(rows * cols, sizeof(int));

    vertical_rlsa(rows, cols, matrix, vert, 2 * mcl());
    horizontal_rlsa(rows, cols, matrix, hori, mtld());

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            *(rlsa_mat + i * rows + j) = *(vert + i * rows + j) & *(hori + i * rows + j);
}




