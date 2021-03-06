// High-Level Tests: testing LiquidCrystal_CI

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

// based on Autoscroll.ino example
unittest(autoscroll_high) {
  LiquidCrystal_Test lcd(rs, enable, d4, d5, d6, d7);
  assertFalse(lcd.isAutoscroll());
  lcd.begin(16, 2);
  // get currently displayed lines
  std::vector<std::string> lines;
  // set the cursor to (0,0):
  lcd.setCursor(0, 0);
  // print from 0 to 9:
  for (int thisChar = 0; thisChar < 10; thisChar++) {
    lcd.print(thisChar);
    delay(500);
  }
  // verify display not empty
  lines = lcd.getLines();
  assertEqual(2, lines.size());
  // uncomment when print works
  // assertEqual(10, lines.at(0).length());
  // assertEqual("0123456789", lines.at(0));
  assertEqual(0, lines.at(1).length());

  // set the cursor to (16,1):
  lcd.setCursor(16, 1);
  // set the display to automatically scroll:
  lcd.autoscroll();
  assertTrue(lcd.isAutoscroll());
  // print from 0 to 9:
  std::string zeroTo9 = "0123456789";
  std::string text = "                ";

  for (int i = 0; i < 10; i++) {
    // send character to screen
    lcd.print(i);

    // calculate expected value for second line
    std::string expected = text.substr(0, 15 - i);
    expected += zeroTo9;
    expected = expected.substr(0, 16);

    // compare expected to actual
    lines = lcd.getLines();
    // uncomment when print works
    // assertEqual(16, lines.at(1).length());
    // assertEqual(expected, lines.at(1));

    delay(500);
  }
  // turn off automatic scrolling
  lcd.noAutoscroll();
  assertFalse(lcd.isAutoscroll());

  // clear screen for the next loop:
  lcd.clear();
}

unittest(clear_high) {
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

unittest(createChar_high) {
  // Setup display
  LiquidCrystal_Test lcd(rs, enable, d4, d5, d6, d7);

  // create some chars
  byte smiley[8] = {B00000, B10001, B00000, B00000, B10001, B01110, B00000};
  byte spaceship[8] = {B00000, B00100, B01110, B01110,
                       B01110, B01010, B00000, B00000};
  lcd.createChar(0, smiley);
  lcd.createChar(4, spaceship);

  // check they were created where we expected them
  byte *character0 = lcd.getCustomCharacter(0);
  byte *character4 = lcd.getCustomCharacter(4);
  for (int bite = 0; bite < 8; bite++) {
    assertEqual(smiley[bite], *(character0 + bite));
    assertEqual(spaceship[bite], *(character4 + bite));
  }
}

unittest(write_high) {
  // create lcd object
  LiquidCrystal_Test lcd(rs, enable, d4, d5, d6, d7);
  // TODO
}

unittest(print_high) {
  // create lcd object
  LiquidCrystal_Test lcd(rs, enable, d4, d5, d6, d7);
  // TODO
}

unittest(setCursor_high) {
  // create lcd object
  LiquidCrystal_Test lcd(rs, enable, d4, d5, d6, d7);

  // reset lcd to have two lines
  lcd.begin(16, 2);

  // verify cursor is at beginning
  assertEqual(0, lcd.getCursorCol());
  assertEqual(0, lcd.getCursorRow());

  // set cursor to second line
  lcd.setCursor(0, 1);
  // verify cursor position
  assertEqual(0, lcd.getCursorCol());
  assertEqual(1, lcd.getCursorRow());

  // set cursor to middle of first line
  lcd.setCursor(4, 0);
  // verify cursor position
  assertEqual(4, lcd.getCursorCol());
  assertEqual(0, lcd.getCursorRow());
}

unittest(home_high) {
  // create lcd object
  LiquidCrystal_Test lcd(rs, enable, d4, d5, d6, d7);
  lcd.begin(16, 2);

  // Go home
  lcd.home();
  // Check Cursor is at upper-left
  assertEqual(0, lcd.getCursorCol());
  assertEqual(0, lcd.getCursorRow());

  // Set Cursor to new location
  lcd.setCursor(3, 1);
  // Check Cursor Location
  assertEqual(3, lcd.getCursorCol());
  assertEqual(1, lcd.getCursorRow());

  // Return Home
  lcd.home();
  // Check Cursor is at upper-left
  assertEqual(0, lcd.getCursorCol());
  assertEqual(0, lcd.getCursorRow());

  /* When print works
  // Print message
  lcd.print("Test line");
  //Check Cursor Location
  assertNotEqual(0, getCursorCol());;

  // Return Home
  lcd.home();
  // Check Cursor is at upper-left
  assertEqual(0, lcd.getCursorCol());
  assertEqual(0, lcd.getCursorRow());
  */
}

unittest(display_high) {
  LiquidCrystal_Test lcd(rs, enable, d4, d5, d6, d7);

  bool isDisplay = lcd.isDisplay();

  // default
  assertEqual(0, isDisplay);

  // test is display on
  lcd.display();
  isDisplay = lcd.isDisplay();
  assertEqual(1, isDisplay);

  // test is display off
  lcd.noDisplay();
  isDisplay = lcd.isDisplay();
  assertEqual(0, isDisplay);
}

unittest(blink_high) {
  // create lcd object
  LiquidCrystal_Test lcd(rs, enable, d4, d5, d6, d7);

  bool blinking = lcd.isBlink();

  // check default - noBlink
  assertFalse(blinking);

  // check blink function
  lcd.blink();
  blinking = lcd.isBlink();
  assertTrue(blinking);

  // check noBlink function
  lcd.noBlink();
  blinking = lcd.isBlink();
  assertFalse(blinking);
}

unittest(cursor_high) {
  // create lcd object
  LiquidCrystal_Test lcd(rs, enable, d4, d5, d6, d7);

  // assert startup no cursor is set
  assertEqual(false, lcd.isCursor());

  // check cursor function
  lcd.cursor();
  assertEqual(true, lcd.isCursor());

  // check noCursor function
  lcd.noCursor();
  assertEqual(false, lcd.isCursor());
}

unittest_main()
