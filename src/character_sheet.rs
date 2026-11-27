use serde_json::Value;
use std::fs;

#[derive(Debug, Clone, Copy)]
enum AttributeType {
    STR,
    DEX,
    CONST,
    INT,
    WIS,
    CHAR,
}

#[derive(Debug, Clone, Copy, PartialEq, Eq, PartialOrd, Ord)]
pub enum DMGType {
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
    pub class_name: String,
    pub armor_prof: Vec<String>,
    pub weapon_prof: Vec<String>,
    pub tool_prof: Vec<String>,
    hit_die: u8,
    pub hit_points: u8,
    pub saving_throws: Vec<AttributeType>,
    pub class_features: Vec<String>,
}

pub struct Race {
    pub race_name: String,
    pub darkvision: bool,
    race_languages: Vec<String>,
    attribute_bonus: Vec<AttributeType>,
    pub race_immunities: Vec<DMGType>,
    pub race_resistances: Vec<DMGType>,
}

pub struct Character {
    pub character_name: String,
    pub character_race: Race,
    pub character_attr: Attributes,
    pub character_class: Class,
    pub character_languages: Vec<String>,
}

impl Character {
    pub fn new(character_name: &str, race_name: &str, class_name: &str) -> Self {
        let race = Self::get_race(race_name);
        let class = Self::get_class(class_name);

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
            character_languages: Vec::new(),
        };

        for i in 0..character.character_race.attribute_bonus.len() {
            character.get_attribute_bonus(character.character_race.attribute_bonus[i]);
        }
        for language in character.character_race.race_languages.clone() {
            character.character_languages.push(language);
        }

        character
    }

    fn get_attribute_bonus(&mut self, attr: AttributeType) {
        match attr {
            AttributeType::STR => self.character_attr.strength += 1,
            AttributeType::DEX => self.character_attr.dexterity += 1,
            AttributeType::CONST => self.character_attr.constitution += 1,
            AttributeType::INT => self.character_attr.intelligence += 1,
            AttributeType::WIS => self.character_attr.wisdom += 1,
            AttributeType::CHAR => self.character_attr.charisma += 1,
        }
    }

    fn match_dmgtype(dmg_type_str: &str) -> DMGType {
        let dmg_type = match dmg_type_str {
            "ACID" => DMGType::ACID,
            "COLD" => DMGType::COLD,
            "FIRE" => DMGType::FIRE,
            "FORCE" => DMGType::FORCE,
            "LIGHTNING" => DMGType::LIGHTNING,
            "NECROTIC" => DMGType::NECROTIC,
            "POISON" => DMGType::POISON,
            "PSYCHIC" => DMGType::PSYCHIC,
            "RADIANT" => DMGType::RADIANT,
            "THUNDER" => DMGType::THUNDER,
            "BLUDGEONING" => DMGType::BLUDGEONING,
            "PIERCING" => DMGType::PIERCING,
            "SLASHING" => DMGType::SLASHING,
            "SPELL" => DMGType::SPELL,
            _ => panic!("no dmg type!"),
        };
        return dmg_type;
    }

    fn match_attributetype(attribute_str: &str) -> AttributeType {
        let attribute_type = match attribute_str {
            "STR" => AttributeType::STR,
            "DEX" => AttributeType::DEX,
            "CONST" => AttributeType::CONST,
            "INT" => AttributeType::INT,
            "WIS" => AttributeType::WIS,
            "CHAR" => AttributeType::CHAR,
            _ => panic!("Unknown attribute"),
        };
        return attribute_type;
    }

    fn get_race(race_name: &str) -> Race {
        let race_data = fs::read_to_string("data/races.json").expect("Failed to read races.json");
        let feat_data = fs::read_to_string("data/feats.json").expect("Failed to read feats.json");

        let race_obj: Value = serde_json::from_str(&race_data).expect("Invalid JSON");
        let feat_obj: Value = serde_json::from_str(&feat_data).expect("Invalid JSON");
        let r = race_obj.get(race_name).unwrap();
        let f = feat_obj.get("race_feats").unwrap()[race_name]
            .as_object()
            .unwrap();

        let mut race_immunities: Vec<DMGType> = Vec::new();
        let mut race_resistances: Vec<DMGType> = Vec::new();

        for (feat_name, feat) in f {
            let feat_type = feat["feat_type"].as_str();

            if feat_type == Some("immunity") || feat_type == Some("resistance") {
                let a = feat["dmg_type"].as_str();
                let dmg_type = Self::match_dmgtype(a.unwrap());
                if feat_type == Some("immunity") {
                    race_immunities.push(dmg_type);
                    race_immunities.sort();
                    race_immunities.dedup();
                } else {
                    race_resistances.push(dmg_type);
                    race_resistances.sort();
                    race_resistances.dedup();
                }
            }
        }

        Race {
            race_name: race_name.to_string(),
            darkvision: r["darkvision"].as_bool().unwrap(),
            attribute_bonus: r["attributes"]
                .as_array()
                .unwrap()
                .iter()
                .map(|v| Self::match_attributetype(v.as_str().unwrap()))
                .collect(),
            race_immunities,
            race_resistances,
            race_languages: r["languages"]
                .as_array()
                .unwrap()
                .iter()
                .map(|v| v.as_str().unwrap().to_string())
                .collect(),
        }
    }

    fn get_class(class_name: &str) -> Class {
        let data = fs::read_to_string("data/classes.json").unwrap();
        let feat_data = fs::read_to_string("data/feats.json").expect("Failed to read feats.json");

        let class_obj: Value = serde_json::from_str(&data).unwrap();
        let feat_obj: Value = serde_json::from_str(&feat_data).expect("Invalid JSON");

        let c = class_obj.get(class_name).unwrap();
        let p = c.get("prof").unwrap();
        let f = feat_obj.get("class_feats").unwrap();

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
                .map(|v| Self::match_attributetype(v.as_str().unwrap()))
                .collect(),
            class_features: f[class_name]
                .as_object()
                .unwrap()
                .keys()
                .map(|v| v.to_string())
                .collect(),
        }
    }
}
