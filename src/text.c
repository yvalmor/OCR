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
extern int debugMode;

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

ImagePart *imageResize(ImagePart *toResize, int new_w, int new_h)
{
    int width = toResize->cols;
    int height = toResize->rows;

    ImagePart *new_image = malloc(sizeof(ImagePart));
    new_image->rows = new_h;
    new_image->cols = new_w;
    new_image->img = calloc(new_h * new_w, sizeof(int));

    double xscale = (new_w+0.0) / width;
    double yscale = (new_h+0.0) / height;
    double threshold = 0.5 / (xscale * yscale);
    double yend = 0.0;

    for (int f = 0; f < new_h; f++)
    {
        double ystart = yend;
        yend = (f + 1) / yscale;
        if (yend >= height)
            yend = height - 0.000001;

        double xend = 0.0;

        for (int g = 0; g < new_w; g++)
        {
            double xstart = xend;
            xend = (g + 1) / xscale;
            if (xend >= width)
                xend = width - 0.000001;

            double sum = 0.0;

            int yst = ystart,
                yse = yend;
            for (int y = yst; y <= yse; y++)
            {
                double yportion = 1.0;
                if (y == yst)
                    yportion -= ystart - y;
                if (y == yse)
                    yportion -= y + 1 - yend;

                int xst = xstart,
                    xse = xend;
                for (int x = xst; x < xse; x++)
                {
                    double xportion = 1.0;
                    if (x == xst)
                        xportion -= xstart - x;
                    if (x == xse)
                        xportion -= x + 1 - xend;
                    sum += toResize->img[y * width + x];
                }
            }
            new_image->img[f * new_w + g] = sum > threshold ? 1 : 0;
        }
    }

    free(toResize->img);
    free(toResize);

    return new_image;
}

void build_word(List *letters, char **content)
{
    Element *letter = letters->first;

    while (letter != NULL)
    {
        /*
        ImagePart *image = letter->val;
        ImagePart *new_img = imageResize(image, 15, 15);
        feedForward(net, new_img->img, 1024);

        free(new_img->img);
        free(new_img);
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
        *content = strcat(*content, "\n");

        line = line->next;
    }
}

char *build_text(int *image, int rows, int cols)
{
    if (debugMode)
    {
        ImagePart *image_p = malloc(sizeof(ImagePart));
        image_p->img = calloc(rows * cols, sizeof(int));
        image_p->rows = rows;
        image_p->cols = cols;

        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                image_p->img[i * cols + j] = image[i * cols + j];

        saveImageAsBMP(image_p, "binarization.bmp");

        free(image_p->img);
        free(image_p);
    }

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
            content = strcat(content, "\n\n");

        paragraph = paragraph->next;
    }

    return content;
}

int build_word_with_training(List *letters, FILE *fp)
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
        ImagePart *new_img = imageResize(image, 32, 32);
        feedForward(net, new_img->img, 1024);

        free(new_img->img);
        free(new_img);
        */

        expected_result[index] = 0;

        //get_answer(net);

        letter = letter->next;
    }

    return 0;
}

int build_line_with_training(List *words,  FILE *fp)
{
    Element *word = words->first;

    while (word != NULL)
    {

        List *letters = word->val;
        if (build_word_with_training(letters, fp))
            return 1;;

        word = word->next;
    }

    return 0;
}

int build_paragraph_with_training(List *lines, FILE *fp)
{
    Element *line = lines->first;

    while (line != NULL)
    {
        List *words = line->val;
        if (build_line_with_training(words, fp))
            return 1;

        line = line->next;
    }

    return 0;
}

void build_text_with_training(int *image, int rows, int cols, FILE *fp)
{
    if (debugMode)
    {
        ImagePart *image_p = malloc(sizeof(ImagePart));
        image_p->img = calloc(rows * cols, sizeof(int));
        image_p->rows = rows;
        image_p->cols = cols;

        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                image_p->img[i * cols + j] = image[i * cols + j];

        saveImageAsBMP(image_p, "binarization.bmp");

        free(image_p->img);
        free(image_p);
    }

    List *paragraphs = get_paragraphs(image, rows, cols);

    Element *paragraph = paragraphs->first;

    while (paragraph != NULL)
    {
        List *lines = paragraph->val;
        if (build_paragraph_with_training(lines, fp))
            break;

        paragraph = paragraph->next;
    }
}
