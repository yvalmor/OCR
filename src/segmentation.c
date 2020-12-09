#include "../hdr/list.h"

int is_blank_line(ImagePart *image, int height)
{
    int cols = image->cols,
        rows = image->rows;

    int *matrix = image->img;

    if (height > rows || height < 0)
        return 0;

    for (int i = 0; i < cols; i++)
    {
        if (*(matrix + height * rows + i) == 1)
            return 0;
    }

    return 1;
}

int is_blank_column(ImagePart *image, int width)
{
    int cols = image->cols,
        rows = image->rows;

    int *matrix = image->img;

    if (width > cols || width < 0)
        return 0;

    for (int i = 0; i < rows; i++)
    {
        if (*(matrix + i * rows + width) == 1)
            return 0;
    }

    return 1;
}

ImagePart get_all_text(ImagePart *image)
{
    int left = image->cols,
        right = 0,
        top = image->rows,
        bottom = 0;

    for (int i = 0; i < image->rows; i++)
        for (int j = 0; j < image->cols; j++)
        {
            int val = *(image->img + i * rows + j);

            if (!val && x < left)
                left = x;
            if (!val && x > right)
                right = x;
            if (!val && y < top)
                top = y;
            if (!val && y > bottom)
                bottom = y;
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

    int rows = image->rows,
        cols = image->cols;

    for (int i = 0; i < rows; i++)
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

ImagePart *cut_image(int *image, int rows, int x, int y, int w, int h)
{
    ImagePart *new_img = malloc(sizeof(ImagePart));

    new_img->rows = h - y;
    new_img->cols = w - x;

    int *matrix = calloc(new_img->rows * new_img * cols, sizeof(int));

    for (int i = y; i < h; i++)
        for (int j = x; j < w; j++)
            *(matrix + i * rows + j) = *(image + i * rows + j);

    return new_image;
}

ImagePart *cut_image(Imagepart *image, int x, int y, int w, int h)
{
    ImagePart *new_img = malloc(sizeof(ImagePart));

    new_img->rows = h - y;
    new_img->cols = w - x;

    int *matrix = calloc(new_img->rows * new_img * cols, sizeof(int));

    for (int i = y; i < h; i++)
        for (int j = x; j < w; j++)
            *(matrix + i * image->rows + j) =
                *(image->img + i * image->rows + j);

    return new_image;
}

List get_paragraphs_lines(ImagePart *image, int paragraphSpace)
{
    int s_index = 0;
    int index = 0;
    int white = 0;

    List paragraphs = new_list();
    List lines = new_list();

    while (index < image->rows)
    {
        if (is_blank_line(image, index))
        {
            if (white == 0)
            {
                white++;

                ImagePart *new_img =
                    cut_image(image, 0, s_index, cols, index - s_index);

                List l = get_words_letters(new_img);
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

                if (white > 0.9 * paragraphSpace)
                {
                    void *elt = line;
                    paragraphs = push_last_list(paragraphs, elt, ParagraphType);
                    line = new_list();
                }

                white++;
                index += 5;
            }
            else
                index++;
        }
    }

    return paragraphs;
}

List get_paragraphs(int *image, int rows, int cols)
{
    ImagePart *img = cut_image(image, rows, 0, 0, rows, cols);

    int paragraphSpace = get_paragraph_space(img);

    List paragraphs = get_paragraphs_lines(img, paragraphSpace);

    return paragraphs;
}
