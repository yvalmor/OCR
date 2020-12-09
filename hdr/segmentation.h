#ifndef SEG_H
#define SEG_H

int is_blank_line(ImagePart *image, int height)

int is_blank_column(ImagePart *image, int width)

int get_paragraph_space(ImagePart *image)

ImagePart *cut_image(Imagepart *image, int x, int y, int w, int h)

List get_paragraphs_lines(ImagePart *image, int paragraphSpace)

List get_paragraphs(int *image, int rows, int cols)

#endif
