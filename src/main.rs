mod character_sheet;

use character_sheet::Character;
use ratatui::{DefaultTerminal, Frame};

//TRY CREATING CHARACTER CREATION MENU TO HANDLE ATTRIBUTES!!!
//THEN LEARN HOW TO HANDLE JSON FEATURE READING

fn main() -> color_eyre::Result<()> {
    let mut new_character = Character::new("Josuke Higashikata", "dragonborn", "paladin");
    new_character.level_up();
    new_character.level_up();

    println!(
        "\n{}'s race is {}, level is {} and class is {} so {:?}",
        new_character.character_name,
        new_character.character_race.race_name,
        new_character.character_level,
        new_character.character_class.class_name,
        new_character.character_attr
    );
    println!(
        "\nThey are proficient in {:?} armor, in {:?} weapons and in {:?} tools.",
        new_character.character_class.armor_prof,
        new_character.character_class.weapon_prof,
        new_character.character_class.tool_prof
    );
    println!(
        "\nimmunities : {:?}, resistances : {:?}, They speak : {:?}",
        new_character.character_race.race_immunities,
        new_character.character_race.race_resistances,
        new_character.character_languages
    );
    println!(
        "\nThey can cast: {:?}, their race attacks are {:?}",
        new_character.character_race.race_spells, new_character.character_race.race_attacks
    );

    color_eyre::install()?;
    ratatui::run(app)?;
    Ok(())
}

fn app(terminal: &mut DefaultTerminal) -> std::io::Result<()> {
    loop {
        terminal.draw(render)?;
        if crossterm::event::read()?.is_key_press() {
            break Ok(());
        }
    }
}

fn render(frame: &mut Frame) {
    frame.render_widget("hello world", frame.area());
}
