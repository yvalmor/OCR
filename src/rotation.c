void imageRotation(SDL_Surface *image, double angle)
{
    int continuer = 1;
    int pastTime = 0;
    int present = 0;
    SDL_Rect rect;

    while(continuer)
    {
        SDL_PollEvent(&event);
        if (event.type == SDL_QUIT)
        {
            continuer = 0;
            break;
        }
        present = SDL_GetTicks();
        if (present - pastTime > TIME)
        {
            angle += 2;
            pastTime = present;
        }
        else
        {
            SDL_Delay(TIME - (present - pastTime));
            SDL_FillRect(image, NULL, SDL_MAPRGB(image->format,255,255,255))
            rotation = rotozoomSurface(image,angle,1.0,1);

            rect.x = 200 - rotation->w / 2;
            rect.y = 200 - rotation->h / 2;
        }
    }
}
