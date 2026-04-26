module;
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <json/json.h>
export module CharacterSheet;

enum ATTRIBUTES{STR, DEX, CONST, INT, WIS, CHAR};
enum FEATURE_TYPES{immunities, resistance, weakness, };
struct attributes
{
    int strength = 0;
    int dexterity = 0;
    int constitution = 0;
    int intelligence = 0;
    int wisdom = 0;
    int charisma = 0;
};
/*struct feat
{
    
};
struct role
{
    std::string role_name;
    int 
};*/
struct race
{
    std::string race_name;
    bool darkvision;
    std::vector <ATTRIBUTES> attribute_bonus;

};
//race tiefling_race{"tiefling", true, {cha, cha}};
//race yuanti_race{"yuan-ti", true, {cha, cha , intelli}};
//export std::vector <race> race_catalogue = {tiefling_race, yuanti_race};
export class Character
{
    public:
    std::string _race_name;
    race _race;
    attributes _attr;
    Character(const std::string race_name)
    {
        _race_name = race_name;
        Get_Race();
    }

    void Get_Race()
    {
        Json::Value race_obj;
        std::ifstream race_data("data/races.json");

        if (!race_data.is_open()) {
        std::cerr << "FILE NOT OPENED\n";
        return;
        }

        Json::Reader reader;
        if (!reader.parse(race_data, race_obj)) {
            std::cerr << "Failed to parse JSON:\n" << reader.getFormattedErrorMessages() << std::endl;
            return;
        }

        const Json::Value& r = race_obj[_race_name];

        if (r.isNull()) {
            std::cerr << "Race not found\n";
            return;
        }

        _race.race_name = _race_name;
        _race.darkvision = r["darkvision"].asBool();

        for (const auto& attr : r["attributes"])
        {
            Get_Attribute_Race_Bonus(
                static_cast<ATTRIBUTES>(attr.asInt())
            );
        }
    }
    void Get_Attribute_Race_Bonus(ATTRIBUTES attr)
    {
        switch(attr)
        {
        case STR:
            _attr.strength ++;
            break;
        case DEX:
            _attr.dexterity ++;
            break;
        case CONST:
            _attr.constitution ++;
            break;
        case INT:
            _attr.intelligence ++;
            break;
        case WIS:
            _attr.wisdom ++;
            break;
        case CHAR:
            _attr.charisma ++;
            break;
        default:
            std::cerr<<"Nonexistent attributes were assigned to the race\n";
        }   
    }
};