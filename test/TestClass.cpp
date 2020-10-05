
#define LiquidCrystal_Test LiquidCrystal
#include "Common.cpp"

unittest(testingClassName) {
  LiquidCrystal_Test lcd(rs, enable, d4, d5, d6, d7);
  assertEqual("LiquidCrystal_CI", lcd.className());
}

unittest(getRows) {
  LiquidCrystal_Test lcd(rs, enable, d4, d5, d6, d7);
  assertEqual(1, lcd.getRows());
  lcd.begin(16, 2);
  assertEqual(2, lcd.getRows());
}

unittest(clearBuffer) {
  // create lcd object
  LiquidCrystal_Test lcd(rs, enable, d4, d5, d6, d7);
  // get currently displayed lines
  std::vector<std::string> lines = lcd.getLines();
  // verify that display contains 1 empty line
  assertEqual(1, lines.size());
  assertEqual(0, lines.at(0).length());

  // reset lcd to have two lines
  lcd.begin(16, 2);
  // verify that begin clears the display
  lines = lcd.getLines();
  // verify that display contains 2 empty lines
  assertEqual(2, lines.size());
  assertEqual(0, lines.at(0).length());
  assertEqual(0, lines.at(1).length());

  // write something to display
  lcd.print("hello world");

  // verify display not empty
  lines = lcd.getLines();
  assertEqual(2, lines.size());
  // assertEqual(11, lines.at(0).length());
  // assertEqual("hello world", lines.at(0));
  assertEqual(0, lines.at(1).length());

  // clear display
  lcd.clear();

  // verify display is empty
  lines = lcd.getLines();
  assertEqual(2, lines.size());
  assertEqual(0, lines.at(0).length());
  assertEqual(0, lines.at(1).length());
}

unittest(print_high) {

  //   size_t print(const String &s)                 { return write(s.c_str(), s.length()); }
  //   size_t print(const char* str)                 { return print(String(str)); }
  //   size_t print(char c)                          { return print(String(c)); }
  //   size_t print(unsigned char b, int base = DEC) { return print(String(b, base)); }
  //   size_t print(int n,           int base = DEC) { return print(String(n, base)); }

  std::vector<std::string> lines;
  // create lcd object
  LiquidCrystal_Test lcd(rs, enable, d4, d5, d6, d7);
  // reset lcd to have two lines
  lcd.begin(16, 2);
  // write something to display
  lcd.print("C String");
  lines = lcd.getLines();
  assertEqual(2, lines.size());
  assertEqual(11, lines.at(0).length());
  assertEqual("C String", lines.at(0));
  assertEqual(0, lines.at(1).length());
  lcd.clear();

  
  lcd.print(String("Test String"));
  lines = lcd.getLines();
  assertEqual(2, lines.size());
  assertEqual(11, lines.at(0).length());
  assertEqual("Test String", lines.at(0));
  assertEqual(0, lines.at(1).length());
  lcd.clear();

  unsigned char testUnsignedChar = "
  lcd.print(testUnsignedChar, DEC);
  lines = lcd.getLines();
  assertEqual(2, lines.size());
  assertEqual(11, lines.at(0).length());
  assertEqual("Test String", lines.at(0));
  assertEqual(0, lines.at(1).length());
  lcd.clear();

  lcd.print(String("Test String"));
  lines = lcd.getLines();
  assertEqual(2, lines.size());
  assertEqual(11, lines.at(0).length());
  assertEqual("Test String", lines.at(0));
  assertEqual(0, lines.at(1).length());
  lcd.clear();

  lcd.print(String("Test String"));
  lines = lcd.getLines();
  assertEqual(2, lines.size());
  assertEqual(11, lines.at(0).length());
  assertEqual("Test String", lines.at(0));
  assertEqual(0, lines.at(1).length());
  lcd.clear();

}



unittest_main()
