#ifndef OCR_PROCESSING_H
#define OCR_PROCESSING_H

#include "../hdr/bitmap.h"

void toGrayscale(IMAGE image, int intensity[*][*]);
void toBlackAndWhite(IMAGE image, int intensity[*][*]);

void toMatrix(char *text, int rows, int columns, int *matrix);

#endif //OCR_PROCESSING_H