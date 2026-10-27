#ifndef CUBE_H
#define CUBE_H

// 0 URF
// 1 UFL
// 2 ULB
// 3 UBR
// 4 DFR
// 5 DLF    
// 6 DBL    fixed
// 7 DRB    forced orientaation due to factor of 3

#define N_MOVES 9   // U U2 U' R R2 R' F F2 F' 
                    // as a L move is same as performing a R move
                    // then turning the cube, so it is redundant and can be avoided
                    // and the cube can be solved using only UFR moves

typedef struct {
    int cp[8];      // cp[slot] = piece in that slot      
    int co[8];      // co[slot] = orientation of that piece 0..2 
} Cube;

extern const char *const MOVE_STR[N_MOVES];

Cube cube_solved(void);
void cube_apply_move(Cube *c, int move);    //move 0..8: face move/3, (move%3)+1 quarter turns
int  cube_is_solved(const Cube *c);
int  cube_is_valid(const Cube *c);          // 1 if the state can exist and is reachable

#endif
