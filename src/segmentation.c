#include "../hdr/segmentation.h"

int check_line(int line[])
{
    int length = sizeof(line) / sizeof(line[0]);

    for (int i = 0; i < length; ++i) {
        if (line[i] == 1)
            return 1;
    }

    return 0;
}