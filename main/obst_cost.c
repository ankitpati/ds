/* obst_cost.c */
/* Date  : 25 April 2016
 * Author: Ankit Pati
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int d;
    size_t freq;
} node;

node *inorder(node *f, size_t n)
{
    size_t i, j, small;
    node temp;

    for(i = 0; i < n; ++i){
        small = i;

        for(j = i; j < n; ++j)
            if(f[j].d < f[small].d)
                small = j;

        temp = f[small];
        f[small] = f[i];
        f[i] = temp;
    }

    return f;
}

size_t obst_cost(node *f, size_t maxlen)
{
    size_t i, row, col, len, sum, tmpcost, cost[maxlen][maxlen];

    inorder(f, maxlen);

    for(len = 0; len < maxlen; ++len)
        for(row = 0; row < maxlen; ++row){
            col = row + len;
            if(col >= maxlen) continue;

            cost[row][col] = ~(size_t)0u;

            for(i = row, sum = 0; i <= col; ++i) sum += f[i].freq;

            for(i = row; i <= col; ++i){
                tmpcost = sum + (i > row ? cost[row][i - 1] : 0) +
                                (i < col ? cost[i + 1][col] : 0) ;
                if(tmpcost < cost[row][col]) cost[row][col] = tmpcost;
            }
        }

    return cost[0][maxlen - 1];
}

int main()
{
    size_t i, n;
    node *f;

    puts("Number of nodes?");
    scanf(" %zu%*c", &n);

    f = malloc(sizeof(*f) * n);
    if(!f){
        fprintf(stderr, "Insufficient Memory!\n");
        exit(12);
    }

    puts("Nodes?");
    for(i = 0; i < n; ++i) scanf(" %d%*c", &f[i].d);

    puts("Frequencies?");
    for(i = 0; i < n; ++i) scanf(" %zu%*c", &f[i].freq);

    printf("Cost of Optimal BST is %zu.\n", obst_cost(f, n));
    return 0;
}
/* end of obst_cost.c */

/* OUTPUT

Number of nodes?
13
Nodes?
50 40 30 25 20 35 33 34 36 60 70 65 80
Frequencies?
10 02 31 23 21 04 04 45 06 04 56 10 09
Cost of Optimal BST is 546.

*/
