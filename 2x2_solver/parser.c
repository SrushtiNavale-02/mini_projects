#include <stdio.h>
#include "parser.h"

static char opp_face(char c)
{
    switch (c)
    {
        case 'R': return 'O';  case 'O': return 'R';
        case 'B': return 'G';  case 'G': return 'B';
        case 'W': return 'Y';  case 'Y': return 'W';
        default:  return 0;
    }
}

static int load_grid(const char *path, char g[6][8], char *err, size_t n)
{
    FILE *f = fopen(path, "r");
    if (!f) { snprintf(err, n, "cannot open file '%s'", path); return 1; }

    for (int r = 0; r < 6; r++)
        for (int k = 0; k < 8; k++)
            if (fscanf(f, " %c", &g[r][k]) != 1)
            {
                snprintf(err, n, "file '%s' is too short (need 6 rows of 8 characters)", path);
                fclose(f);
                return 1;
            }
    fclose(f);
    return 0;
}

static int check_colours(char g[6][8], char *err, size_t n)
{
    const char colours[6] = {'R', 'O', 'B', 'G', 'W', 'Y'};
    int counts[6] = {0};

    for (int r = 0; r < 6; r++)
        for (int k = 0; k < 8; k++)
        {
            char ch = g[r][k];
            if (ch == '.') continue;
            int found = 0;
            for (int i = 0; i < 6; i++)
                if (ch == colours[i]) { counts[i]++; found = 1; }
            if (!found) { snprintf(err, n, "unknown colour '%c'", ch); return 1; }
        }
    for (int i = 0; i < 6; i++)
        if (counts[i] != 4)
        {
            snprintf(err, n, "colour %c appears %d times (expected 4)", colours[i], counts[i]);
            return 1;
        }
    return 0;
}

static int grid_to_cube(char g[6][8], Cube *c, char *err, size_t n)
{
    const char d = g[5][2], b = g[3][7], l = g[3][0];
    const char ud = opp_face(d), ub = opp_face(b), ul = opp_face(l);
    if (!ud || !ub || !ul) { snprintf(err, n, "bad colour on the DBL corner"); return 1; }

    const char solved[8][3] = {
        {ud, ul, ub}, {ud, ub, l},  {ud, l,  b},  {ud, b, ul},
        {d,  ub, ul}, {d,  l,  ub}, {d,  b,  l},  {d,  ul, b} };

    const char now[8][3] = {
        {g[1][3], g[2][4], g[2][3]}, {g[1][2], g[2][2], g[2][1]},
        {g[0][2], g[2][0], g[2][7]}, {g[0][3], g[2][6], g[2][5]},
        {g[4][3], g[3][3], g[3][4]}, {g[4][2], g[3][1], g[3][2]},
        {g[5][2], g[3][7], g[3][0]}, {g[5][3], g[3][5], g[3][6]} };

    for (int i = 0; i < 8; i++)
    {
        int found = 0;
        for (int j = 0; j < 8 && !found; j++)
            for (int r = 0; r < 3; r++)
                if (now[i][ r         ] == solved[j][0] &&
                    now[i][(r + 1) % 3] == solved[j][1] &&
                    now[i][(r + 2) % 3] == solved[j][2])
                {
                    c->cp[i] = j;
                    c->co[i] = r;
                    found = 1;
                    break;
                }
        if (!found)
        {
            snprintf(err, n, "corner in slot %d does not match any real corner", i);
            return 1;
        }
    }
    return 0;
}

int parse_cube_file(const char *path, Cube *out, char *err, size_t err_size)
{
    char g[6][8];
    if (load_grid(path, g, err, err_size))        return 1;
    if (check_colours(g, err, err_size))          return 1;
    if (grid_to_cube(g, out, err, err_size))      return 1;
    if (!cube_is_valid(out))
    {
        snprintf(err, err_size, "this cube cannot be solved (impossible twist or pieces)");
        return 1;
    }
    return 0;
}
