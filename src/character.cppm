module;
#include <string>
#include <vector>
export module CharacterSheet;
struct attributes
{
    int strength = 0;
    int dexterity = 0;
    int constitution = 0;
    int intelligence = 0;
    int wisdom = 0;
    int charisma = 0;
}
struct race
{
    std::string race_name;
    bool darkvision;
    std::vector <attributes> attribute_bonus;
};
export race tiefling{"tiefling", true, {charisma, charisma}};