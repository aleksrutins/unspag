/* MIT License
 *
 * Copyright (c) 2023 Aleks Rutins
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * SPDX-License-Identifier: MIT
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include <sys/stat.h>

#ifdef __linux
# include <linux/limits.h>
#else
# include <syslimits.h>
#endif

int init(int, char **);

int source(int, char **);

char config_path[PATH_MAX];

const char HELP[] =
  "Usage: %s <command> [arguments...]\n\n"

  "Commands:\n"
  "  init\t\t\tInitialize unspag's configuration file at %s.\n"
  "  source <shell>\tSource the configuration for the given shell.\n";


int
init(int    _argc,
     char **_argv)
{
  char scratch[PATH_MAX];
  strcpy (scratch, config_path);
  mkdir(dirname(scratch), 01777);
  FILE *config_file = fopen(config_path, "w");

  if(!config_file) {
    fprintf (stderr, "Error creating configuration file %s\n.", config_path);
    return 1;
  }

  fputs ("% Welcome to your configuration file! See the docs for more information.\n", config_file);

  fclose(config_file);

  printf ("Successfully created configuration file %s.\n", config_path);

  return 0;
}

int
source(int    argc,
       char **argv)
{

  FILE *config_file = fopen(config_path, "r");
  if(!config_file) {
    fprintf (stderr, "Error opening configuration file %s; please run `%s init` to create it.\n", config_path, argv[0]);
    return 1;
  }

  fclose(config_file);
  return 0;
}

int
main (int argc,
      char *argv[])
{
  sprintf(config_path, "%s/.config/unspag/config", getenv ("HOME"));

  if(argc < 2) {
    printf(HELP, argv[0], config_path);
    return 1;
  }

  char *cmd = argv[1];

  if(!strcmp(cmd, "init")) {
    return init (argc, argv);
  } else if(!strcmp(cmd, "source")) {
    return source (argc, argv);
  }
}
