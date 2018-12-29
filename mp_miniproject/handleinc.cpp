#include <ctype.h>
#include <dirent.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>

#include <cstring>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#define PATH_LEN 256

/*
  Helper function to determine integer part zero or not
 */
bool onlyZero(std::string str, size_t point) {
  size_t end = point == std::string::npos ? str.size() : point;

  for (size_t i = 1; i < end; i++) {
    if (str[i] != '0') {
      return false;
    }
  }

  return true;
}

/*
  Helper function to determine fraction part zero or not
 */
bool onlyZero(std::string str) {
  for (size_t i = 0; i < str.size(); i++) {
    if (str[i] != '0') {
      return false;
    }
  }
  return true;
}

/*
  Handle increment for string representation of number
*/
std::string incrementNumber(std::string str) {
  std::string answer;
  size_t point = str.find(".");

  if (str[0] == '-') { /* negative */
    if ((onlyZero(str, point) && point == std::string::npos) ||
        (point != std::string::npos && onlyZero(str, point) &&
         onlyZero(str.substr(point + 1))))  // condition1 like -0000000   condition2 like -000.0000
      return "1";
    else if (!onlyZero(str,
                       point)) {     // do normal minus for integer number part and concat fraction
      size_t curt = str.size() - 1;  // mark concatenate position

      if (point != std::string::npos) {  // has point, concat fraction first
        answer += str.substr(point);
        curt = point - 1;
      }

      bool decarry = true;  // do minus
      while (curt > 0 && decarry) {
        if (str[curt] == '0') {
          answer = "9" + answer;
        }
        else {
          answer = std::to_string((str[curt] - '0') - 1) + answer;
          decarry = false;
        }
        curt--;
      }

      if (curt == 0) {
        answer = "-" + answer;
      }
      else {
        answer = str.substr(0, curt - 0 + 1) + answer;
      }
    }
    else {  // like -0.123
      size_t curt = str.size() - 1;
      for (; curt > point; curt--) {  // find first non-zero from right to left
        if (str[curt] != '0') {
          break;
        }
        else {
          answer = "0" + answer;
        }
      }

      // handle least significant digit
      answer = std::to_string(10 - (str[curt] - '0')) + answer;
      curt--;

      // other fraction digits use 9 to minus
      while (curt > point) {
        answer = std::to_string(9 - (str[curt] - '0')) + answer;
        curt--;
      }

      // add "0."
      answer = "0." + answer;
    }
  }
  else { /* positive */
    if (str[0] == '+') {
      return "+" + incrementNumber(str.substr(1));
    }
    size_t curt = str.size() - 1;  // mark concatenate position

    if (point != std::string::npos) { /* fraction */
      answer += str.substr(point);    // copy number after point directly
      curt = point - 1;
    }

    bool carry = true;  // initial carry with inc's 1
    while (curt != SIZE_MAX && carry) {
      if (str[curt] == '9') {
        answer = "0" + answer;  // carry
      }
      else {
        answer = std::to_string((str[curt] - '0') + 1) + answer;  // no carry
        carry = false;
      }
      curt--;
    }

    if (curt == SIZE_MAX && carry) {  // still carry after all digits
      answer = "1" + answer;
    }
    else if (curt == SIZE_MAX && !carry) {  // no carry after all digits
      return answer;
    }
    else {  // no carry with remaining digits
      answer = str.substr(0, curt - 0 + 1) + answer;
    }
  }

  return answer;
}

// test prune input
int main(void) {
  std::string input;

  while (getline(std::cin, input)) {
    std::cout << "incremented number: " << incrementNumber(input) << std::endl;
  }
  return 0;
}
