#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include "ai.h"
#include "circles.h"
#include <SDL2/SDL.h>

void DrawO(SDL_Renderer *renderer, int tri_x, int tri_y)
{
    SDL_SetRenderDrawColor(renderer, 3, 123, 252, 255);
    SDL_RenderFillCircle(renderer, 200.0 * (((float)tri_x) + 0.5), 200.0 * (((float)tri_y) + 0.5), 75);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillCircle(renderer, 200.0 * (((float)tri_x) + 0.5), 200.0 * (((float)tri_y) + 0.5), 55);
}

void DrawX(SDL_Renderer *renderer, int tri_x, int tri_y)
{
    SDL_SetRenderDrawColor(renderer, 252, 3, 61, 255);
    SDL_RenderFillCross(renderer, 200.0 * (((float)tri_x) + 0.5), 200.0 * (((float)tri_y) + 0.5), 70, 20);
}

void DrawGrid(SDL_Renderer *renderer)
{
    struct SDL_Rect horiz;
    horiz.x = 0;
    horiz.y = 195;
    horiz.w = 600;
    horiz.h = 10;
    struct SDL_Rect vert;
    vert.x = 195;
    vert.y = 0;
    vert.w = 10;
    vert.h = 600;
    for (int i = 0; i < 2; ++i)
    {
        SDL_RenderFillRect(renderer, &horiz);
        SDL_RenderFillRect(renderer, &vert);
        horiz.y += 200;
        vert.x += 200;
    }
}

bool full_board(char *board)
{
    for (int i = 0; i < 9; ++i)
    {
        if (board[i] == ' ')
        {
            return false;
        }
    }
    return true;
}

bool tictactoe(SDL_Renderer *rend, SDL_Window *window)
{
    SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
    SDL_RenderClear(rend);
    SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
    DrawGrid(rend);

    char board[] = "         ";
    int eval = 0;
    int ai_move = minimax(board, 'x', &eval);

    board[ai_move] = 'x';
    printf("EVAL: %d\n", eval);
    DrawX(rend, ai_move % 3, ai_move / 3);
    SDL_RenderPresent(rend);

    SDL_Event event;
    while (1)
    {
        if (!SDL_PollEvent(&event))
        {
            continue;
        }
        if (event.type == SDL_QUIT)
        {
            SDL_DestroyRenderer(rend);

            // Close and destroy the window
            SDL_DestroyWindow(window);

            // Clean up
            SDL_Quit();
            return false;
        }
        else if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            int x, y, tri_x, tri_y;
            SDL_GetMouseState(&x, &y);
            tri_x = x / 200;
            tri_y = y / 200;
            if (board[tri_x + tri_y * 3] != ' ')
            {
                continue;
            }
            printf("PRESSED: %d, %d\n", x, y);
            DrawO(rend, tri_x, tri_y);
            board[tri_x + tri_y * 3] = 'o';
            int eval = 0;
            int ai_move = minimax(board, 'x', &eval);
            board[ai_move] = 'x';
            printf("EVAL: %d\n", eval);
            DrawX(rend, ai_move % 3, ai_move / 3);
            SDL_RenderPresent(rend);
            if (detect_win(board, &eval) || full_board(board))
            {
                SDL_Delay(1000);
                return true;
            }
        }
    }
}

int main(int argc, char *argv[])
{
    int WIDTH = 600;
    int HEIGHT = 600;


    //https://wiki.libsdl.org/SDL_CreateWindow
    SDL_Window *window; // Declare a pointer

    SDL_Init(SDL_INIT_VIDEO); // Initialize SDL2

    // Create an application window with the following settings:
    window = SDL_CreateWindow(
        "Tic-Tac-Toe",           // window title
        SDL_WINDOWPOS_UNDEFINED, // initial x position
        SDL_WINDOWPOS_UNDEFINED, // initial y position
        WIDTH,                   // width, in pixels
        HEIGHT,                  // height, in pixels
        0                        // flags - see below
    );

    // Check that the window was successfully created
    if (window == NULL)
    {
        // In the case that the window could not be made...
        printf("Could not create window: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Renderer *rend = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_RenderSetIntegerScale(rend, SDL_TRUE);
    // A basic main loop to prevent blocking
    while (tictactoe(rend, window));
    return 0;
}
