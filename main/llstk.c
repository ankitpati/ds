/* llstk.c */
/* Date  : 22 February 2016
 * Author: Ankit Pati
 */

#include <stdio.h>
#include <stdlib.h>

typedef int data;

typedef struct Node{
    data d;
    struct Node *next;
} *node;

node first = NULL;

void traverse()
{
    node tmp;
    for(tmp = first; tmp; tmp = tmp->next)
        printf("%d ", tmp->d);
    putchar('\n');
}

void push(data d)
{
    node newnode;

    newnode = malloc(sizeof(*newnode));
    if(!newnode) exit(12);
    newnode->d = d;

    if(!first) newnode->next = NULL;
    else       newnode->next = first;

    first = newnode;
}

data pop()
{
    data d;
    node tmp;

    if(!first) return -1;

    d = first->d;
    tmp = first->next;
    free(first);
    first = tmp;

    return d;
}

int main()
{
    unsigned ch;
    data d;

    do{
        puts("What would you like to do?");
        puts(" ( 0) Exit");
        puts(" ( 1) Push");
        puts(" ( 2) Pop");
        puts(" ( 3) Traverse");
        scanf(" %u%*c", &ch);
        switch(ch){
        case 0:
            puts("Bye!");
            break;
        case 1:
            puts("Data?");
            scanf(" %d%*c", &d);
            push(d);
            break;
        case 2:
            d = pop();
            if(d == -1) puts("List empty.");
            else printf("%d\n", d);
            break;
        case 3:
            traverse();
            break;
        default:
            puts("Incorrect Choice!");
            break;
        }
        putchar('\n');
    } while(ch);
    return 0;
}
/* end of llstk.c */

/* OUTPUT

What would you like to do?
 ( 0) Exit
 ( 1) Push
 ( 2) Pop
 ( 3) Traverse

1
Data?
43

1
Data?
50

1
Data?
86

3
86 50 43

2
86

2
50

2
43

2
List empty.

0
Bye!

*/
