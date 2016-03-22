/* clinklst.c */
/* Date  : 01 February 2016
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

void traverse(size_t num)
{
    size_t i;
    node tmp;
    if(!first) return;
    for(i = 0, tmp = first; i < num; tmp = tmp->next){
        if(tmp->next == first) ++i;
        printf("%d ", tmp->d);
    }
    putchar('\n');
}

void insert(size_t pos, data d)
{
    size_t i;
    node prev, newnode;

    newnode = malloc(sizeof(*newnode));
    if(!newnode) exit(12);
    newnode->d = d;

    if(!first){
        newnode->next = first;
        first = newnode;
        return;
    }

    if(!pos){
        for(prev = first; prev->next != first; prev = prev->next);
        prev->next = newnode;
        newnode->next = first;
        first = newnode;
        return;
    }

    --pos;

    for(
        i = 0, prev = first;
        i < pos && prev->next != first;
        ++i, prev = prev->next
    );

    newnode->next = prev->next;
    prev->next = newnode;
}

data delet(size_t pos)
{
    size_t i;
    data d;
    node tmp, prev;

    if(!first) return -1;

    if(first->next == first){
        d = first->d;
        free(first);
        first = NULL;
        return d;
    }

    if(!pos){
        d = first->d;
        tmp = first->next;
        for(prev = first; prev->next != first; prev = prev->next);
        prev->next = tmp;
        free(first);
        first = tmp;
        return d;
    }

    --pos;

    for(
        i = 0, prev = first, tmp = first->next;
        i < pos && tmp->next != first;
        ++i, prev = tmp, tmp = tmp->next
    );

    d = tmp->d;
    prev->next = tmp->next;
    free(tmp);

    return d;
}

size_t search(data key)
{
    size_t pos;
    node tmp;

    if(!first) return ~(size_t)0;

    pos = 0;
    tmp = first;
    do{
        if(tmp->d == key) return pos;
        tmp = tmp->next;
        ++pos;
    } while(tmp != first);

    return ~0;
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
        puts(" ( 3) Search");
        puts(" ( 4) Traverse");
        puts(" ( 5) Circular Traverse");
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
            puts("Key?");
            scanf(" %d%*c", &d);
            pos = search(d);
            if(pos == ~(size_t)0) puts("Not found.");
            else printf("Found at index %zu.\n", pos);
            break;
        case 4:
            traverse(1);
            break;
        case 5:
            puts("Number of Traversals?");
            scanf(" %zu%*c", &pos);
            traverse(pos);
            break;
        default:
            puts("Incorrect Choice!");
            break;
        }
        putchar('\n');
    } while(ch1);
    return 0;
}
/* end of clinklst.c */

/* OUTPUT

What would you like to do?
 ( 0) Exit
 ( 1) Insert
 ( 2) Delete
 ( 3) Search
 ( 4) Traverse
 ( 5) Circular Traverse

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

4
43 86 50

3
Key?
43
Found at index 0.

    2
    Delete from where?
     ( 0) Back to previous menu
     ( 1) Beginning
     ( 2) Middle
     ( 3) End

    3
    50

    0

5
Number of Traversals?
2
43 86 43 86

0
Bye!

*/
