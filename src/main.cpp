#include <iostream>
import CharacterSheet;
int main()
{
    Character new_character("tiefling", "paladin");
    std::cout<<"this character has "<<new_character._attr.charisma<<" charisma and "<<new_character._attr.intelligence<<" intelligence\n";
    for(int i = 0; i< new_character._race.features.size(); i++)
        std::cout<<"feature "<<i+1<<" : "<<new_character._race.features[i]<<"\n";
    for(int i = 0; i < new_character._class.armor_prof.size(); i++)
        std::cout<<"armor prof "<<i+1<<" : "<<new_character._class.armor_prof[i]<<"\n";
    for(int i = 0; i < 2; i++)
        std::cout<<"sawing throw "<<i+1<<" : "<<new_character._class.saving_throws[i]<<"\n";
    return 0;
}