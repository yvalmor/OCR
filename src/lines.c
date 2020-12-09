#include "../hdr/list.h"
#include "../hdr/paragraphs.h"
#include "../hdr/seg2.h"

int get_words_space(ImagePart *image)
{
    unsigned int max_count = 0,
                 min_count = cols,
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

List get_letters(ImagePart *image)
{
    List letters_l = new_list();
    int s_index = 0;

    for (int x = 0; x <= image->cols; x++)
    {
        if (is_blank_column(image, x) || x == image->cols)
        {
            if (x == s_index)
                s_index++;
            else
            {
                ImagePart *new_img = cut_image(image, s_index, 0, x - s_index,
                                               image->rows);
                new_img = get_all_text(new_img, 50);
                new_img = resize_image(new_img, 32);

                letters_l = push_last_list(letters_l, new_img, LetterType);

                s_index++;
            }
        }
    }

    return letters_l;
}

List get_words_letters(ImagePart *image)
{
    image = get_all_text(image, 50);
    int space_limit = get_words_space(image);
    space_limit -= space_limit * 0.4;

    int wait_for_b_col = 0;
    List words_l = new_list();
    int s_index = 0;
    int blank_count = 0;

    for (int x = 0; x <= image->cols; x++)
    {
        if (wait_for_b_col && !is_blank_column(image, x))
            wait_for_b_col = 0;

        if (x != image->cols && is_blank_column(image, x) && !wait_for_b_col)
            blank_count++;
        else
            blank_count = 0;

        if (blank_count >= space_limit || x == image->cols)
        {
            ImagePart *new_img = cut_image(image, s_index, 0, x - s_index,
                                           image->rows);

            void *letters = get_letters(new_img);

            words_l = push_last_list(words_l, letters, WordType);

            wait_for_b_col = 1;
            s_index++;
            blank_count = 0;
        }
    }

    return words_l;
}
