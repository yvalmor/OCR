#ifndef BITMAP_H
#define BITMAP_H

#include <stdio.h>

/**
 * Saves a string inside a file
 *
 * @author Yvon Morice
 * @param file_name, char[]
 * @param text, char[]
 * @return 1 if fails, 0 otherwise
 */
int save_Text(char *file_name, char *text);


/**
 * Resizes an image
 *
 * @author Yvon Morice
 * @param toResize, ImagePart
 * @param new_w, int
 * @param new_h, int
 * @return the resized image
 */
ImagePart *imageResize(ImagePart *toResize, int new_w, int new_h);


/**
 * Saves the result on the letters inside of a word
 * given by the neural network in content
 *
 * @author Yvon Morice
 * @param letters, List
 * @param content, char
 */
void build_word(List *letters, char **content);


/**
 * Saves the result of build_word for every word
 * in a line inside of content
 *
 * @author Yvon Morice
 * @param words, List
 * @param content, char
 */
void build_line(List *words, char **content);


/**
 * Saves the result of build_line for every word
 * in a paragraph inside of content
 *
 * @author Yvon Morice
 * @param lines, List
 * @param content, char
 */
void build_paragraph(List *lines, char **content);


/**
 * Saves the result of build_paragraph for every paragraph
 * in an image
 *
 * @param image, int[]
 * @param rows, int
 * @param cols, int
 * @return a string containing the result on the text from the image
 */
char *build_text(int *image, int rows, int cols);


/**
 * Trains the neural network with the content of fp
 * and the result of the neural network
 *
 * @author Yvon Morice
 * @param letters, List
 * @param fp, FILE
 * @return 1 if there was an error, 0 otherwise
 */
int build_word_with_training(List *letters, FILE *fp);


/**
 * Calls build_word_with_training
 *
 * @author Yvon Morice
 * @see build_word_with_training
 * @param words, List
 * @param fp, FILE
 * @return 1 if there was an error, 0 otherwise
 */
int build_line_with_training(List *words, FILE *fp);


/**
 * Calls build_line_with_training
 *
 * @author Yvon Morice
 * @see build_line_with_training
 * @param lines, List
 * @param fp, FILE
 * @return 1 if there was an error, 0 otherwise
 */
int build_paragraph_with_training(List *lines, FILE *fp);


/**
 * Calls build_paragraph_with_training
 *
 * @author Yvon Morice
 * @see build_paragraph_with_training
 * @param image, int[]
 * @param rows, int
 * @param cols, int
 * @param filename, char[]
 */
void build_text_with_training(int *image, int rows, int cols, FILE *fp);

#endif
