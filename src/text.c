#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>

#include "../hdr/bitmap.h"
#include "../hdr/list.h"
#include "../hdr/text.h"
#include "../hdr/segmentation.h"
#include "../hdr/network.h"
#include "../hdr/main.h"

extern Network *net;

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

void build_word(List *letters, char **content)
{
    Element *letter = letters->first;

    while (letter != NULL)
    {
        /*
        ImagePart *image = letter->val;
        resize_image(image, 32, 32);
        feedForward(net, image->img, 1024);
        */

        char new_content = 'x';//get_answer(net);

        char *c = calloc(2, sizeof(char));
        c[0] = new_content;
        *content = strcat(*content, c);

        letter = letter->next;
    }
}

void build_line(List *words, char **content)
{
    Element *word = words->first;

    while (word != NULL)
    {
        char *new_content = calloc(10000, sizeof(char));

        List *letters = word->val;
        build_word(letters, &new_content);

        *content = strcat(*content, new_content);
        *content = strcat(*content, " ");

        word = word->next;
    }
}

void build_paragraph(List *lines, char **content)
{
    Element *line = lines->first;

    while (line != NULL)
    {
        char *new_content = calloc(10000, sizeof(char));

        List *words = line->val;
        build_line(words, &new_content);

        *content = strcat(*content, new_content);
        *content = strcat(*content, "\n\n");

        line = line->next;
    }
}

char *build_text(int *image, int rows, int cols)
{
    List *paragraphs = get_paragraphs(image, rows, cols);

    char *content = calloc(1000000, sizeof(char));

    Element *paragraph = paragraphs->first;

    while (paragraph != NULL)
    {
        char *new_content = calloc(10000, sizeof(char));

        List *lines = paragraph->val;
        build_paragraph(lines, &new_content);

        content = strcat(content, new_content);

        if (paragraph->next != NULL)
            content = strcat(content, "\n\n\n\n");

        paragraph = paragraph->next;
    }

    return content;
}

int build_word_with_training(List *letters, char **content, FILE *fp)
{
    Element *letter = letters->first;

    double expected_result[62];

    for (int i = 0; i < 62; i++)
        expected_result[i] = 0;

    while (letter != NULL)
    {
        char current;
        while ((current = getc(fp)) == ' ' || current == '\n');

        if (current== EOF)
            return 1;

        int index = 0;

        if (current >= 'A' && current <= 'Z')
            index = current - 'A';
        else if (current >= 'a' && current <= 'z')
            index  = current - 'a' + 26;
        else if (current >= '0' && current <= '9')
            index = current - '0' + 52;

        expected_result[index] = 1;

        index = expected_result[index]; // to delete, just avoiding a warning

        /*
        ImagePart *image = letter->val;
        resize_image(image, 32, 32);
        feedForward(net, image->img, 1024);
        */

        expected_result[index] = 0;

        char new_content = 'x';//get_answer(net);

        char *c = calloc(2, sizeof(char));
        c[0] = new_content;
        *content = strcat(*content, c);

        letter = letter->next;
    }

    return 0;
}

int build_line_with_training(List *words, char **content, FILE *fp)
{
    Element *word = words->first;

    while (word != NULL)
    {
        char *new_content = calloc(10000, sizeof(char));

        List *letters = word->val;
        if (build_word_with_training(letters, &new_content, fp))
            return 1;;

        *content = strcat(*content, new_content);
        *content = strcat(*content, " ");

        word = word->next;
    }

    return 0;
}

int build_paragraph_with_training(List *lines, char **content, FILE *fp)
{
    Element *line = lines->first;

    while (line != NULL)
    {
        char *new_content = calloc(10000, sizeof(char));

        List *words = line->val;
        if (build_line_with_training(words, &new_content, fp))
            return 1;

        *content = strcat(*content, new_content);
        *content = strcat(*content, "\n\n");

        line = line->next;
    }

    return 0;
}

void build_text_with_training(int *image, int rows, int cols, FILE *fp)
{
    List *paragraphs = get_paragraphs(image, rows, cols);

    char *content = calloc(1000000, sizeof(char));

    Element *paragraph = paragraphs->first;

    while (paragraph != NULL)
    {
        char *new_content = calloc(10000, sizeof(char));

        List *lines = paragraph->val;
        if (build_paragraph_with_training(lines, &new_content, fp))
        {
            content = strcat(content, new_content);
            break;
        }

        content = strcat(content, new_content);

        if (paragraph->next != NULL)
            content = strcat(content, "\n\n\n\n");

        paragraph = paragraph->next;
    }
}
