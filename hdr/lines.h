#ifndef LINES_H
#define LINES_H


/**
 * Gets the average number of spaces between two words in a line
 *
 * @author Yvon Morice
 * @param image, the part of the image in which we want the average
 * @return the average number of spaces between two words in the image
 */
int get_words_space(ImagePart *image);


/**
 * Gets an isolated letter
 *
 * @author Yvon Morice
 * @param image, the part of the image in which we the letter
 * @return the isolated letter
 */
ImagePart *get_letters(ImagePart *image);


/**
 * Separates the words and letters in a line
 *
 * @author Yvon Morice
 * @param image, the line to cut in parts
 * @return a list of words
 */
List *get_words_letters(ImagePart *image);

#endif
