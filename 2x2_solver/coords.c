#include "coords.h"

static const int SLOT7[7] = {0, 1, 2, 3, 4, 5, 7};   // every slot except DBL 

static int perm_rank(const int *p, int n)   //ranking a permutation in
{                                           //the 3.6 mil combos
    int r = 0;
    for (int i = 0; i < n; i++)
    {
        int count = 0;
        for (int j = i + 1; j < n; j++)
        {
            if (p[j] < p[i]) count++;
        }
        r = r * (n - i) + count;
    }
    return r;
}

static void perm_unrank(int r, int *p, int n)   //interprets the permutation from
                                                //the rank nunmber
{
    int count[8], used[8] = {0};
    for (int i = n - 1; i >= 0; i--) 
    { 
        count[i] = r % (n - i); r /= (n - i); 
    }
    for (int i = 0; i < n; i++)
    {
        int k = count[i];
        for (int v = 0; v < n; v++)
        {
            if (used[v]) continue;
            if (k == 0) 
            { 
                p[i] = v; used[v] = 1; 
                break; 
            }
            k--;
        }
    }
}

static int get_perm(const Cube *c)
{
    int q[7];
    for (int i = 0; i < 7; i++)
    {
        int piece = c->cp[SLOT7[i]];
        q[i] = (piece == 7) ? 6 : piece;     //squeeze pieces 0..5,7 into 0..6
                                             //as index 6 piece is fixed and 
                                             //7th has forced movement
    }
    return perm_rank(q, 7);
}

static void set_perm(Cube *c, int r)
{
    int q[7];
    perm_unrank(r, q, 7);
    for (int i = 0; i < 7; i++)
    {

        c->cp[SLOT7[i]] = (q[i] == 6) ? 7 : q[i];
        c->cp[6] = 6;
    }
}

static int get_twist(const Cube *c)
{
    int t = 0;
    for (int i = 0; i < 6; i++) 
    {
        t = t * 3 + c->co[i];
    }
    return t;
}

static void set_twist(Cube *c, int t)
{
    int sum = 0;
    for (int i = 5; i >= 0; i--)
    {
        c->co[i] = t % 3;
        sum += c->co[i];
        t /= 3;
    }
    c->co[6] = 0;
    c->co[7] = (3 - sum % 3) % 3;
}

int cube_to_index(const Cube *c)
{
    return get_perm(c) * N_TWIST + get_twist(c);
}

void index_to_cube(int idx, Cube *c)
{
    set_perm(c, idx / N_TWIST);
    set_twist(c, idx % N_TWIST);
}
