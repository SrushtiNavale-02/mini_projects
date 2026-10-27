#include <string.h>
#include "cube.h"

const char *const MOVE_STR[N_MOVES] = {
    "U", "U2", "U'", "R", "R2", "R'", "F", "F2", "F'"
};

// clockwise quarter turns of U,R,F 
static const Cube BASE[3] = {
    { {3, 0, 1, 2, 4, 5, 6, 7}, {0, 0, 0, 0, 0, 0, 0, 0} },   //U 
    { {4, 1, 2, 0, 7, 5, 6, 3}, {2, 0, 0, 1, 1, 0, 0, 2} },   // R
    { {1, 5, 2, 3, 0, 4, 6, 7}, {1, 2, 0, 0, 2, 1, 0, 0} },   // F
};

Cube cube_solved(void)
{
    Cube c;
    memset(&c, 0, sizeof c);
    for (int i = 0; i < 8; i++) c.cp[i] = i;
    return c;
}

void cube_apply_move(Cube *c, int move)
{
    const Cube *b = &BASE[move / 3];
    for (int k = 0; k <= move % 3; k++)
    {
        Cube t;
        for (int i = 0; i < 8; i++)
        {
            t.cp[i] = c->cp[b->cp[i]];
            t.co[i] = (c->co[b->cp[i]] + b->co[i]) % 3;
        }
        *c = t;
    }
}

int cube_is_solved(const Cube *c)
{
    Cube s = cube_solved();
    return memcmp(c, &s, sizeof s) == 0;
}

int cube_is_valid(const Cube *c)
{
    int seen[8] = {0}, sum = 0;
    for (int i = 0; i < 8; i++)
    {
        if (c->cp[i] < 0 || c->cp[i] > 7 || seen[c->cp[i]]++) return 0;
        if (c->co[i] < 0 || c->co[i] > 2) return 0;
        sum += c->co[i];
    }
    return c->cp[6] == 6 && c->co[6] == 0 && sum % 3 == 0;
}
