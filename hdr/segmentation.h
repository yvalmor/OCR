#ifndef SEG_H
#define SEG_H

#include "../hdr/list.h"
#include "../hdr/segmentation.h"


/**
 * Checks if a line doesn't contains text
 *
 * @author Yvon Morice
 * @param image, ImagePart
 * @param height, int index of the line
 * @return 1 if it is empty, 0 otherwise
 */
int is_blank_line(ImagePart *image, int height);


/**
 * Checks if a line doesn't contains text
 *
 * @author Yvon Morice
 * @param image, ImagePart
 * @param width, int index of the column
 * @return 1 if it is empty, 0 otherwise
 */
int is_blank_column(ImagePart *image, int width);


/**
 * Gets the average number of spaces between two lines
 *
 * @author Yvon Morice
 * @param image, ImagePart
 * @return The average number of spaces between two pages
 */
int get_paragraph_space(ImagePart *image);


/**
 * Gets a part of an int matrix
 *
 * @author Yvon Morice
 * @param image, int[]
 * @param x, int
 * @param y, int
 * @param w, int
 * @param h, int
 * @return
 */
ImagePart *cut_image_m(int *image, int x, int y, int w, int h);

/**
 * Gets a part of a binarized image
 *
 * @author Yvon Morice
 * @param image, ImagePart
 * @param x, int
 * @param y, int
 * @param w, int
 * @param h, int
 * @return
 */
ImagePart *cut_image(ImagePart *image, int x, int y, int w, int h);


/**
 * Gets the paragraphs and lines of the image
 *
 * @author Yvon Morice
 * @param image, ImagePart
 * @param paragraphSpace, int
 * @return a List of paragraphs
 */
List *get_paragraphs_lines(ImagePart *image, int paragraphSpace);


/**
 * Get the paragraphs from an int matrix
 *
 * @author Yvon Morice
 * @param image, int[]
 * @param rows, int
 * @param cols, int
 * @return
 */
List *get_paragraphs(int *image, int rows, int cols);


/**
 * Removes the borders without text of the image
 *
 * @author Yvon Morice
 * @param image, ImagePart
 * @return the text extracted
 */
ImagePart *get_all_text(ImagePart *image);

#endif
