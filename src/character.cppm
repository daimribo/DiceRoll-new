module;
#include <string>
#include <vector>
export module CharacterSheet;
export enum RACE_NAME{tiefling};
export enum ATTRIBUTES{stre, dex, con, intelli, wis, cha};
struct attributes
{
    int strength = 0;
    int dexterity = 0;
    int constitution = 0;
    int intelligence = 0;
    int wisdom = 0;
    int charisma = 0;
};
struct race
{
    std::string race_name;
    bool darkvision;
    std::vector <ATTRIBUTES> attribute_bonus;

    bool operator==(const race& other) const
    {
        bool is_equal = true;
        if(race_name != other.race_name)
            is_equal = false;
        if(darkvision != other.darkvision)
            is_equal = false;
        for(int i = 0; i < attribute_bonus.size(); i++)
        {
            if(attribute_bonus[i] != other.attribute_bonus[i])
                is_equal = false;
        }
        return is_equal;
    }
};
race tiefling_race{"tiefling", true, {cha, cha}};
std::vector <race> race_catalogue = {tiefling_race};
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
        Get_Attribute_Race_Bonus();
    }

    void Get_Race()
    {
        switch(_race_name)
        {
            case tiefling:
                _race = race_catalogue[0];
                break;
        }
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