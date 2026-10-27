#ifndef PARSER_H
#define PARSER_H

#include <stddef.h>
#include "cube.h"

/*          . . U U . . . .
            . . U U . . . .
            L L F F R R B B
            L L F F R R B B
            . . D D . . . .
            . . D D . . . .
  
Input the colors into the state.csv file in the given format with all upppercase letters
only containing of only the standard 6 cube colors. Will later change it to accomodate
any 6 symbols as long is the scramble is valid. your own csv file can be passed as an argument
while running the binary
 */
int parse_cube_file(const char *path, Cube *out, char *err, size_t err_size);

#endif
