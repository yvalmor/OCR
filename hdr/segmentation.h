#ifndef SEG_H
#define SEG_H

#include "../hdr/list.h"
#include "../hdr/segmentation.h"


int is_blank_line(ImagePart *image, int height);

int is_blank_column(ImagePart *image, int width);

int get_paragraph_space(ImagePart *image);

ImagePart *cut_image_m(int *image, int x, int y, int w, int h);

ImagePart *cut_image(ImagePart *image, int x, int y, int w, int h);

List *get_paragraphs_lines(ImagePart *image, int paragraphSpace);

List *get_paragraphs(int *image, int rows, int cols);

ImagePart *get_all_text(ImagePart *image);

#endif
