#include <gtest/gtest.h>

import CharacterSheet;
TEST(Character_Creation_Tests, Get_Race_Test)
{
    Character test_character_1(tiefling);
    ASSERT_EQ(test_character_1._race.race_name, "tiefling");
    Character test_character_2(yuanti);
    ASSERT_EQ(test_character_2._race.race_name, "yuan-ti");
}