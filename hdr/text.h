#ifndef BITMAP_H
#define BITMAP_H

int save_Text(char *file_name, char *text);

char *build_text(int *image, int rows, int cols);
void build_text_with_training(int *image, int rows, int cols, FILE *fp);

#endif
