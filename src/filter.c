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
//    Implementation of the filter pattern
//
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

// Return values for various errors:
#define ERR_BAD_PARAMS 1
#define ERR_NOT_OPEN   2

// The delimiter character to use on the input stream, default is of course \n for line by line input
#define delim_char     '\n'

static char* exe_name; // the name of our binary

static char*  in_str;   // the string last read from input
static size_t in_len;    // length of the last string

// This function does whatever transform we want, as an example we'd check if it matches a regular expression here to implement grep
// This example just returns the string back, so what we actually implement is basically cat
// Note also that the delim_char is included in input_str
char* transform(char* input_str, size_t input_len) {
      return input_str;
}

void print_usage() {
     fprintf(stderr,"usage: %s [-f filename] [-v]\n", exe_name);
}

int main(int argc, char** argv) {
    extern char *optarg;
    extern int optind;


    exe_name = strdup(argv[0]);

    FILE* input_fd           = NULL;
    char* input_filename     = NULL;

    int c = 0;
    int verbose = 0;

    while ((c = getopt(argc, argv, "f:v")) != -1) {
       switch(c) {
          case 'f':
             input_filename = strdup(optarg);
          break;

          case 'v':
             verbose = 1;
          break;

          case '?':
             print_usage();
             exit(ERR_BAD_PARAMS);
          break;

       }
    }

    if(input_filename == NULL) {
       input_fd = stdin;
    } else {
       input_fd = fopen(input_filename,"r");
       if(input_fd==NULL) {
          fprintf(stderr,"%s: Error opening file %s - %s\n",exe_name,input_filename,strerror(errno));
          exit(ERR_NOT_OPEN);
       }
       if(verbose) {
          fprintf(stderr,"%s: Opened %s\n",exe_name,input_filename);
       }
    }

    // The main event!
    // We read everything from input, transform it and then pass it to output
    in_str = NULL;
    while ( (getdelim(&in_str,&in_len,delim_char,input_fd)) != -1) {
          fprintf(stdout,"%s",transform(in_str,in_len));
          free(in_str);
          in_str = NULL;
    }
    
}
