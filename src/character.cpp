module;
#include <string>
export module CharacterSheet;
export struct race
{
    std::string race_name;
    bool darkvision;
};
export race tiefling{"tiefling", true};