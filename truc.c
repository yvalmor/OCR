
                SDL_Surface *surface;
                surface = SDL_CreateRGBSurface(0, new_img->cols, new_img->rows,
                                               32, 0, 0, 0, 0);

                for (unsigned int x = 0; x < (unsigned int)new_img->cols; x++)
                    for (unsigned int y = 0; y < (unsigned int)new_img->rows; y++)
                    {
                        int val = new_img->img[y * new_img->cols + x];
                        Uint32 value = SDL_MapRGB(surface->format, val*255, val*255, val*255);
                        put_pixel(surface, x, y, value);
                    }

                int x1 = cpt/1000;
                int x2 = cpt%1000/100;
                int x3 = cpt%100/10;
                int x4 = cpt%10;

                char name[20] = {'l','e','t','t','e','r','s',
                    (char) x1+'0', (char) x2+'0', (char) x3+'0', (char) x4+'0', 
                    '.','b','m','p'};
                cpt++;

                SDL_SaveBMP(surface, name);
                SDL_FreeSurface(surface);
