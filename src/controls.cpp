#include <SDL.h>
#include "structs.h"

void eventCheck(bool &end, bool &restart){
    SDL_Event gameEvent;
    while(SDL_PollEvent(&gameEvent)){
        switch(gameEvent.type){
            case SDL_QUIT:
                end = true;
            break;
            case SDL_KEYDOWN:
                switch(gameEvent.key.keysym.sym){
                    case SDLK_r:
                        restart = true;
                    break;
                    case SDLK_ESCAPE:
                        end = true;
                    break;
                }
            break;
        }
    }
}

Mouse getMouseXY(Mouse mouse){
    SDL_GetMouseState(&mouse.x, &mouse.y);
    if(mouse.y < 95){
        mouse.y = 95;
    } else if (mouse.y > 530){
        mouse.y = 530;
    }
    return {mouse.x, mouse.y};
}
