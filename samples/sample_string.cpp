/////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2012, Jared Duke.
// This code is released under the MIT License.
// www.opensource.org/licenses/mit-license.php
/////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <sstream>
#include <vector>
#include <conio.h>

#include <fc.h>

enum {
  FilteredStringLength = 10
};

using std::string;
using std::stringstream;
typedef std::vector<string> strings;

strings& split_helper(const string& s, char delim, strings& elems) {
  stringstream ss(s);
  string item;
  while(std::getline(ss, item, delim)) {
    elems.push_back(item);
  }
  return elems;
}

strings split(const string &s, char delim) {
  strings elems;
  return split_helper(s, delim, elems);
};

auto filter = [=](const strings& elems) -> strings {
  strings filteredElems;
  std::copy_if(begin(elems), end(elems), back_inserter(filteredElems), [=](const std::string& s) {
    return s.size() < FilteredStringLength;
  });
  return filteredElems;
};

auto lines = [](const string& s) -> strings {
  return split(s, ' ');
};

strings lines2 (const string& s) {
  return split(s, ' ');
}

auto unlines = [](const strings& elems) -> string {
  stringstream ss;
  std::for_each(elems.begin(), elems.end(), [&ss](const string& s) {
    ss << s << std::endl;
  });
  return ss.str();
};

string unlines2( const strings& elems) {
  stringstream ss;
  std::for_each(elems.begin(), elems.end(), [&ss](const string& s) {
    ss << s << std::endl;
  });
  return ss.str();
}

string inlines2(const std::string& input) {
  if (!input.empty())
    return input;
  else
  {
    std::cout << "Please enter a series of strings using separated by spaces." << std::endl;
    std::string line;
    std::getline(std::cin, line);
    return line;
  }
};

auto inlines = [](const std::string& input) -> std::string {
  return inlines2(input);
};

int main(int argc, char** argv) {

  using namespace fc;

  static const std::string testInput = "one two fifty-fivehundred eight-thousand-ninety-nine ten 0 sixtyfivethousand";

  auto lines_inlines  = lines + make_function(inlines2);
  auto unlines_filter = unlines + filter;
  auto shortLines     = unlines_filter.with(lines_inlines);
  auto shortLines2    = unlines_filter + lines_inlines;
  auto shortLines3    = make_function(unlines2) + filter + lines + inlines;
  auto shortLines4    = (unlines + filter).with(lines + inlines);

  auto print = [](const std::string& s) {
    std::cout << s << std::endl << std::endl;
  };
  
  print( unlines(filter(lines(inlines(testInput)))));
  print( shortLines (testInput) );
  print( shortLines2(testInput) );
  print( shortLines3(testInput) );
  print( shortLines4(testInput) );

  std::cout << "Press any key to continue...";
  std::cin.ignore(0,'\n');
  _getch();

  return 0;
}
