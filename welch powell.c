#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define x 8
const int colors[2] = { 1, 2 }; 
int counter = 0;
bool problem = false;

bool graf[x][5] = {
    {0,1,0,0,1},
    {0,1,0,1,0},
    {0,0,1,1,0},
    {1,1,0,0,0},
    {0,1,0,1,0},
    {0,0,1,1,0},
    {1,0,1,0,0},
    {0,0,1,1,0}
};

char vertex_names[x] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
int rate_list[x] = {0}; 
typedef struct {
    char vertex_id[x];
    int vertex_rates[x];
    bool adj[x][5]; 
    int colors[x];
    bool colored[x];
} Graf;

void colorIt(Graf *g) {
    counter++;
    int biggest = 0;
    int temp_rate = 0;

    if (counter == 1) {
        for (int i = 0; i < x; i++) {
            for (int j = 0; j < 5; j++) {
                if (g->adj[i][j]) {
                    rate_list[i]++;
                }
            }
        }
    }
    
    for (int w = 0; w < x; w++) {
        if (!g->colored[w]) {
            g->vertex_rates[w] = rate_list[w];
            if (temp_rate < g->vertex_rates[w]) {
                temp_rate = g->vertex_rates[w];
                biggest = w;
            }
        }
    }

    g->colors[biggest] = colors[(counter - 1) % 2]; 

    for (int e = 0; e < x; e++) {
        if (!g->adj[biggest][e] && biggest != e && !g->colored[e]) {
            for (int t = 0; t < 5; t++) {
                if (g->adj[e][t] && g->colors[t] == g->colors[biggest]) {
                    problem = true;
                }
                if (t == 4 && !problem) {
                    g->colors[e] = colors[(counter - 1) % 2];
                    g->colored[e] = true;
                    problem = false;
                } else if (t == 4) {
                    problem = false;
                }
            }
        }
    }
    
    g->colored[biggest] = true;
    if (memchr(g->colored, false, x) == NULL) {
        printf("Graph fully colored\n");
    } else {
        colorIt(g);
    }
}

void printColors(Graf *g) {
    for (int i = 0; i < x; i++) {
        printf("%c: color %d\n", g->vertex_id[i], g->colors[i]);
    }
}

int main() {
    Graf graf1;

    for (int y = 0; y < x; y++) {
        graf1.colors[y] = 99;
        graf1.colored[y] = false;
    }
    memcpy(&graf1.adj, &graf, sizeof(graf));
    memcpy(&graf1.vertex_id, &vertex_names, sizeof(graf1.vertex_id));
    colorIt(&graf1);
    printColors(&graf1); 
    return 0;
}
