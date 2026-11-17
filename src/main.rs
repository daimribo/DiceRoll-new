mod CharacterSheet;

use CharacterSheet::Character;

fn main() {
    let new_character = Character::new("Josuke Higashikata", "tiefling", "paladin");

    println!(
        "Character name is: {}, Character's darkvision is: {}, attributes: {:?}",
        new_character.character_name,
        new_character.character_race.darkvision,
        new_character.character_attr
    );
}
