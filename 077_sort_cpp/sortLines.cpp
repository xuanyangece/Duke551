#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

void mySort(std::istream & is) {
  // store strings
  std::vector<std::string> v;
  std::string s;
  while (is.good()) {
    std::getline(is, s);
    v.push_back(s);
  }

  // sort strings
  std::sort(v.begin(), v.end());

  // print strings
  for (typename std::vector<std::string>::iterator it = v.begin(); it != v.end(); ++it) {
    std::cout << *it << std::endl;
  }
}

int main(int argc, char ** argv) {
  if (argc < 2) {
    mySort(std::cin);
  }
  else {
    for (int i = 1; i < argc; i++) {
      std::ifstream ifs;
      ifs.open(argv[i], std::fstream::in);
      if (!ifs.good()) {
        std::cerr << "cannot open" << argv[i] << std::endl;
        exit(EXIT_FAILURE);
      }
      mySort(ifs);
      ifs.close();
    }
  }

  return EXIT_SUCCESS;
}
