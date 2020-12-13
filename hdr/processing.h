#ifndef OCR_PROCESSING_H
#define OCR_PROCESSING_H

#include "../hdr/bitmap.h"

//Input:
//image :               IMAGE -> the image we use
//intensity :           int[][] -> intensity of image's pixels

//change the coloured image to a grayscale image
void toGrayscale(IMAGE image, int *intensity);

//Input:
//image :               IMAGE -> the image we use
//intensity :           int[][] ->intensity of image's pixels

//change the grayscaled image to a classic black and white image
void toBlackAndWhite(IMAGE image, int *intensity);

//Input:
//image :               IMAGE -> the image we use
//intensity :           int[][] -> intensity of image's pixels

//change the grayscaled image to a black and white image using the Otsu's method
void toBlackAndWhite2(IMAGE image, int *intensity);

#endif //OCR_PROCESSING_H
