#include <string.h>
#include <SDL2/SDL.h>

#include "../hdr/list.h"
#include "../hdr/segmentation.h"
#include "../hdr/bitmap.h"

static int cpt = 0;

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

List *get_letters(ImagePart *image)
{
    List *letters_l = new_list();
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
                new_img = get_all_text(new_img);
                //new_img = resize_image(new_img, 32);

                SDL_Surface *surface;
                surface = SDL_CreateRGBSurface(0, new_img->cols, new_img->rows, 32, 0, 0, 0, 0);

                for (unsigned int x = 0; x < (unsigned int)new_img->cols; x++)
                    for (unsigned int y = 0; y < (unsigned int)new_img->rows; y++)
                    {
                        int val = new_img->img[y * new_img->cols + x];
                        Uint32 value = SDL_MapRGB(surface->format, val * 255, val * 255, val * 255);
                        put_pixel(surface, x, y, value);
                    }

                int x1 = cpt/100;
                int x2 = cpt%100/10;
                int x3 = cpt%10;

                char name[20] = {'l', 'e', 't', 't', 'e', 'r', 's',
                    cpt < 100 ? '0' : (char) x1 + '0',
                    cpt < 10 ? '0' : (char) x2 + '0',
                    (char) x3 + '0',
                    '.', 'b', 'm', 'p', '\0'};
                cpt++;

                SDL_SaveBMP(surface, name);
                SDL_FreeSurface(surface);

                letters_l = push_last_list(letters_l, new_img, LetterType);

                s_index++;
            }
        }
    }

    return letters_l;
}

List *get_words_letters(ImagePart *image)
{
    image = get_all_text(image);
    int space_limit = get_words_space(image);
    space_limit -= space_limit * 0.4;

    int wait_for_b_col = 0;
    List *words_l = new_list();
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
