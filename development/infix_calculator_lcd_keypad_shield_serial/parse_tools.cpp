/*
 *  This file implements some parsing tools related to operators.
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

// include header defining the interface of the library.
#include "parse_tools.h"

// get the precedence of an operator symbol.
//
// precedence   operators
// 1            !
// 2            * /
// 3            + -
int
op_precedence (const char c) {
  switch (c) {
    case '!':
    case '~':
      return 7;

    case '*':
    case '/':
    case '%':
      return 6;

    case '+':
    case '-':
      return 5;

    case '&':
      return 4;

    case '^':
      return 3;

    case '|':
      return 2;

  }

  return 0;
}

// get the associativity of an operator symbol.
//
// associativity   operators
// right to left   !
// left to right   * /
// left to right   + -
bool
op_left_associative (const char c) {
  switch (c) {
    case '!':
    case '~':
      return false;

    case '*':
    case '/':    
    case '%':
      return true;

    case '+':
    case '-':
      return true;

    case '&':
    case '^':
    case '|':
      return true;

  }

  return false;
}

// check if a character is an operator symbol.
bool
is_operator (const char c) {
  switch (c) {
    case '!':
    
    case '~':

    case '/':
    case '*':

    case '+':
    case '-':

    case '&':

    case '^':

    case '|':
      return true;
  }

  return false;
}

// check if a character is an identifier symbol.
bool
is_identifier (const char c) {
  if (c >= '0' && c <= '9')
    return true;

  return false;
}

// get the number of the operands of an operator symbol.
int
op_operands_count (const char c) {
  switch (c) {
    case '*':
    case '/':
    case '+':
    case '-':
    case '&':
    case '^':
    case '|':  
      return 2;

    case '!':
    case '~':
      return 1;
  }

  return 0;
}
