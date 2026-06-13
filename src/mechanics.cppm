module;
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <vector>

export module Mechanics;

void direction_user_should_move(int& x_axis, int& y_axis)
{
    const bool *key_states = SDL_GetKeyboardState(NULL);

    if (key_states[SDL_SCANCODE_W]) {
        y_axis += 1;
        SDL_Delay(100);
    } 
    if (key_states[SDL_SCANCODE_S]) {
        y_axis -= 1;
        SDL_Delay(100);
    }
    if (key_states[SDL_SCANCODE_A]) {
        x_axis -= 1;
        SDL_Delay(100);
    } 
    if (key_states[SDL_SCANCODE_D]) {
        x_axis += 1;
        SDL_Delay(100);
    }
}

export void window_actions(std::vector <void(*)()> actions)
{
    bool success = false;
    SDL_Event test_event;
    int direction = 0;
    SDL_Init(SDL_INIT_EVENTS);
    SDL_Window* window = SDL_CreateWindow("DiceRoll", 500, 500, NULL);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);
    while(!success){
        SDL_zero(test_event);
        while(SDL_PollEvent(&test_event))
        {
            if(test_event.type == SDL_EVENT_QUIT)
                success = true;
        }
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        SDL_RenderPresent(renderer);
        //for(int i = 0;)
    }
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}