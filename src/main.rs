mod character_sheet;

use character_sheet::Character;

fn main() {
    let new_character = Character::new("Josuke Higashikata", "tiefling", "paladin");

    println!(
        "{}'s race is {} and class is {} so {:?}\n",
        new_character.character_name,
        new_character.character_race.race_name,
        new_character.character_class.class_name,
        new_character.character_attr
    );
    println!(
        "They are proficient in {:?} armor, in {:?} weapons and in {:?} tools.",
        new_character.character_class.armor_prof,
        new_character.character_class.weapon_prof,
        new_character.character_class.tool_prof
    );
    println!("");
}
