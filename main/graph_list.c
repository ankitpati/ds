/* graph_list.c */
/* Date  : 04 April 2016
 * Author: Ankit Pati
 */

#include <stdio.h>
#include <stdlib.h>

typedef int data;

typedef struct Edge{
    struct Node *n;
    struct Edge *next;
} *edge;

typedef struct Node{
    data d;
    struct Node *next;
    edge edg;
} *node;

node first = NULL;

node insert(data d)
{
    node temp, newnode;

    newnode = malloc(sizeof(*newnode));
    if(!newnode) exit(12);
    newnode->d = d;
    newnode->next = NULL;
    newnode->edg = NULL;

    if(!first){
        first = newnode;
        return newnode;
    }

    for(temp = first; temp->next; temp = temp->next)
        if(temp->d == d){
            free(newnode);
            return temp;
        }

    if(temp->d == d){
        free(newnode);
        return temp;
    }

    temp->next = newnode;
    return newnode;
}

void delet(data d)
{
    node n, nprev;
    edge e, eprev;

    for(n = first; n; n = n->next){
        if(!n->edg) continue;

        if(n->edg->n->d == d){
            e = n->edg;
            n->edg = n->edg->next;
            free(e);
            continue;
        }

        eprev = n->edg;
        e = n->edg->next;
        while(e)
            if(e->n->d == d){
                eprev->next = e->next;
                free(e);
                e = eprev->next;
            }
            else{
                eprev = e;
                e = e->next;
            }
    }

    if(!first) return;

    if(first->d == d){
        n = first;
        first = first->next;
        goto cleanup;
    }

    for(nprev = first, n = first->next; n && n->d != d; nprev = n, n = n->next);
    if(n->d == d){
        nprev->next = n->next;
        goto cleanup;
    }

    return;

cleanup:
    while(n->edg){
        e = n->edg;
        n->edg = n->edg->next;
        free(e);
    }

    free(n);
}

void directed_insert_edge(data from, data to)
{
    node n;
    edge e, newedge;

    insert(from);

    newedge = malloc(sizeof(*newedge));
    if(!newedge) exit(12);
    newedge->n = insert(to);
    newedge->next = NULL;

    for(n = first; n->d != from; n = n->next);

    if(!n->edg){
        n->edg = newedge;
        return;
    }

    for(e = n->edg; e->next; e = e->next);
    e->next = newedge;
}

void directed_delet_edge(data from, data to)
{
    node n;
    edge e, eprev;

    for(n = first; n && n->d != from; n = n->next);

    if(!n) return;

    if(!n->edg) return;

    if(n->edg->n->d == to){
        e = n->edg;
        n->edg = n->edg->next;
        free(e);
        return;
    }

    for(
        eprev = n->edg, e = n->edg->next;
        e && e->n->d != to;
        eprev = e, e = e->next
    );
    if(e->n->d == to){
        eprev->next = e->next;
        free(e);
    }
}

void undirected_insert_edge(data from, data to)
{
    if(from == to) directed_insert_edge(from, to);
    else{
        directed_insert_edge(from, to);
        directed_insert_edge(to, from);
    }
}

void undirected_delet_edge(data from, data to)
{
    if(from == to) directed_delet_edge(from, to);
    else{
        directed_delet_edge(from, to);
        directed_delet_edge(to, from);
    }
}

void display()
{
    node n;
    edge e;

    for(n = first; n; n = n->next){
        printf("[%d]", n->d);
        for(e = n->edg; e; e = e->next) printf(" -> %d", e->n->d);
        putchar('\n');
    }
}

int main()
{
    int ch;
    data d, f, t;

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
            insert(d);
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

            directed_insert_edge(f, t);
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

            undirected_insert_edge(f, t);
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
/* end of graph_list.c */

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
[43]
[64]
[55]

3
From?
43
To?
55

3
From?
43
To?
64

7
[43] -> 55 -> 64
[64]
[55]

2
Node?
55

7
[43] -> 64
[64]

0

*/
