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
//    Implementation of the ed pattern
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

// A couple of standard commands:
#define CMD_QUIT 'q' // quit
#define CMD_ADD  'a' // add stuff together, takes 2 params

static char* exe_name; // the name of our binary

static char*  in_line;   // the string last read from input
static size_t in_len;    // the length of that line

// Here we interpret the commands and do stuff
// Return ? on invalid command and ! on error
char* cmd_proc(char* cmd_line, size_t cmd_len) {
      char* retval = "?\n"; // Standard response if the command doesn't match
      char new_retval[1024]; // Buffer used for responses
      int a,b;
      int s_err=0;
      char tmp;
      switch((char)cmd_line[0]) {
         case CMD_QUIT:
          exit(0);
         break;

         case CMD_ADD:
          s_err = sscanf(cmd_line,"%c %d %d\n",&tmp,&a,&b);
          if(s_err != 3) {
            retval = "!\n";
          } else {
            snprintf(new_retval,1023,"%d\n",a+b);
            return strdup(new_retval);
          }
         break;

         default:
          retval = "?\n";
         break;
      }
      return retval;
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
    // We read everything from input, process it and then pass it to output
    in_line = NULL;
    while ( (getline(&in_line,&in_len,input_fd)) != -1) {
          fprintf(stdout,"%s",cmd_proc(in_line,in_len));
          free(in_line);
          in_line = NULL;
    }
    
}
