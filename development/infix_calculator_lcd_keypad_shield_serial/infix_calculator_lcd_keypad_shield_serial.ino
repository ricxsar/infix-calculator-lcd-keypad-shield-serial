/*
 *  Infix Calculator With LCD Keypad Shield & Serial.
 *
 *  Copyright (C) 2010  Efstathios Chatzikyriakidis (contact@efxa.org)
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

/*
 *  In order to compile the sketch you will need to hack the LCD4Bit_mod library.
 *
 *  You should both add and implement the following
 *  method in order to clear specific lines of LCD:
 *
 *    void LCD4Bit_mod::clearLine (int line)
 *    {
 *      // Not implemented method (add your code here).
 *    }
 */

// include some external libraries' headers.
#include <LCD4Bit_mod.h>
#include <Streaming.h>
#include <StackList.h>

// include some calculator libraries' headers.
#include "infix_postfix.h"
#include "evaluate_postfix.h"
#include "conversion_tools.h"
#include "io_tools.h"

const int SERIAL_BAUD = 9600;   // the serial baud rate.
const int DELAY_TIME = 1500;    // the delay time before scrolling.
const int SCROLL_TIME = 500;    // the scrolling delay time.
const int EXPR_MAX_SIZE = 80;   // the maximum expression size in chars.
const int RESULT_MAX_SIZE = 64; // the maximum result size in chars.
const int RESULT_PRECISION = 8; // the result's fractional part precision.
const int LCD_MAX_LINES = 2;    // the number of LCD's lines.

// the object to manage the LCD.
LCD4Bit_mod lcd = LCD4Bit_mod (LCD_MAX_LINES);

// startup point entry (runs once).
void
setup () {
  // set serial data rate.
  Serial.begin (SERIAL_BAUD);

  // initialize the LCD.
  lcd.init ();

  // clear the LCD.
  lcd.clear ();

  // print the title message.
  lcd.printIn ("Infix Calculator V1.0, (GNU/GPL V3)");

  // delay some time before scrolling.
  delay (DELAY_TIME);
}

// loop the main sketch.
void
loop () {
  String infix;                // the infix expression.
  String postfix;              // the postfix expression.
  double result;               // the evaluated result.
  char value[RESULT_MAX_SIZE]; // the result as string.

  // try to read an expression.
  if (read_string (infix, EXPR_MAX_SIZE)) {
    // print the infix to the serial.
    Serial << "Infix Expression: " << infix << endl;

    // try to convert the infix expression to postfix.
    if (infix_postfix (infix, postfix)) {
      // print the postfix to the serial.
      Serial << "Postfix Expression: " << postfix << endl;

      // try to evaluate the postfix expression.
      if (evaluate_postfix (postfix, result)) {
        // convert the result as string.
        double_string (value, result, RESULT_PRECISION);

        // print the result to the serial.
        Serial << "Result is: " << value << endl;

        // clear the second line.
        lcd.clearLine (2);

        // print the result.
        lcd.printIn ("Result ~ ");
        lcd.printIn (value);

        // delay some time before scrolling.
        delay (DELAY_TIME);
      }
    }
  }

  // scrolling the LCD data.
  lcd.leftScroll (1, SCROLL_TIME);
}
