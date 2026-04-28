#include <iostream>
import CharacterSheet;
int main()
{
    Character new_character("yuanti");
    std::cout<<"this character has "<<new_character._attr.charisma<<" charisma and "<<new_character._attr.intelligence<<" intelligence\n";
    for(int i = 0; i< new_character._race.features.size(); i++)
        std::cout<<"feature: "<<i+1<<" "<<new_character._race.features[i]<<"\n";
    return 0;
}