#ifndef CONSOLESIZE_H_INCLUDE
#define CONSOLESIZE_H_INCLUDE

#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <termios.h>

class consolesize
{
  private:
    int lines;
    int columns;
  public:
    consolesize ()
    {
      processLines();
      processColumns();
    }
    void processLines ()
    {
      struct winsize wsize;
      ioctl (STDOUT_FILENO, TIOCGWINSZ, &wsize);
      auto wlines= (int)wsize.ws_row;
      lines = wlines;
    }
    void processColumns ()
    {
      struct winsize wsize;
      ioctl (STDOUT_FILENO, TIOCGWINSZ, &wsize);
      auto wcols= (int)wsize.ws_col;
      columns = wcols;
    }
    int currentLines ()
    {
      processLines ();
      return lines;
    }
    int currentColumns ()
    {
      processColumns ();
      return columns;
    }
    void setLines (int lines_s)
    {
      struct winsize wsize;
      ioctl (STDOUT_FILENO, TIOCSWINSZ, &wsize);
      wsize.ws_row = lines_s;
      lines = (int)wsize.ws_row;
    }
    void setColums (int columns_s)
    {
      struct winsize wsize;
      ioctl (STDOUT_FILENO, TIOCSWINSZ, &wsize);
      wsize.ws_col = columns_s;
      columns = (int)wsize.ws_col;
    }
};

#endif
