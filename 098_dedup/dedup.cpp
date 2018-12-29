#include <dirent.h>
#include <stdio.h>
#include <string.h>

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <list>
#include <unordered_map>
#include <vector>

const size_t SIZE = 99999;
std::vector<std::list<std::string> > table(SIZE);

size_t hashing(std::string content) {
  std::hash<std::string> key;
  return key(content);
}

void output(std::list<std::string> & curt) {
  std::string first = curt.front();
  curt.pop_front();
  for (std::list<std::string>::iterator it = curt.begin(); it != curt.end(); ++it) {
    std::cout << "#Removing " << first << " (duplicate of " << *it << ").\n";
    std::cout << "rm " << first << std::endl;
  }
}

void goMapping(std::string dirname) {
  // open directory
  DIR * d = opendir(dirname.c_str());
  if (!d) {
    std::cerr << "invalid directory path.\n";
    std::exit(EXIT_FAILURE);
  }

  struct dirent * entry;
  while ((entry = readdir(d)) != NULL) {
    std::string filename(entry->d_name);
    // ?? handle . or ..
    if (filename == "." || filename == "..")
      continue;

    // handle symlink
    if (entry->d_type == DT_LNK)
      continue;

    /* DIR */
    if (entry->d_type == DT_DIR) {
      goMapping(dirname + entry->d_name + "/");
    }
    else {
      // file open
      std::ifstream file(dirname + entry->d_name);

      // get content
      std::string temp;
      size_t index = 0;
      while (std::getline(file, temp)) {
        index += hashing(temp);
        index = index % SIZE;
      }
      std::string pathname;
      pathname += dirname + entry->d_name;

      table[index].push_front(pathname);

      // file close
      file.close();
    }
  }
  // close directory
  closedir(d);
}

int main(int argc, char ** argv) {
  if (argc < 2) {
    std::cerr << "Invalid command line arguments";
    std::exit(EXIT_FAILURE);
  }

  std::cout << "#!/bin/bash\n";

  // set up directory
  for (int i = 1; i < argc; i++) {
    // check if there's a '/' at the end
    char * fast = argv[i];
    char * slow = NULL;
    while (*fast != '\0') {
      slow = fast;
      fast++;
    }

    std::string dirname;
    dirname += argv[i];
    if (*slow != '/')
      dirname += "/";

    goMapping(dirname);
  }

  // print
  for (size_t i = 0; i < SIZE; i++) {
    if (table[i].size() > 1)
      output(table[i]);
  }

  return EXIT_SUCCESS;
}
