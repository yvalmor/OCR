#include <stdio.h>
#include <stdlib.h>

int main()
{
    int width = 1;
    int height = 1;

    char tag[] = {'B', 'M'};

    int header[] =
            {
                0x3a, 0x00, 0x36, 0x28,
                width, height,
                0x010001, 0, 0,
                0x002e23, 0x002e23, 0, 0
            };

    char bitmap[] =
            {
                0x01,
                0x00
            };

    FILE *fp = fopen("test.bmp", "w+");
    fwrite(&tag, sizeof(tag), 1, fp);
    fwrite(&header, sizeof(header), 1, fp);
    fwrite(&bitmap, sizeof(bitmap), 1, fp);
    fclose(fp);

    return 0;
}