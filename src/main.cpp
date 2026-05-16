#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
import CharacterSheet;
int main()
{
    bool success = false;
    SDL_Event test_event;
    SDL_Init(SDL_INIT_EVENTS);
    SDL_Window* window = SDL_CreateWindow("DiceRoll", 500, 500, NULL);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);
    uint8_t old_time = SDL_GetTicks();
    while(!success)
    {
        SDL_zero(test_event);
        while(SDL_PollEvent(&test_event))
        {
            if(test_event.type == SDL_EVENT_QUIT)
                success = true;
        }
        SDL_SetRenderDrawColor(renderer, 50, 5, 255, 255);
        SDL_RenderClear(renderer);
    }

    Character new_character("tiefling", "paladin");
    std::cout<<"this character has "<<new_character._attr.charisma<<" charisma and "<<new_character._attr.intelligence<<" intelligence\n";
    for(int i = 0; i< new_character._race.features.size(); i++)
        std::cout<<"feature "<<i+1<<" : "<<new_character._race.features[i]<<"\n";
    for(int i = 0; i < new_character._class.armor_prof.size(); i++)
        std::cout<<"armor prof "<<i+1<<" : "<<new_character._class.armor_prof[i]<<"\n";
    for(int i = 0; i < 2; i++)
        std::cout<<"sawing throw "<<i+1<<" : "<<new_character._class.saving_throws[i]<<"\n";
    return 0;
    SDL_Quit();
}