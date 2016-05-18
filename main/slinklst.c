/* slinklst.c */
/* Date  : 18 January 2016
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

void invert()
{
    node c, prev, temp;

    if(!first) return;

    c = first->next;
    first->next = NULL;

    for(prev = first; c; c = temp){
        temp = c->next;
        c->next = prev;
        prev = c;
    }

    first = prev;
}

void insert(size_t pos, data d)
{
    size_t i;
    node prev, newnode;

    newnode = malloc(sizeof(*newnode));
    if(!newnode) exit(12);
    newnode->d = d;

    if(!first){
        newnode->next = NULL;
        first = newnode;
        return;
    }

    if(!pos){
        newnode->next = first;
        first = newnode;
        return;
    }

    --pos;

    for(i = 0, prev = first; i < pos && prev->next; ++i, prev = prev->next);

    newnode->next = prev->next;
    prev->next = newnode;
}

data delet(size_t pos)
{
    size_t i;
    data d;
    node tmp, prev;

    if(!first) return -1;

    if(!first->next){
        d = first->d;
        free(first);
        first = NULL;
        return d;
    }

    if(!pos){
        d = first->d;
        tmp = first->next;
        free(first);
        first = tmp;
        return d;
    }

    --pos;

    for(
        i = 0, prev = first, tmp = first->next;
        i < pos && tmp->next;
        ++i, prev = tmp, tmp = tmp->next
    );

    d = tmp->d;
    prev->next = tmp->next;
    free(tmp);

    return d;
}

int main()
{
    unsigned ch1, ch2;
    size_t pos;
    data d;

    do{
        puts("What would you like to do?");
        puts(" ( 0) Exit");
        puts(" ( 1) Insert");
        puts(" ( 2) Delete");
        puts(" ( 3) Traverse");
        puts(" ( 4) Invert");
        scanf(" %u%*c", &ch1);
        switch(ch1){
        case 0:
            puts("Bye!");
            break;
        case 1:
            do{
                puts("Insert where?");
                puts(" ( 0) Back to previous menu");
                puts(" ( 1) Beginning");
                puts(" ( 2) Middle");
                puts(" ( 3) End");
                scanf(" %u%*c", &ch2);
                switch(ch2){
                case 0:
                    break;
                case 1:
                    puts("Data?");
                    scanf(" %d%*c", &d);
                    insert(0, d);
                    break;
                case 2:
                    puts("Position?");
                    scanf(" %zu%*c", &pos);
                    puts("Data?");
                    scanf(" %d%*c", &d);
                    insert(pos, d);
                    break;
                case 3:
                    puts("Data?");
                    scanf(" %d%*c", &d);
                    insert(~(size_t)0, d);
                    break;
                default:
                    puts("Incorrect Choice!");
                    break;
                }
            } while(ch2);
            break;
        case 2:
            do{
                puts("Delete from where?");
                puts(" ( 0) Back to previous menu");
                puts(" ( 1) Beginning");
                puts(" ( 2) Middle");
                puts(" ( 3) End");
                scanf(" %u%*c", &ch2);
                switch(ch2){
                case 0:
                    break;
                case 1:
                    d = delet(0);
                    if(d == -1) puts("List empty.");
                    else printf("%d\n", d);
                    break;
                case 2:
                    puts("Position?");
                    scanf(" %zu%*c", &pos);
                    d = delet(pos);
                    if(d == -1) puts("List empty.");
                    else printf("%d\n", d);
                    break;
                case 3:
                    d = delet(~(size_t)0);
                    if(d == -1) puts("List empty.");
                    else printf("%d\n", d);
                    break;
                default:
                    puts("Incorrect Choice!");
                    break;
                }
            } while(ch2);
            break;
        case 3:
            traverse();
            break;
        case 4:
            invert();
            break;
        default:
            puts("Incorrect Choice!");
            break;
        }
        putchar('\n');
    } while(ch1);
    return 0;
}
/* end of slinklst.c */

/* OUTPUT

What would you like to do?
 ( 0) Exit
 ( 1) Insert
 ( 2) Delete
 ( 3) Traverse
 ( 4) Invert

    1
    Insert where?
     ( 0) Back to previous menu
     ( 1) Beginning
     ( 2) Middle
     ( 3) End

    1
    Data?
    43

    3
    Data?
    50

    2
    Position?
    1
    Data?
    86

    0

3
43 86 50

    2
    Delete from where?
     ( 0) Back to previous menu
     ( 1) Beginning
     ( 2) Middle
     ( 3) End

    3
    50

    0

4

3
86 43

0
Bye!

*/
