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

int main(void) {
  std::string input;
  std::vector<char *> vec;
  std::cout << "begin\n";

  while (getline(std::cin, input)) {
    std::string modified(input);
    size_t end = modified.size() - 1;

    vec.clear();
    bool inword = false;
    for (size_t i = 0, j = 0; i < input.size(); i++) {
      if (input[i] != ' ' && inword == false) {
        if (input[i] != '\\') {
          modified[j] = input[i];
        }
        else {  // encouter '\'
          modified[j] = ' ';
          i++;
          modified[end] = 0;
          end--;
        }
        inword = true;
        vec.push_back(&modified[j]);
        j++;
      }
      else if (input[i] != ' ' && inword == true) {
        if (input[i] != '\\') {
          modified[j] = input[i];
        }
        else {
          modified[j] = ' ';
          i++;
          modified[end] = 0;
          end--;
        }
        j++;
      }
      else if (input[i] == ' ') {
        input[i] = 0;
        modified[j] = 0;
        j++;
        inword = false;
      }
    }

    for (size_t i = 0; i < vec.size(); i++) {
      std::cout << "No." << i << " arg is: " << vec[i] << std::endl;
    }
  }

  return 0;
}
