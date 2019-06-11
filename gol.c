// HEADERS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "gol.h"
// CW, NW = Current and Next Worlds, respectively; w = world; ws = worlds;
// ENUMERATION
enum world_type {
        CW,
        NW,
};
// STATIC FUNCTIONS
static bool get_cell(const struct gol *g, int x, int y);
static int count_neighbors(const struct gol *g, int x, int y);
// FUNCTIONS
// 1st Function
void gol_alloc(struct gol *g, int sx, int sy)
{
    g->ws[CW] = (bool **)malloc(sx * sizeof(bool*));
    g->ws[NW] = (bool **)malloc(sx * sizeof(bool*));
    for (int k = 0; k < sy; k++) {
        g->ws[CW][k] = (bool *)malloc(sy * sizeof(bool));
        g->ws[NW][k] = (bool *)malloc(sy * sizeof(bool));
    }
}
// 2nd Function
void gol_free(struct gol *g, int sy)
{
    for (int k = 0; k < sy; k++) {
        free(g->ws[NW][k]);
        free(g->ws[CW][k]); 
    }
    free(g->ws[NW]);
    free(g->ws[CW]);
}
// 3rd Function
void gol_init(struct gol *g, int sx, int sy)
{
    for (int x = 0; x < sx; x++) {
        for (int y = 0; y < sy; y++) { 
            g->ws[CW][x][y] = 0;
        }
    }
            // Initial pattern
            g->ws[CW][0][1] = 1;
            g->ws[CW][1][2] = 1;
            g->ws[CW][2][0] = 1;
            g->ws[CW][2][1] = 1;
            g->ws[CW][2][2] = 1;
}
// 4th Function
void gol_print(struct gol *g, int sx, int sy)
{
    for (int x = 0; x < sx; x++) {
        for (int y = 0; y < sy; y++) {
            printf("%c ", g->ws[CW][x][y]? '#' : '.');
        }
        printf("\n");
    }
}
// 5th Function
// an = aive neighbors;
void gol_step(struct gol *g)
{
    for (int x = 0; x < SX; x++) {
        for (int y = 0; y < SY; y++) {
            int an = count_neighbors(g, x, y);
            if (g->ws[CW][x][y]) {
                // Survival condition
                    g->ws[NW][x][y] = (an == 2) || (an == 3);
            }   else {      
                    // Resurrection condition
                    g->ws[NW][x][y] = (an == 3);
                }
        }      
    }
    bool **swap = g->ws[CW];
    g->ws[CW] = g->ws[NW];
    g->ws[NW] = swap;
}
// STATIC FUNCTIONS
// 1st Function
// anc = alive neighbors counter
static int count_neighbors(const struct gol *g, int x, int y)
{
    int anc = 0;
    
    anc += get_cell(g, x - 1, y + 1);
    anc += get_cell(g, x - 0, y + 1);
    anc += get_cell(g, x + 1, y + 1);
    
    anc += get_cell(g, x - 1, y + 0);
    anc += get_cell(g, x + 1, y + 0);
    
    anc += get_cell(g, x - 1, y - 1);
    anc += get_cell(g, x - 0, y - 1);
    anc += get_cell(g, x + 1, y - 1);
    
    return anc;         
}
// 2nd Function
static bool get_cell(const struct gol *g, int x, int y)
{
     if(x >= SX)
        x = 0;
    else if (x < 0)
        x = SX - 1;
    if(y >= SY)
        y = 0;
    else if (y <0)
        y = SY - 1;
    return g->ws[CW][x][y];
}
