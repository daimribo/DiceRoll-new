use serde_json::Value;
use std::fs;

#[derive(Debug, Clone, Copy)]
enum ATTRIBUTES {
    STR,
    DEX,
    CONST,
    INT,
    WIS,
    CHAR,
}
enum SPELLDMG {
    ACID,
    COLD,
    FIRE,
    FORCE,
    LIGHTNING,
    NECROTIC,
    POISON,
    PSYCHIC,
    RADIANT,
    THUNDER,
}
enum WEAPONDMG {
    BLUDGEONING,
    PIERCING,
    SLASHING,
    SPELL,
}

#[derive(Debug)]
pub struct Attributes {
    strength: u8,
    dexterity: u8,
    constitution: u8,
    intelligence: u8,
    wisdom: u8,
    charisma: u8,
}

pub struct Class {
    class_name: String,
    armor_prof: Vec<String>,
    weapon_prof: Vec<String>,
    tool_prof: Vec<String>,
    hit_die: u8,
    hit_points: u8,
    saving_throws: Vec<ATTRIBUTES>,
}

pub struct Race {
    race_name: String,
    pub darkvision: bool,
    attribute_bonus: Vec<ATTRIBUTES>,
    //features : vec<&str>
}

pub struct Character {
    pub character_name: String,
    pub character_race: Race,
    pub character_attr: Attributes,
    pub character_class: Class,
}

impl Character {
    pub fn new(character_name: &str, race_name: &str, class_name: &str) -> Self {
        let race = Self::getRace(race_name);
        let class = Self::getClass(class_name);

        let attr = Attributes {
            strength: 0,
            dexterity: 0,
            constitution: 0,
            intelligence: 0,
            wisdom: 0,
            charisma: 0,
        };

        let mut character = Self {
            character_name: character_name.to_string(),
            character_race: race,
            character_attr: attr,
            character_class: class,
        };

        for i in 0..character.character_race.attribute_bonus.len() {
            character.getAttributeBonus(character.character_race.attribute_bonus[i]);
        }
        character
    }

    fn getAttributeBonus(&mut self, attr: ATTRIBUTES) {
        match attr {
            ATTRIBUTES::STR => self.character_attr.strength += 1,
            ATTRIBUTES::DEX => self.character_attr.dexterity += 1,
            ATTRIBUTES::CONST => self.character_attr.constitution += 1,
            ATTRIBUTES::INT => self.character_attr.intelligence += 1,
            ATTRIBUTES::WIS => self.character_attr.wisdom += 1,
            ATTRIBUTES::CHAR => self.character_attr.charisma += 1,
        }
    }

    fn getRace(race_name: &str) -> Race {
        let data = fs::read_to_string("data/races.json").expect("Failed to read races.json");

        let race_obj: Value = serde_json::from_str(&data).expect("Invalid JSON");
        let r = race_obj.get(race_name).unwrap();

        Race {
            race_name: race_name.to_string(),
            darkvision: r["darkvision"].as_bool().unwrap(),
            attribute_bonus: r["attributes"]
                .as_array()
                .unwrap()
                .iter()
                .map(|v| match v.as_str().unwrap() {
                    "STR" => ATTRIBUTES::STR,
                    "DEX" => ATTRIBUTES::DEX,
                    "CONST" => ATTRIBUTES::CONST,
                    "INT" => ATTRIBUTES::INT,
                    "WIS" => ATTRIBUTES::WIS,
                    "CHAR" => ATTRIBUTES::CHAR,
                    _ => panic!("Unknown attribute"),
                })
                .collect(),
        }
    }

    fn getClass(class_name: &str) -> Class {
        let data = fs::read_to_string("data/classes.json").unwrap();
        let class_obj: Value = serde_json::from_str(&data).unwrap();

        let c = class_obj.get(class_name).unwrap();
        let p = c.get("prof").unwrap();

        Class {
            class_name: class_name.to_string(),

            armor_prof: p["armor"]
                .as_array()
                .unwrap()
                .iter()
                .map(|v| v.as_str().unwrap().to_string())
                .collect(),

            weapon_prof: p["weapons"]
                .as_array()
                .unwrap()
                .iter()
                .map(|v| v.as_str().unwrap().to_string())
                .collect(),

            tool_prof: p["tools"]
                .as_array()
                .unwrap()
                .iter()
                .map(|v| v.as_str().unwrap().to_string())
                .collect(),

            hit_die: c["hit_die"].as_u64().unwrap() as u8,
            hit_points: c["hit_die"].as_u64().unwrap() as u8,

            saving_throws: p["saving_throws"]
                .as_array()
                .unwrap()
                .iter()
                .map(|v| match v.as_str().unwrap() {
                    "STR" => ATTRIBUTES::STR,
                    "DEX" => ATTRIBUTES::DEX,
                    "CONST" => ATTRIBUTES::CONST,
                    "INT" => ATTRIBUTES::INT,
                    "WIS" => ATTRIBUTES::WIS,
                    "CHAR" => ATTRIBUTES::CHAR,
                    _ => panic!("Unknown attribute"),
                })
                .collect(),
        }
    }
}
