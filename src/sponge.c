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
//    Implementation of the sponge pattern
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

// Optimisation stuff here
#define READ_BLOCK_SIZE 512

static char* exe_name; // the name of our binary

static char*  in_str;   // the string read from input
static size_t in_len;   // length of the string
static size_t cur_len;  // length of the current read op

// Same as in the filter example
// For simplicity, we just return a copy of the string
char* do_work(char* input_str, size_t input_len) {
    
    return strdup(input_str);
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
    in_str = (char*)malloc(READ_BLOCK_SIZE);
    while ( (cur_len = fread(in_str,READ_BLOCK_SIZE,1,input_fd)) > 0) {
          in_str = (char*)realloc(in_str,strlen(in_str)+cur_len);
    }
    in_len = strlen(in_str);

    printf("%s",do_work(in_str,in_len));
}
