// -----------------------------------------------
// 'colorstatic'
// Copyright © 2022
// Ian Pride @ New Pride Software/Services
// Sat 11 Jun 2022 17:40:31 CST
// -----------------------------------------------
#include <iostream>
#include <chrono>
#include <thread>
#include <consolesize.h>
#include <functions.h>
#include <regex>
#include <cstdlib>
#include <csignal>

#include <cstdio>

using std::cout;
using std::endl;
using std::flush;
using std::regex;
using std::regex_match;
using std::string;
using std::thread;
using std::to_string;
using std::vector;
using std::chrono::milliseconds;
using std::this_thread::sleep_for;

inline void sleep(int milliseconds_)
{
  sleep_for(
      milliseconds(
          milliseconds_));
}

inline void reset_screen()
{
  cout << "\x1bM\x1b[2J\x1b[1;1H\x1b[?25h" << flush;
}

auto LOOPSTOP = false;
void signalHandler(int signal)
{
  (void)signal;
  LOOPSTOP = true;
  sleep(50);
  reset_screen();
  sleep(50);
  exit(0);
}
void threadWaitForEnter()
{
  getchar();
  signalHandler(0);
}

int main(int argc, char *argv[])
{
  signal(SIGINT, signalHandler);
  const char space = ' ';
  string line_empty = repeatChar(space, 50);
  const string LINE_EMPTY_WHITE = "\x1b[107m" + line_empty + "\x1b[0m";
  auto delay = 0;
  auto forced_column = false,
       forced_line = false,
       mono = false;
  int cell_column_max, cell_line_max;
  const vector<string> FRAMES_DEFAULT = {"\020 ", "█", "░", "▒", "▓"};
  vector<string> frames_select;
  consolesize wsize;
  int rand_column, rand_line, rand_frame;
  if (argc > 1)
  {
    vector<string> argv_copy;
    regex help_rgx("^-([hH]|-[hH][eE][lL][pP])$");
    regex delay_rgx("^-([dD]|-[dD][eE][lL][aA][yY])$");
    regex lines_rgx("^-([lL]|-[lL][iI][nN][eE][sS])$");
    regex columns_rgx("^-([cC]|-[cC][oO][lL][uU][mM][nN][sS])$");
    regex mono_rgx("^-([mM]|-[mM][oO][nN][oO])$");
    regex frames_rgx("^-([fF]|-[fF][rR][aA][mM][eE][sS])$");
    argv_copy.assign(argv + 1, argv + argc);
    auto argv_size = (int)argv_copy.size();
    for (auto index = 0; index < argv_size; index++)
    {
      if (regex_match(argv_copy[index], help_rgx))
      {
        const int WHITEBG_BLACKFG[] = {107, 30, 23};
        const int WHITEBG_GREENFG[] = {107, 32, 3};
        const int WHITEBG_BLUEFG[] = {107, 34, 3};
        const int WHITEBG_MAGENTAFG[] = {107, 35, 3};
        const int WHITEBG_REDFG[] = {107, 31, 3};
        const string USAGE = colorString("USAGE", WHITEBG_GREENFG, 3);
        const string SWITCH = colorString("SWITCH", WHITEBG_BLUEFG, 3);
        const string PARAMETER = colorString("PARAMETER", WHITEBG_MAGENTAFG, 3);
        const string ERRORS = colorString("ERRORS", WHITEBG_REDFG, 3);
        const string WHITE_SPACE = colorString(" ", WHITEBG_BLACKFG, 3);
        cout
            << LINE_EMPTY_WHITE << "\n"
            << WHITE_SPACE << USAGE
            << colorString(": colorstatic [", WHITEBG_BLACKFG, 3)
            << SWITCH
            << colorString(" [", WHITEBG_BLACKFG, 3)
            << PARAMETER
            << colorString("]...]...    ", WHITEBG_BLACKFG, 3) << "\n"
            << colorString(
                   " 'ColorStatic' - Random color animations by       ",
                   WHITEBG_BLACKFG, 3)
            << '\n'
            << colorString(
                   " character frames in the command line. Press      ",
                   WHITEBG_BLACKFG, 3)
            << "\n"
            << colorString(
                   " [Enter] or [Ctrl+C] to quit this program.        ",
                   WHITEBG_BLACKFG, 3)
            << "\n"
            << LINE_EMPTY_WHITE << '\n'
            << WHITE_SPACE << SWITCH
            << colorString(": optional                                 ", WHITEBG_BLACKFG, 3) << '\n'
            << colorString("     -h, --help    This HELP message.             ", WHITEBG_BLACKFG, 3) << '\n'
            << colorString("     -d, --delay   Delay between frames in        ", WHITEBG_BLACKFG, 3) << '\n'
            << colorString("                   milliseconds.                  ", WHITEBG_BLACKFG, 3) << '\n'
            << colorString("     -c, --columns Force number of columns.       ", WHITEBG_BLACKFG, 3) << '\n'
            << colorString("     -l, --lines   Force number of lines.         ", WHITEBG_BLACKFG, 3) << '\n'
            << colorString("     -f, --frames  A comma delimited string or    ", WHITEBG_BLACKFG, 3) << '\n'
            << colorString("                   array of characters to be used ", WHITEBG_BLACKFG, 3) << '\n'
            << colorString("                   as random frames. Defaults to: ", WHITEBG_BLACKFG, 3) << '\n'
            << colorString("                   \' ,█,░,▒,▓\'                    ", WHITEBG_BLACKFG, 3) << '\n'
            << colorString("     -m, --mono    Monochrome mode, disable       ", WHITEBG_BLACKFG, 3) << '\n'
            << colorString("                   random colors.                 ", WHITEBG_BLACKFG, 3) << '\n'
            << LINE_EMPTY_WHITE << '\n'
            << WHITE_SPACE << PARAMETER
            << colorString(":                                       ", WHITEBG_BLACKFG, 3) << '\n'
            << colorString("     Delay      Number in integer milliseconds.   ", WHITEBG_BLACKFG, 3) << '\n'
            << colorString("     Columns    Number in integers.               ", WHITEBG_BLACKFG, 3) << '\n'
            << colorString("     Lines      Number in integers.               ", WHITEBG_BLACKFG, 3) << '\n'
            << colorString("     Frames     String array of characters        ", WHITEBG_BLACKFG, 3) << '\n'
            << colorString("                delimited by a comma; e.g.:       ", WHITEBG_BLACKFG, 3) << '\n'
            << colorString("                \' ,#,@,^,*\' or:                   ", WHITEBG_BLACKFG, 3) << '\n'
            << colorString("                \"${BASH_ARRAY[@]}\" etc...         ", WHITEBG_BLACKFG, 3) << '\n'
            << LINE_EMPTY_WHITE << '\n'
            << WHITE_SPACE << ERRORS
            << colorString(":                                          ", WHITEBG_BLACKFG, 3) << '\n'
            << colorString("     1   Error in delay parameter.                ", WHITEBG_BLACKFG, 3) << '\n'
            << colorString("     2   Error in columns parameter.              ", WHITEBG_BLACKFG, 3) << '\n'
            << colorString("     3   Error in lines parameter.                ", WHITEBG_BLACKFG, 3) << '\n'
            << colorString("     4   Error in frames parameter.               ", WHITEBG_BLACKFG, 3) << '\n'
            << LINE_EMPTY_WHITE << '\n'
            << endl;
        return 0;
      }
      if (regex_match(argv_copy[index], delay_rgx))
      {
        if (index + 1 > (int)argv_copy.size() - 1)
          return 1;
        auto opt = argv_copy[index + 1];
        if (!isInt(opt))
          return 1;
        auto castint = atoi(opt.c_str());
        if (castint < 0)
          return 1;
        delay = castint;
      }
      if (regex_match(argv_copy[index], mono_rgx))
        mono = true;
      if (regex_match(argv_copy[index], columns_rgx))
      {
        if (index + 1 > (int)argv_copy.size() - 1)
          return 2;
        auto opt = argv_copy[index + 1];
        if (!isInt(opt))
          return 2;
        auto castint = atoi(opt.c_str());
        if (castint < 0)
          return 2;
        forced_column = true;
        cell_column_max = castint;
      }
      if (regex_match(argv_copy[index], lines_rgx))
      {
        if (index + 1 > (int)argv_copy.size() - 1)
          return 3;
        auto opt = argv_copy[index + 1];
        if (!isInt(opt))
          return 3;
        auto castint = atoi(opt.c_str());
        if (castint < 0)
          return 3;
        forced_line = true;
        cell_line_max = castint;
      }
      if (regex_match(argv_copy[index], frames_rgx))
      {
        if (index + 1 > (int)argv_copy.size() - 1)
          return 4;
        string opt = argv_copy[index + 1];
        vector<string> tmpvec = split(opt);
        if (tmpvec.size() == 0)
          return 4;
        frames_select = tmpvec;
      }
    }
  }
  if (frames_select.size() == 0)
    frames_select = FRAMES_DEFAULT;
  thread waitForEnter(threadWaitForEnter);
  cout << "\x1b[2J\x1b[1;1f" << flush;
  while (true)
  {
    if (!forced_column)
      rand_column = rand_int_in_range(1, wsize.currentColumns());
    else
      rand_column = rand_int_in_range(1, cell_column_max);
    if (!forced_line)
      rand_line = rand_int_in_range(1, wsize.currentLines());
    else
      rand_line = rand_int_in_range(1, cell_line_max);
    rand_frame = rand_int_in_range(0, frames_select.size() - 1);
    cout << "\x1b[?25l" << flush;
    if (!mono)
    {
      printf("%s%d%c%d%s%d%c%s%s", "\x1b[", rand_line, ';',
             rand_column, "f\x1b[", clr_in_range(), 'm',
             frames_select[rand_frame].c_str(), "\x1b[0m");
    }
    else
    {
      printf("%s%d%c%d%c%s", "\x1b[", rand_line, ';',
             rand_column, 'f', frames_select[rand_frame].c_str());
    }
    cout << "\x1b[?25h" << flush;
    sleep_for(milliseconds(delay));
    if (LOOPSTOP)
    {
      reset_screen();
      break;
    }
  }
  waitForEnter.join();
  sleep_for(milliseconds(10));
  reset_screen();
}
