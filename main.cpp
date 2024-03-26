#include <SDL.h>

SDL_Event evento;
SDL_Surface *tela = NULL;
bool executando = true;

const int screen_width = 288;
const int screen_height = 512;
const int screen_bpp = 32;

// para o framerate
Uint32 start = 0;
const int fps = 30;
const int framerate =  1000/fps;

SDL_Surface *iconImage = NULL;

// use essa função pra carregar arquivos
// nota: essa função só deve ser chamada no começo do programa
void LoadFiles()
{
}

// use essa função pra fechar arquivos
// nota: essa função só deve ser chamada no final do programa
void CloseFiles()
{
    SDL_FreeSurface(iconImage);
}

int main(int argc, char*args[])
{
SDL_Init(SDL_INIT_EVERYTHING);
SDL_putenv("SDL_VIDEO_WINDOW_POS=center");
iconImage = SDL_LoadBMP("gfx/icon.bmp");
SDL_WM_SetIcon(iconImage, NULL);
tela = SDL_SetVideoMode(screen_width,screen_height,screen_bpp,SDL_SWSURFACE);
SDL_WM_SetCaption("Flappy bird Clone", NULL);

// game loop
while(executando)
{
    start = SDL_GetTicks();
    while(SDL_PollEvent(&evento))
    {
        // clicou no x da janela
        if(evento.type == SDL_QUIT)
        {
            executando = false; // fecha o programa
        }
    }

    SDL_FillRect(tela, 0, 0xffffff);
    SDL_Flip(tela);
    if(framerate > (SDL_GetTicks()-start))
    {
        SDL_Delay(framerate - (SDL_GetTicks()-start));
    }
}


CloseFiles();
SDL_Quit();
return 0;
}
