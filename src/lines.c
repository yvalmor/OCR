#include <string.h>

#include "../hdr/list.h"
#include "../hdr/segmentation.h"

int get_words_space(ImagePart *image)
{
    unsigned int max_count = 0,
                 min_count = image->cols,
                 count = 0;

    for (int x = 0; x < image->cols; ++x)
    {
        if (is_blank_column(image, x))
            count++;
        else
        {
            if (count > max_count)
                max_count = count;
            if (count < min_count)
                min_count = count;
            count = 0;
        }
    }

    return max_count - (min_count) / 2;
}

ImagePart *get_letters(ImagePart *image)
{
    return get_all_text(image);
}

List *get_words_letters(ImagePart *image)
{
    image = get_all_text(image);
    int words_space = get_words_space(image);
    words_space += 0.1 * words_space;

    List *words_l = new_list();
    List *letters = new_list();

    int s_index = 0;
    int index = 0;
    int white = 0;

    while (index < image->cols)
    {
        if (is_blank_column(image, index))
        {
            if (white == 0 && index != 0)
            {
                white++;

                ImagePart *new_img =
                    cut_image(image, s_index, 0, index - s_index, image->rows);

                ImagePart *l = get_letters(new_img);
                void *elt = l;

                letters = push_last_list(letters, elt, LetterType);
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

                if (white >= words_space)
                {
                    void *elt = letters;
                    words_l = push_last_list(words_l, elt, WordType);
                    letters = new_list();
                }

                white = 0;
            }

            index++;
        }
    }

    if (letters != NULL)
    {
        void *elt = letters;
        words_l = push_last_list(words_l, elt, WordType);
    }

    return words_l;
}
