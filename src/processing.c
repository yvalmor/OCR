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

int* histogramme(int intensity[][],int row,int column)
{
    int histo[255];
    for (int i = 0;i<row;i++)
    {
        for (int j = 0;j<column;j++)
            histo[intensity[i][j]]+=1;
    }
    return histo;
}

float muValue(histo[],int size)
{
    float mu = 0;
    for (int i = 0;i<255;i++)
    {
        mu+= i*histo[i];
    }
    mu = mu/size;
}

float sigmaPower_of_2(float mu,int size)
{
    float sigmPower2 = 0;
    for(int i = 0;i<255;i++)
    {
        sigmPower2 += ((i-mu)*(i-mu))*histo[i];
    }
    sigmPower2 = sigmPower2/size;
    return sigmPower2,mu;
}

int treshold(size)
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
        float sigm1 = sigmaPower_of_2(mu1, size);
        float sigm2 = sigmaPower_of_2(mu2, size);

        float vB2 = (nbPixel1 / size) * (nbPixel2 / size) * ((mu1 - mu2) * (mu1 - mu2));

        if (vB<vB2)
        {
            vB = vB2;
            T = j;
        }
    }
}

void toBlackAndWhite2(PIXEL *pixels,int row, int column,int intensity[row][column])
{
    int size = row*column;
    int histo[255] = histogramme(intensity,row,column);
    int T = treshold(size);

    for (int i = 0;i<row;i++)
    {
        for (int j = 0; j < column; j++)
        {
            if (intensity[i][j] < T)
                intensity[i][j] = 1;
            else
                intensity[i][j] = 0;
        }
    }
}
