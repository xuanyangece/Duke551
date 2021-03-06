#include <dirent.h>
#include <stdio.h>
#include <string.h>

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <unordered_map>

size_t hashing(std::string content) {
  std::hash<std::string> key;
  return key(content);
}

void goMapping(std::string & answer,
               std::unordered_map<size_t, std::string> & map,
               std::string dirname) {
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
      goMapping(answer, map, dirname + entry->d_name + "/");
    }
    else {
      // file open
      std::ifstream file(dirname + entry->d_name);

      // get content
      std::string temp;
      std::string content;
      while (std::getline(file, temp)) {
        content += temp;
        content.push_back('\n');
      }

      size_t hashkey = hashing(content);

      // Map not contains, add it and its location
      if (map.find(hashkey) == map.end()) {
        map.insert(make_pair(hashkey, dirname + entry->d_name));
      }
      // Map already contains, print comparasion
      else {
        std::string comment;
        std::string shell;

        comment += "#Removing ";
        comment += dirname;
        comment += entry->d_name;
        comment += " (duplicate of ";
        comment += map[hashkey];
        comment += ").\n";

        shell += "rm ";
        shell += dirname;
        shell += entry->d_name;
        shell += "\n";

        answer += comment;
        answer += shell;
      }

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

  std::string answer;
  // key : content, value : dir
  std::unordered_map<size_t, std::string> map;
  answer += "#!/bin/bash\n";

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

    goMapping(answer, map, dirname);
  }
  std::cout << answer;

  return EXIT_SUCCESS;
}
