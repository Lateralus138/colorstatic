#ifndef FUNCTIONS_H_INCLUDE
#define FUNCTIONS_H_INCLUDE

#include <random>
#include <vector>
#include <string>
#include <sstream>

inline int rand_int_in_range (int begin, int end)
{
    std::random_device rand_dev;
    std::mt19937 engine (rand_dev ());
    std::uniform_int_distribution<> distribute(begin, end);
    return (int) distribute (engine);
}
inline int clr_in_range ()
{
  std::vector<int> rand =
  {
    rand_int_in_range (30,37),
    rand_int_in_range (90,97)
  };
  return rand[rand_int_in_range (0,1)];
}

inline std::string repeatChar (const char chr,int repeat_number)
{
  return std::string(repeat_number,chr);
}

std::string colorString (std::string str, const int colors[], int count)
{
  std::string  pre = "\x1b[",
          open = pre,
          close = pre + "0m";
  for (auto index = 0; index < count; index++)
  {
    if (index > 0)
    {
      open.push_back(';');
    }
    open.append(std::to_string(colors[index]));
  }
  open.push_back('m');
  return open + str + close;
}

inline bool isInt (const std::string & str)
{
  if(str.empty() ||
    ((!isdigit(str[0])) &&
      (str[0] != '-') &&
        (str[0] != '+'))) return false;
  char * pointer;
  strtol(str.c_str(), &pointer, 10);
  return (*pointer == 0);
}

std::vector<std::string> split(std::string text, char delim = ',')
{
    std::string line;
    std::vector<std::string> vec;
    std::stringstream ss(text);
    while(std::getline(ss, line, delim))
    {
        vec.push_back(line);
    }
    return vec;
}

#endif