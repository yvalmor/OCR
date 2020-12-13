#include <stdlib.h>

#include "../hdr/bitmap.h"
#include "../hdr/list.h"
#include "../hdr/segmentation.h"
#include "../hdr/lines.h"
#include "../hdr/main.h"

extern int debugMode;
static int cpt = 0;

int is_blank_line(ImagePart *image, int height)
{
    int cols = image->cols;
    int rows = image->rows;

    if (height > rows || height < 0)
        return 0;

    for (int i = 0; i < cols; i++)
    {
        if (image->img[height * cols + i] == 1)
            return 0;
    }

    return 1;
}

int is_blank_column(ImagePart *image, int width)
{
    int cols = image->cols;
    int rows = image->rows;

    if (width > cols || width < 0)
        return 0;

    for (int i = 0; i < rows; i++)
    {
        if (image->img[i * cols + width] == 1)
            return 0;
    }

    return 1;
}

ImagePart *get_all_text(ImagePart *image)
{
    int left = image->cols,
        right = 0,
        top = image->rows,
        bottom = 0;

    for (int i = 0; i < image->rows; i++)
        for (int j = 0; j < image->cols; j++)
        {
            int val = image->img[i * image->cols + j];

            if (val && j < left)
                left = j;
            if (val && j > right)
                right = j;
            if (val && i < top)
                top = i;
            if (val && i > bottom)
                bottom = i;
        }

    ImagePart *new_img = cut_image(image, left, top,
                                   right - left + 1, bottom - top + 1);
    return new_img;
}

int get_paragraph_space(ImagePart *image)
{
    int paragraphSpace = 0;
    int lineHeight = 0;

    int spaceCount = 0;
    int lineHeightCount = 0;

    for (int i = 0; i < image->rows; i++)
    {
        if (is_blank_line(image, i))
        {
            if (lineHeightCount != 0 && lineHeightCount > lineHeight)
            {
                lineHeight = lineHeightCount;
            }

            spaceCount++;
            lineHeightCount = 0;
        }
        else
        {
            if (spaceCount != 0 && spaceCount > paragraphSpace)
            {
                paragraphSpace = spaceCount;
            }

            spaceCount = 0;
            lineHeightCount++;
        }
    }

    return paragraphSpace;
}

ImagePart *cut_image_m(int *image, int x, int y, int w, int h)
{
    size_t rows = h;
    size_t cols = w;

    ImagePart *new_img = malloc(sizeof(ImagePart));

    new_img->rows = h;
    new_img->cols = w;

    new_img->img = calloc(new_img->rows * new_img->cols, sizeof(int));

    for (size_t i = y; i < rows; i++)
        for (size_t j = x; j < cols; j++)
            new_img->img[i * cols + j] = image[i * cols + j];

    return new_img;
}

ImagePart *cut_image(ImagePart *image, int x, int y, int w, int h)
{
    size_t rows = h + y;
    size_t cols = w + x;

    ImagePart *new_img = malloc(sizeof(ImagePart));

    new_img->rows = h;
    new_img->cols = w;

    new_img->img = calloc(new_img->rows * new_img->cols, sizeof(int));

    for (size_t i = y; i < rows; i++){
        for (size_t j = x; j < cols; j++)
            new_img->img[(i - y) * new_img->cols + j - x] =
                image->img[i * image->cols + j];
    }

    return new_img;
}

List *get_paragraphs_lines(ImagePart *image, int paragraphSpace)
{
    image = get_all_text(image);
    saveImageAsBMP(image, "image.bmp");

    int s_index = 0;
    int index = 0;
    int white = 0;

    List *paragraphs = new_list();
    List *lines = new_list();

    while (index <= image->rows)
    {
        if (index == image->rows || is_blank_line(image, index))
        {
            if (white == 0 && index != 0)
            {
                white++;

                ImagePart *new_img =
                    cut_image(image, 0, s_index, image->cols, index - s_index);

                if (debugMode)
                {
                    char x1 = cpt/1000 + '0',
                         x2 = cpt/100%10 + '0',
                         x3 = cpt/10%10 + '0',
                         x4 = cpt%1000 + '0';

                    char name[20] = {
                        'l', 'i', 'n', 'e', 's', '/',
                        'l', 'i', 'n', 'e', 's',
                        x1, x2, x3, x4, '.', 'b', 'm', 'p'
                    };

                    saveImageAsBMP(new_img, name);
                    cpt++;
                }

                List *l = get_words_letters(new_img);
                void *elt = l;

                lines = push_last_list(lines, elt, LineType);
            }
            else
                white++;

            index++;
        }
        else
        {
            if (white != 0)
            {
                s_index = index;

                if (white > 0.95 * paragraphSpace && lines != NULL)
                {
                    void *elt = lines;
                    paragraphs = push_last_list(paragraphs, elt, ParagraphType);
                    lines = new_list();
                }

                white = 0;
                index++;
            }
            else
                index++;
        }
    }

    if (lines != NULL)
    {
        void *elt = lines;
        paragraphs = push_last_list(paragraphs, elt, ParagraphType);
    }

    return paragraphs;
}

List *get_paragraphs(int *image, int rows, int cols)
{
    ImagePart *img = cut_image_m(image, 0, 0, cols, rows);

    img = get_all_text(img);

    int paragraphSpace = get_paragraph_space(img);

    List *paragraphs = get_paragraphs_lines(img, paragraphSpace);

    return paragraphs;
}
