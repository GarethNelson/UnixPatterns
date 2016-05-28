//-----------------------------------------------------------------------------
//
// $Id:$
//
// Copyright (C) 2016 by Gareth Nelson (gareth@garethnelson.com)
//
// This is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// The Lambda engine is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
//
// $Log:$
//
// DESCRIPTION:
//    Implementation of the roguelike pattern
//
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <curses.h>
#include <signal.h>

// A couple of standard commands:
#define CMD_QUIT 'q' // quit
#define CMD_LIC  'l' // Show the license info

static char* exe_name; // the name of our binary
static void finish(int sig);

// Here we interpret the commands and do stuff
char* cmd_proc(char cmd) {
      char* retval = "?\n"; // Standard response if the command doesn't match
      switch(cmd) {
         case CMD_QUIT:
          finish(0);
         break;

         case CMD_LIC:
          return "\n"
"    This program is free software: you can redistribute it and/or modify\n"
"    it under the terms of the GNU General Public License as published by\n"
"    the Free Software Foundation, either version 2 of the License, or\n"
"    (at your option) any later version.\n"
"\n"
"    This program is distributed in the hope that it will be useful,\n"
"    but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
"    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
"    GNU General Public License for more details.\n"
"\n"
"    You should have received a copy of the GNU General Public License\n"
"    along with this program.  If not, see <http://www.gnu.org/licenses/>\n";
         break;

         default:
          retval = "\n?\n";
         break;
      }
      return retval;
}

void print_usage() {
     fprintf(stderr,"usage: %s\n", exe_name);
}


int main(int argc, char** argv) {
    exe_name = strdup(argv[0]);

    signal(SIGINT, finish);
    initscr();
    keypad(stdscr,TRUE);
    nonl();
    cbreak();
    
    char* cmd_ret;
    while(1) {
        cmd_ret = cmd_proc(getch());
        addstr(cmd_ret);
    }
    finish(0); 
}

static void finish(int sig) {
   endwin();
   exit(0);
}
