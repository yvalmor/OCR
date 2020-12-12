#ifndef ROTATION_H
#define ROTATION_H

#include <SDL2/SDL.h>

struct result {
    double rho;
    double theta;
};

struct result *winner(int maxRho, int maxIndexTheta, int maxIndexRho, int acc[maxIndexTheta][maxIndexRho]);

void vote(int x, int y, int maxRho, int maxIndexTheta, int maxIndexRho, int acc[maxIndexTheta][maxIndexRho],
          SDL_Surface *img);

double find_angle(SDL_Surface *image);

SDL_Surface *SDL_RotateImage(SDL_Surface *origine, float angle);

#endif
