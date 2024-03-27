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

// use essa função pra desenhar uma imagem na tela
void DrawImage(int x, int y, SDL_Surface *image)
{
    SDL_Rect mover;
    mover.x = x;
    mover.y = y;

    SDL_BlitSurface(image, NULL, tela, &mover);
}

SDL_Surface *iconImage = NULL;
SDL_Surface *dayImage = NULL;
SDL_Surface *nightImage = NULL;



// use essa função pra carregar arquivos
// nota: essa função só deve ser chamada no começo do programa
void LoadFiles()
{
    dayImage = SDL_LoadBMP("gfx/day.bmp");
    nightImage = SDL_LoadBMP("gfx/night.bmp");
}

// use essa função pra fechar arquivos
// nota: essa função só deve ser chamada no final do programa
void CloseFiles()
{
    SDL_FreeSurface(iconImage);
    SDL_FreeSurface(dayImage);
    SDL_FreeSurface(nightImage);
}


void DrawBackground(int CurrentTime)
{
    switch(CurrentTime)
    {
        case 0: DrawImage(0,0,dayImage); break;
        case 1: DrawImage(0,0,nightImage); break;
        default: ;break;
    }
}

int main(int argc, char*args[])
{
SDL_Init(SDL_INIT_EVERYTHING);
SDL_putenv("SDL_VIDEO_WINDOW_POS=center");
iconImage = SDL_LoadBMP("gfx/icon.bmp");
SDL_WM_SetIcon(iconImage, NULL);
tela = SDL_SetVideoMode(screen_width,screen_height,screen_bpp,SDL_SWSURFACE);
SDL_WM_SetCaption("Flappy bird Clone", NULL);

LoadFiles();

int CurrentTime = rand() % 2;

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

    DrawBackground(CurrentTime);

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
