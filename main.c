#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
    int w = 16;
    int h = 16;
    int black[w][h] = {
            {1,1,1,1,0,0,0,0,0,0,0,0,0,0,0},
            {0,1,1,1,1,0,0,0,0,0,0,0,0,0,0},
            {0,0,1,1,1,1,0,0,0,0,0,0,0,0,0},
            {0,0,0,1,1,1,1,0,0,0,0,0,0,0,0},
            {0,0,0,0,1,1,1,1,0,0,0,0,0,0,0},
            {0,0,0,0,0,1,1,1,1,0,0,0,0,0,0},
            {0,0,0,0,0,0,1,1,1,1,0,0,0,0,0},
            {0,0,0,0,0,0,0,1,1,1,1,0,0,0,0},
            {0,0,0,0,0,0,0,0,1,1,1,1,0,0,0},
            {0,0,0,0,0,0,0,0,0,1,1,1,1,0,0},
            {0,0,0,0,0,0,0,0,0,0,1,1,1,1,0},
            {0,0,0,0,0,0,0,0,0,0,0,1,1,1,1},
            {0,0,0,0,0,0,0,0,0,0,0,0,1,1,1},
            {0,0,0,0,0,0,0,0,0,0,0,1,1,1,1},
            {0,0,0,0,0,0,0,0,0,0,1,1,1,1,0}
    };

    FILE *f;
    unsigned char *img = NULL;
    int filesize = 54 + w * h;
    if (img)
        free(img);
    img = malloc(w * h);
    memset(img, 0, sizeof(img));

    int x;
    int y;
    int b;
    unsigned char val;

    for (int i = 0; i < w; ++i) {
        for (int j = 0; j < h; ++j) {
            x = i;
            y = (h - 1) - j;
            b = black[i][j];
            val = b;
            img[x + y * w] = val;
        }
    }

    unsigned char bmpfileheader[14] = {'B','M', 0,0,0,0, 0,0, 0,0, 54,0,0,0};
    unsigned char bmpinfoheader[40] = {40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0, 24,0};
    unsigned char bmppad[3] = {0,0,0};

    bmpfileheader[ 2] = (unsigned char)(filesize    );
    bmpfileheader[ 3] = (unsigned char)(filesize>> 8);
    bmpfileheader[ 4] = (unsigned char)(filesize>>16);
    bmpfileheader[ 5] = (unsigned char)(filesize>>24);

    bmpinfoheader[ 4] = (unsigned char)(       w    );
    bmpinfoheader[ 5] = (unsigned char)(       w>> 8);
    bmpinfoheader[ 6] = (unsigned char)(       w>>16);
    bmpinfoheader[ 7] = (unsigned char)(       w>>24);
    bmpinfoheader[ 8] = (unsigned char)(       h    );
    bmpinfoheader[ 9] = (unsigned char)(       h>> 8);
    bmpinfoheader[10] = (unsigned char)(       h>>16);
    bmpinfoheader[11] = (unsigned char)(       h>>24);

    f = fopen("img.bmp","wb");
    fwrite(bmpfileheader,1,14,f);
    fwrite(bmpinfoheader,1,40,f);
    for(int i=0; i<h; i++)
    {
        fwrite(img+(w*(h-i-1)*3),3,w,f);
        fwrite(bmppad,1,(4-(w*3)%4)%4,f);
    }
    fclose(f);

    return 0;
}