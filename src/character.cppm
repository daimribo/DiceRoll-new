module;
#include <string>
#include <vector>
export module CharacterSheet;

export enum RACE_NAME{tiefling, yuanti};
enum ATTRIBUTES{stre, dex, con, intelli, wis, cha};
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
race tiefling_race{"tiefling", true, {cha, cha}};
race yuanti_race{"yuan-ti", true, {cha, cha, intelli}};
export std::vector <race> race_catalogue = {tiefling_race, yuanti_race};
export class Character
{
    public:
    RACE_NAME _race_name;
    race _race;
    attributes _attr;
    Character(const RACE_NAME race_name)
    {
        _race_name = race_name;
        Get_Race();
    }
    void Get_Race()
    {
        _race = race_catalogue[_race_name];
        Get_Attribute_Race_Bonus();
    }
    void Get_Attribute_Race_Bonus()
    {
        for(int i = 0; i < _race.attribute_bonus.size(); i++)
        {
            switch(_race.attribute_bonus[i])
            {
            case stre:
                _attr.strength ++;
                break;
            case dex:
                _attr.dexterity ++;
                break;
            case con:
                _attr.constitution ++;
                break;
            case intelli:
                _attr.intelligence ++;
                break;
            case wis:
                _attr.wisdom ++;
                break;
            case cha:
                _attr.charisma ++;
                break;
            }   
        }
    }
};