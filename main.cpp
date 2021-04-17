#include <iostream>
#include <iterator>
#include <string>
#include <regex>
#include <fstream>
#include <stdlib.h>

using std::regex;
using std::string;

const char* patterns[] = {
  " +<polozky>",
  " +</polozky>",
  " +<id>.*</id>",
  " +<poctyN>.*</poctyN>",
};

int main() {
  // patterns
  int num_patterns = sizeof(patterns)/sizeof(char*);
  // printf("having %d patterns\n", num_patterns);
  regex* expressions = new regex[num_patterns];
  for (int i=0; i<num_patterns; i++) {
    expressions[i] = regex(patterns[i], std::regex_constants::ECMAScript);
  }

  // input from file
  std::ifstream file("WEB_ARTFORBAPOC.XML");
  std::ofstream result("zle_riadky.csv");
  std::string s = "  <polozky>\r\n";
  int line_count = 0;
  while (std::getline(file, s)) {
    line_count++;
    // if string matches any pattern, it is valid
    bool valid = false;
    for (int i=0; i<num_patterns; i++) {
      if (std::regex_search(s, expressions[i])) {
        valid = true;
      }
    }

    if (!valid) {
      // printf("invalid line %s\n", s.c_str());
      result << line_count << "," << s << std::endl;
    }
  }
}