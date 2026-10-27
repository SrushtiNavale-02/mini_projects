#ifndef SOLVER_H
#define SOLVER_H

#include "cube.h"

#define MAX_SOLUTION 16   
// optimal solution is 11 moves is half turn metric and 14 moves in 
// quarter turn metric. 16 is a safe size buffer

void solver_build_table(void);

int  solver_solve(Cube *c, int *out);

int  solver_god_number(void);

void solver_print_stats(void);

#endif
