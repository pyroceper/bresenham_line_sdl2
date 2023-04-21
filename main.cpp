#include <iostream>
#include <string>
#include <SDL2/SDL.h>

const int WIDTH = 640;
const int HEIGHT = 480;

void DrawLine(SDL_Renderer *renderer, int x1, int y1, int x2, int y2, SDL_Color color)
{
    //https://en.wikipedia.org/wiki/Bresenham's_line_algorithm

    int dx = abs(x2 - x1);
    int sx = x1 < x2 ? 1 : -1;
    int dy = -abs(y2 - y1);
    int sy = y1 < y2 ? 1 : -1;
    int error = dx + dy;
    int e2 = 0;


    while(1)
    {
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_RenderDrawPoint(renderer, x1, y1);

        if(x1 == x2 && y1 == y2) break;
        e2 = error << 1;
        if(e2 >= dy)
        {
            if(x1 == x2) break;
            error = error + dy;
            x1 = x1 + sx;
        }
        if(e2 <= dx)
        {
            if(y1 == y2) break;
            error = error + dx;
            y1 = y1 + sy;
        }
    }
}

int main(int argc, char * argv[])
{
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout<<"[Error] SDL_Init "<<SDL_GetError()<<std::endl;
        exit(1);
    }

    std::string window_name = "Bresenham's Line Algorithm";
    SDL_Window *window = SDL_CreateWindow(window_name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, 0);
    if(window == nullptr)
    {
        std::cout<<"[Error] SDL_CreateWindow"<<SDL_GetError()<<std::endl;
        exit(1);
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(renderer == nullptr)
    {
        std::cout<<"[Error] SDL_CreateRenderer"<<SDL_GetError()<<std::endl;
        exit(1);
    }


    SDL_Event event;
    while(1)
    {
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                    goto clean;
            }
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);//teal
        SDL_RenderClear(renderer);
        

        DrawLine(renderer, 30, 50, 200, 500, {50, 0, 50, 0});
        DrawLine(renderer, 130, 33, 130, 77, {255, 50, 50, 0});

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    clean:
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
        SDL_DestroyWindow(window);
        window = nullptr;
        SDL_Quit();
        

    return 0;
}
