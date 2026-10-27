#include <stdio.h>
#include <string.h>
#include "solver.h"
#include "coords.h"

#define DIST_UNSET 255
#define MAX_DEPTH  16

static unsigned char dist[N_STATES];    // contains all possible combos for the cube
                                        // provided by perm_rank and twist
static int  god = 0;
static long level_count[MAX_DEPTH];

void solver_build_table(void)
{
    memset(dist, DIST_UNSET, sizeof dist);
    dist[0] = 0;
    level_count[0] = 1;
    long filled = 1;
    god = 0;

    for (int d = 0; filled < N_STATES && d + 1 < MAX_DEPTH; d++)
    {
        long added = 0;
        for (int i = 0; i < N_STATES; i++)
        {
            if (dist[i] != d) continue;

            Cube base;
            index_to_cube(i, &base);
            for (int m = 0; m < N_MOVES; m++)
            {
                Cube c = base;
                cube_apply_move(&c, m);
                int j = cube_to_index(&c);
                if (dist[j] == DIST_UNSET) 
                { 
                    dist[j] = d + 1; 
                    added++; 
                }
            }
        }
        if (added == 0) break;
        level_count[d + 1] = added;
        filled += added;
        god = d + 1;
    }
}

int solver_solve(Cube *c, int *out)
{
    int idx = cube_to_index(c), n = 0;
    if (dist[idx] == DIST_UNSET) return -1;

    while (dist[idx] != 0)
    {
        int stepped = 0;
        for (int m = 0; m < N_MOVES && !stepped; m++)
        {
            Cube t = *c;
            cube_apply_move(&t, m);
            int j = cube_to_index(&t);
            if (dist[j] == dist[idx] - 1)
            {
                out[n++] = m;
                *c = t;
                idx = j;
                stepped = 1;
            }
        }
        if (!stepped) return -1;
    }
    return n;
}

int solver_god_number(void) { return god; }

void solver_print_stats(void)
{
    for (int d = 0; d <= god; d++) printf("%2d %ld\n", d, level_count[d]);
    printf("God's number = %d\n", god);
}
