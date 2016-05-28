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
//    Implementation of the cantrip pattern
//
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

// Default return values for the example function
#define GOOD_VAL 200
#define BAD_VAL -1

// To keep in line with the standard way to do things, we return 1 in case of an error
#define ERR_BAD_PARAMS 1

static char* exe_name; // the name of our binary

int do_work(int is_verbose) {
    if(is_verbose) {
       fprintf(stderr,"%s: Doing stuff\n", exe_name);
    }
    
    if(1) {  // obviously in reality you'd set this expression to actually check stuff
       return GOOD_VAL;
    } else {
       return BAD_VAL;
    }
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
    
    return do_work(verbose);
}
