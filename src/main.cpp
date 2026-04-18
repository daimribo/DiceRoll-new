#include <iostream>
import CharacterSheet;
int main()
{
    Character new_character(tiefling);
    std::cout<<"this character has "<<new_character._attr.charisma<<" charisma and "<<new_character._attr.strength<<"strength\n";
    return 0;
}