#include <stdio.h>
#include <string.h>

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
    printf("file: \"%s\": saved successfully!\n", file_name);

    return 0;
}

void build_word(List letters, char **content)
{
    Element *letter = letters->first;

    while (letter != NULL)
    {
        char new_content = 'x'; //TODO Replace by feed forward

        char *c = calloc(2, sizeof(char));
        c[0] = new_content;
        *content = strcat(*content, c);

        letter = letter->next;
    }
}

void build_line(List words, char **content)
{
    Element *word = words->first;

    while (word != NULL)
    {
        char *new_content = calloc(10000, sizeof(char));

        List *letters = word->value;
        build_word(letters, &new_content);

        *content = strcat(*content, new_content);
        *content = strcat(*content, " ");

        word = word->next;
    }
}

void build_paragraph(List paragraphs, char **content)
{
    Element *line = paragraphs->first;

    while (line != NULL)
    {
        char *new_content = calloc(10000, sizeof(char));

        List *words = line->value;
        build_line(words, &new_content);

        *content = strcat(*content, new_content);
        *content = strcat(*content, "\n");

        line = line->next;
    }
}

char *build_text(ImagePart image)
{
    List paragraphs = get_paragraphs(image);

    char *content = calloc(1000000, sizeof(char));

    Element *paragraph = paragraphs->first;

    while (paragraph != NULL)
    {
        //TODO
    }
}
