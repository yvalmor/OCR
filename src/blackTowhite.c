int toGrayscale(PIXEL *pixels,int row,int column)
{
    int intensity[row][column];
    for (int i = 0;i<row;i++)
    {
        for (int j = 0;j<column;j++)
        {
            (pixels+i*row+j)-> r;
            (pixels+i*row+j)-> g;
            (pixels+i*row+j)-> b;
            Uint8 average = 0.3*r + 0.59*g + 0.11*b;
            intensity[i][j] = average;
        }
    }
    return intensity;
}
void toBlackAndWhite(PIXEL *pixels,int row, int column,intensity)
{
    for (int i = 0;i<row;i++)
    {
        for (int j = 0;j<column;j++)
        {
            if (intensity[i][j] >= 127)
                intensity[i][j] = 255;
            else
                intensity[i][j] = 0;
        }
    }
}