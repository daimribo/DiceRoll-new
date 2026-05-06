module;
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <json/json.h>
export module CharacterSheet;

enum ATTRIBUTES{STR, DEX, CONST, INT, WIS, CHAR};
enum SPELL_DMG{acid, cold, fire, force, lightning, necrotic, poison, psychic, radiant, thunder};
enum WEAPON_DMG{bludgeoning, piercing, slashing, spell};
struct attributes
{
    int strength = 0;
    int dexterity = 0;
    int constitution = 0;
    int intelligence = 0;
    int wisdom = 0;
    int charisma = 0;
};
struct character_class
{
    std::string class_name;
    std::vector<std::string> armor_prof;
    std::vector<std::string> weapon_prof;
    std::vector<std::string> tool_prof;
    int hit_die;
    int hit_points;
    int saving_throws [2];
};
struct race
{
    std::string race_name;
    bool darkvision;
    std::vector <ATTRIBUTES> attribute_bonus;
    std::vector <std::string> features;

};
export class Character
{
    public:
    std::string _race_name;
    std::string _class_name;
    race _race;
    attributes _attr;
    character_class _class;
    Character(const std::string race_name, const std::string class_name)
    {
        _race_name = race_name;
        Get_Race();
        _class_name = class_name;
        Get_Class();
    }

    void Get_Race()
    {
        Json::Value race_obj;
        Json::Value feat_obj;
        std::ifstream race_data("data/races.json");
        std::ifstream feat_data("data/feats.json");

        if (!race_data.is_open() || !feat_data.is_open()) {
        std::cerr << "FILE NOT OPENED\n";
        return;
        }

        Json::Reader reader;
        if (!reader.parse(race_data, race_obj) || !reader.parse(feat_data, feat_obj)) {
            std::cerr << "Failed to parse JSON:\n" << reader.getFormattedErrorMessages() << std::endl;
            return;
        }

        const Json::Value& r = race_obj[_race_name];
        const Json::Value& f = feat_obj["race_feats"][_race_name];

        if (r.isNull() && f.isNull()) {
            std::cerr << "Race not found\n";
            return;
        }

        _race.race_name = _race_name;
        _race.darkvision = r["darkvision"].asBool();

        for (const auto& attr : r["attributes"]){
            Get_Attribute_Race_Bonus(static_cast<ATTRIBUTES>(attr.asInt()));
        }
        _race.features = f.getMemberNames();
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
    void Get_Class()
    {
        Json::Value class_obj;
        std::ifstream class_data("data/character_classes.json");
        Json::Reader reader;
        reader.parse(class_data, class_obj);
        const Json::Value& c = class_obj[_class_name];

        _class.class_name = _class_name;
        _class.hit_die = c["hit_die"].asInt();

        for(const auto& armor_names : c["prof"]["armor"]){
            _class.armor_prof.push_back(armor_names.asString());
        }
        for(const auto& weapon_names : c["prof"]["weapons"]){
            _class.weapon_prof.push_back(weapon_names.asString());
        }
        for(const auto& tools : c["prof"]["tools"]){
            _class.tool_prof.push_back(tools.asString());
        }
        for(int i = 0; i < 2; i++){
        _class.saving_throws[i] = c["prof"]["saving_throws"][i].asInt();
        }
    }
};