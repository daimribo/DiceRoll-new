mod character_sheet;

use character_sheet::Character;
use ratatui::{DefaultTerminal, Frame};

//TRY CREATING CHARACTER CREATION MENU TO HANDLE ATTRIBUTES!!!
//THEN LEARN HOW TO HANDLE JSON FEATURE READING

fn main() -> color_eyre::Result<()> {
    let new_character = Character::new("Josuke Higashikata", "yuanti", "paladin");

    println!(
        "\n{}'s race is {} and class is {} so {:?}",
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
    println!(
        "immunities : {:?}, resistances : {:?}",
        new_character.character_race.race_immunities, new_character.character_race.race_resistances
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
