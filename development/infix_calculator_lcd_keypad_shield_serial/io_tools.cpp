/*
 *  This file implements some i/o (input, output) tools.
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

// include some external libraries' headers.
#include <Streaming.h>

// include header defining the interface of the library.
#include "io_tools.h"

// try to read specific number of characters from serial line.
bool
read_string (String & str, int n) {
  // the delay time for serial buffer to fill.
  static const int delayTime = 1000;

  // defensive issue.
  if (n <= 0) {
    Serial << "SERIAL-READ: positive number for characters to fetch." << endl;
    return false;
  }

  // if there are any data in the serial buffer.
  if (Serial.available ()) {
    // wait the serial buffer to fill.
    delay (delayTime);

    // if the data in the buffer is more than we want.
    if (Serial.available () > n) {
      Serial << "SERIAL-READ: the length of the data given is greater than the allowed." << endl;

      // continue clearing any data coming.
      do {
        // clear the buffer.
        while (Serial.available ()) { Serial.read(); }

        // wait the serial buffer to fill.
        delay (delayTime);
      }
      // loop while there are any data in the serial buffer.
      while (Serial.available ());

      return false;
    }

    // handle each character from the serial buffer.
    while (Serial.available () && (str.length () < n))
      str += (char) Serial.read ();

    // continue clearing any data coming.
    do {
      // clear the buffer.
      while (Serial.available ()) { Serial.read(); }

      // wait the serial buffer to fill.
      delay (delayTime);
    }
    // loop while there are any data in the serial buffer.
    while (Serial.available ());
  }
  else
    return false;

  // string was read from the serial.
  return true;
}
