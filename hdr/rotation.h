#ifndef ROTATION_H
#define ROTATION_H

#include <SDL2/SDL.h>

struct result {
    double rho;
    double theta;
};

//Input:
//maxRho :                          int -> the max value of rho
//maxIndexTheta :                   int -> the max value of rho
//maxIndexRho :                     int -> the max value of rho
//acc[maxIndexTheta][maxIndexRho] : int[][] -> the max value of rho

//return rho and theta value
struct result *winner(int maxRho, int maxIndexTheta, int maxIndexRho,
                      int acc[maxIndexTheta][maxIndexRho]);

//Input :
//x :                               int -> the x position of the pixel
//y :                               int -> the y position of the pixel
//maxRho :                          int -> the max value of rho
//maxIndexTheta :                   int -> the max value of rho
//maxIndexRho :                     int -> the max value of rho
//acc[maxIndexTheta][maxIndexRho] : int[][] -> the max value of rho
//img :                             SDL_Surface()

//add a vote to calculate degree
void vote(int x, int y, int maxRho, int maxIndexTheta, int maxIndexRho,
          int acc[maxIndexTheta][maxIndexRho],
          SDL_Surface *img);

//Input :
//*image :                          SDL_Surface -> the image to get angle

//calculate the degree we must rotate the image and return that degree
double find_angle(SDL_Surface *image);

//Input :
//*origine :                        SDL_Surface -> the image to rotate
//angle :                           float -> an angle in degree to rotate

//it apply the degree found to the image and return a rotated image
SDL_Surface *SDL_RotateImage(SDL_Surface *origine, float angle);

#endif
