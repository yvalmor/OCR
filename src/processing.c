#include "../hdr/processing.h"

void toGrayscale(IMAGE image, int *intensity)
{
    int r, g, b;

    int rows = image.rows;
    int columns = image.columns;

    for (int i = 0;i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            r = (image.pixels + i * columns + j)-> r;
            g = (image.pixels + i * columns + j)-> g;
            b = (image.pixels + i * columns + j)-> b;

            Uint8 average = 0.3*r + 0.59*g + 0.11*b;

            *(intensity + i * columns + j) = average;
        }
    }
}

void toBlackAndWhite(IMAGE image, int *intensity)
{
    int rows = image.rows;
    int columns = image.columns;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            int value = *(intensity + i * columns + j);

            if (value < 127)
                *(intensity + i * columns + j) = 0;
            else
                *(intensity + i * columns + j) = 1;
        }
    }
}

int* histogram(int *intensity, int row, int column)
{
    int *histo = malloc(255 * sizeof(int));

    for (int i = 0;i<row;i++)
    {
        for (int j = 0;j<column;j++)
            histo[intensity[i * column + j]]++;
    }

    return histo;
}

float muValue(int *histo, int size)
{
    float mu = 0;

    for (int i = 0;i<255;i++)
    {
        mu+= i*histo[i];
    }

    mu = mu/size;

    return mu;
}

float sigmaPower_of_2(float mu, int *histo, int size)
{
    float sigmPower2 = 0;

    for(int i = 0;i<255;i++)
    {
        sigmPower2 += ((i-mu)*(i-mu))*histo[i];
    }

    sigmPower2 = sigmPower2/size;

    return sigmPower2;
}

int treshold(int *histo, int size)
{
    int nbPixel1 = 0;
    int nbPixel2 = 0;

    float vB;
    float T;

    for(int j = 1;j<255;j++)
    {
        int class1[j];
        int class2[255-j];

        for (int i = 0; i < 255; i++)
        {
            if (i < j)
            {
                class1[i] = histo[i];
                nbPixel1 += class1[i];
            }
            else
            {
                class2[i] = histo[i];
                nbPixel2 += class2[i];
            }
        }

        float mu1 = muValue(class1, size);
        float mu2 = muValue(class2, size);

        //float sigm1 = sigmaPower_of_2(mu1, histo, size);
        //float sigm2 = sigmaPower_of_2(mu2, size);

        float vB2 = (nbPixel1 / size) * (nbPixel2 / size) * ((mu1 - mu2) * (mu1 - mu2));

        if (vB<vB2)
        {
            vB = vB2;
            T = j;
        }
    }

    return T;
}

void toBlackAndWhite2(IMAGE image, int *intensity)
{
    int row = image.rows;
    int column = image.columns;

    int size = row*column;
    int *histo = histogram(intensity, row, column);
    int T = treshold(histo, size);

    for (int i = 0;i<row;i++)
    {
        for (int j = 0; j < column; j++)
        {
            if (intensity[i * column + j] < T)
                intensity[i * column + j] = 1;
            else
                intensity[i * column + j] = 0;
        }
    }

    free(histo);
}
