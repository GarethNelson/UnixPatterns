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
//    Implementation of the source pattern
//
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define ERR_BAD_PARAMS 1

static char* exe_name; // the name of our binary

static int state; // we keep state in the global context so get_stuff() knows where it's up to
                  // in a real tool (such as ls), there'd be multiple state variables
                  // in this example, state is just incremented and returned as a string

// This is where we generate our stuff, we call it repeatedly until it returns NULL
// This example just generates a list of numbers
// Note that it's the responsibility of get_stuff() to add the \n character
char* get_stuff() {
      state++;
      if(state>5) {
         return NULL;
      }
      char retval[4];
      snprintf(retval,3,"%d\n", state);
      return strdup(retval);
}

void print_usage() {
     fprintf(stderr,"usage: %s [-v]\n", exe_name);
}

int main(int argc, char** argv) {
    extern char *optarg;
    extern int optind;

    exe_name = strdup(argv[0]);

    int c = 0;
    int verbose = 0;

    while ((c = getopt(argc, argv, "f:v")) != -1) {
       switch(c) {
          case 'v':
             verbose = 1;
          break;

          case '?':
             print_usage();
             exit(ERR_BAD_PARAMS);
          break;

       }
    }
    
    char* out_str;
    state = 0;
    while( (out_str=get_stuff()) != NULL) {
       fprintf(stdout,"%s",out_str);
    }
}
