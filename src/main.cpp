#include <ftxui/component/app.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <iostream>
#include <vector>

import CharacterSheet;
using namespace ftxui;

Element drawTitle(Screen &screen) {
    auto logo_color = color(Color::RGB(0, 0, 255));
    auto cell_full = text("█") | logo_color;
    auto cell_upper = text("▀") | logo_color;
    auto cell_down = text("▄") | logo_color;
    auto cell_empty = text(" ");

    std::vector<Element> rows = {vbox(cell_down, cell_down, cell_down),
                                 vbox(cell_full, cell_upper, cell_upper, cell_full)};

    auto art = vbox(rows);
    // looks bad
    return art;
}

int main() {

    auto app = App::TerminalOutput();

    auto place_holder_title = text("DICE ROLL") | center;

    std::vector<std::string> menu_options{"PLAY", "MULTIPLAYER", "CHARACTERS", "SETTINGS"};
    int selected = 0;

    auto menu_components = Menu(&menu_options, &selected);

    Character new_character("tiefling", "paladin");
    std::cout << "this character has " << new_character._attr.charisma << " charisma and "
              << new_character._attr.intelligence << " intelligence\n";
    for (int i = 0; i < new_character._race.features.size(); i++)
        std::cout << "feature " << i + 1 << " : " << new_character._race.features[i] << "\n";
    for (int i = 0; i < new_character._class.armor_prof.size(); i++)
        std::cout << "armor prof " << i + 1 << " : " << new_character._class.armor_prof[i] << "\n";
    for (int i = 0; i < 2; i++)
        std::cout << "sawing throw " << i + 1 << " : " << new_character._class.saving_throws[i]
                  << "\n";

    auto screen = Screen::Create(Dimension::Full(), Dimension::Full());
    Render(screen, place_holder_title);
    screen.Print();
    app.Loop(menu_components);

    return 0;
}