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

    std::vector<Element> rows = {hbox(cell_down, cell_down, cell_down),
                                 hbox(cell_full, cell_upper, cell_upper, cell_full)};

    auto art = vbox(rows);
    // looks bad
    return art;
}

int main() {

    auto screen = ftxui::Screen::Create(ftxui::Dimension::Full(), ftxui::Dimension::Full());
    ftxui::Render(screen, drawTitle(screen));

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
    // std::cout<<"direction "<<direction<<std::endl;
    screen.Print();

    return 0;
}