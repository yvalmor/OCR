#include <stdio.h>
#include <stdlib.h>

#include "../hdr/text.h"

int save_Text(char *file_name, char *text)
{
    FILE *file = fopen(file_name, "w+");

    if(file == NULL)
    {
        printf("Impossible to open the file \"%s\"", file_name);
        return 1;
    }

    fprintf(file, "%s", text);
    fclose(file);
    printf("file: %s: saved successfully!\n", file_name);

    return 0;
}
