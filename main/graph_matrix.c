/* graph_matrix.c */
/* Date  : 28 March 2016
 * Author: Ankit Pati
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 20

typedef int node;

struct graph{
    node adjmat[MAX_NODES + 1][MAX_NODES + 1];
    size_t count;
} g;

void init()
{
    size_t i, j;

    for(i = 0; i < MAX_NODES + 1; ++i)
        for(j = 0; j < MAX_NODES + 1; ++j)
            g.adjmat[i][j] = 0;

    g.count = 0;
}

size_t find(node d) /* return 0; on failure */
{
    size_t i;
    for(i = 1; i <= g.count && g.adjmat[0][i] != d; ++i);
    if(i <= g.count) return i;
    return 0;
}

size_t insert(node d) /* return 0; on failure */
{
    size_t f;

    if(g.count == MAX_NODES) return 0;

    if((f = find(d))) return f;

    f = ++g.count;
    g.adjmat[0][f] = g.adjmat[f][0] = d;

    return g.count;
}

void delet(node d)
{
    size_t i, j, f;

    if(!(f = find(d))) return;

    for(i = 0; i <= g.count; ++i)
        for(j = f; j < g.count; ++j){
            g.adjmat[i][j] = g.adjmat[i][j + 1];
            g.adjmat[j][i] = g.adjmat[j + 1][i];
        }

    for(i = 0; i <= g.count; ++i){
        g.adjmat[i][g.count] = 0;
        g.adjmat[g.count][i] = 0;
    }

    --g.count;
}

int directed_insert_edge(node from, node to) /* return 0; on failure */
{
    size_t f, t;
    if(!(f = insert(from)) || !(t = insert(to))) return 0;
    return ++g.adjmat[f][t];
}

int directed_delet_edge(node from, node to) /* return 0; is not failure */
{
    size_t f, t;
    if(!(f = find(from)) || !(t = find(to))) return 0;
    return g.adjmat[f][t] ? --g.adjmat[f][t] : 0;
}

int undirected_insert_edge(node from, node to) /* return 0; on failure */
{
    return from == to ?
        directed_insert_edge(from, to) :
        (directed_insert_edge(from, to) + directed_insert_edge(to, from)) / 2;
}

int undirected_delet_edge(node from, node to) /* return 0; on failure */
{
    return from == to ?
        directed_delet_edge(from, to) :
        (directed_delet_edge(from, to) + directed_delet_edge(to, from)) / 2;
}

void display()
{
    size_t i, j;

    printf(" x  | ");
    for(i = 1; i <= g.count; ++i)
        printf("%3d ", g.adjmat[0][i]);
    putchar('\n');

    printf("----+");
    for(i = g.count ? 1 + 4 * g.count : 0; i; --i)
        putchar('-');
    putchar('\n');

    for(i = 1; i <= g.count; ++i){
        printf("%3d | ", g.adjmat[i][0]);

        for(j = 1; j <= g.count; ++j)
            printf("%3d ", g.adjmat[i][j]);

        putchar('\n');
    }
}

int main()
{
    int ch;
    node d, f, t;

    init();

    do{
        puts("What would you like to do?");
        puts("( 0) Exit");
        puts("( 1) Insert");
        puts("( 2) Delete");
        puts("( 3) Directed Insert Edge");
        puts("( 4) Directed Delete Edge");
        puts("( 5) Undirected Insert Edge");
        puts("( 6) Undirected Delete Edge");
        puts("( 7) Display");

        scanf(" %d%*c", &ch);

        switch(ch){
        case 0:
            break;
        case 1:
            puts("Node?");
            scanf(" %d%*c", &d);
            if(!insert(d)) puts("Matrix Full!");
            break;
        case 2:
            puts("Node?");
            scanf(" %d%*c", &d);
            delet(d);
            break;
        case 3:
            puts("From?");
            scanf(" %d%*c", &f);

            puts("To?");
            scanf(" %d%*c", &t);

            if(!directed_insert_edge(f, t)) puts("Matrix Full!");
            break;
        case 4:
            puts("From?");
            scanf(" %d%*c", &f);

            puts("To?");
            scanf(" %d%*c", &t);

            directed_delet_edge(f, t);
            break;
        case 5:
            puts("From?");
            scanf(" %d%*c", &f);

            puts("To?");
            scanf(" %d%*c", &t);

            if(!undirected_insert_edge(f, t)) puts("Matrix Full!");
            break;
        case 6:
            puts("From?");
            scanf(" %d%*c", &f);

            puts("To?");
            scanf(" %d%*c", &t);

            undirected_delet_edge(f, t);
            break;
        case 7:
            display();
            break;
        default:
            puts("Incorrect Choice!");
            break;
        }
    } while(ch);

    return 0;
}
/* end of graph_matrix.c */

/* OUTPUT

What would you like to do?
( 0) Exit
( 1) Insert
( 2) Delete
( 3) Directed Insert Edge
( 4) Directed Delete Edge
( 5) Undirected Insert Edge
( 6) Undirected Delete Edge
( 7) Display

1
43

1
50

1
64

1
55

2
50

7
 x  |  43  64  55
----+-------------
 43 |   0   0   0
 64 |   0   0   0
 55 |   0   0   0

5
From?
43
To?
55

7
 x  |  43  64  55
----+-------------
 43 |   0   0   1
 64 |   0   0   0
 55 |   1   0   0

6
From?
43
To?
55

7
 x  |  43  64  55
----+-------------
 43 |   0   0   0
 64 |   0   0   0
 55 |   0   0   0

0

*/
