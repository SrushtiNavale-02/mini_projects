#ifndef COORDS_H
#define COORDS_H

#include "cube.h"

// A cube (DBL fixed) maps to one number: permutation rank * N_TWIST + twist. 

#define N_PERM    5040                 // 7! permutation of corners
#define N_TWIST   729                  // 3^6 orientation of corenrs as DBL is 
                                       // fixed and 7th is forced so 3^6 not 7
#define N_STATES  (N_PERM * N_TWIST)   // 3,674,160; the solved cube is index 0 

int  cube_to_index(const Cube *c);
void index_to_cube(int idx, Cube *c);

#endif
