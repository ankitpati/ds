/* dlinklst.c */
/* Date  : 08 February 2016
 * Author: Ankit Pati
 */

#include <stdio.h>
#include <stdlib.h>

typedef int data;

typedef struct Node{
    data d;
    struct Node *prev, *next;
} *node;

void traverse(node *first)
{
    node tmp;
    for(tmp = *first; tmp; tmp = tmp->next) printf("%d ", tmp->d);
    putchar('\n');
}

void reverse_traverse(node *first)
{
    node last;
    if(!*first) return;
    for(last = *first; last->next; last = last->next);
    do printf("%d ", last->d);
    while((last = last->prev));
    putchar('\n');
}

void insert(node *first, size_t pos, data d)
{
    size_t i;
    node temp, newnode;

    newnode = malloc(sizeof(*newnode));
    if(!newnode) exit(12);
    newnode->d = d;

    if(!*first){
        newnode->next = newnode->prev = NULL;
        *first = newnode;
        return;
    }

    if(!pos){
        newnode->next = *first;
        newnode->prev = NULL;
        (*first)->prev = newnode;
        *first = newnode;
        return;
    }

    --pos;

    for(i = 0, temp = *first; i < pos && temp->next; ++i, temp = temp->next);

    newnode->next = temp->next;
    newnode->prev = temp;
    if(temp->next) temp->next->prev = newnode;
    temp->next = newnode;

}

data delet(node *first, size_t pos)
{
    size_t i;
    data d;
    node temp;

    if(!*first) return -1;

    if(!(*first)->next){
        d = (*first)->d;
        free(*first);
        *first = NULL;
        return d;
    }

    if(!pos){
        d = (*first)->d;
        temp = (*first)->next;
        free(*first);
        *first = temp;
        (*first)->prev = NULL;
        return d;
    }

    for(i = 0, temp = *first; i < pos && temp->next; ++i, temp = temp->next);

    d = temp->d;
    temp->prev->next = temp->next;
    if(temp->next) temp->next->prev = temp->prev;
    free(temp);

    return d;
}

void concat(node *first, node *second)
{
    node prev;

    if(!*second) return;
    if(!*first){
        *first = *second;
        return;
    }

    for(prev = *first; prev->next; prev = prev->next);
    prev->next = *second;
    (*second)->prev = prev;
}

int main()
{
    unsigned ch1, ch2, ch3;
    size_t pos;
    data d;
    node first, second;

    first = second = NULL;

    do{
        puts("Which linked list?");
        puts(" ( 0) Exit");
        puts(" ( 1) First");
        puts(" ( 2) Second");
        scanf(" %u%*c", &ch3);
        if(!ch3) continue;
        if(ch3 > 2){
            puts("Incorrect Choice!");
            continue;
        }
        do{
            puts("What would you like to do?");
            puts(" ( 0) Back to previous menu");
            puts(" ( 1) Insert");
            puts(" ( 2) Delete");
            puts(" ( 3) Traverse");
            puts(" ( 4) Reverse Traverse");
            puts(" ( 5) Concatenate");
            scanf(" %u%*c", &ch1);
            switch(ch1){
            case 0:
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
                        insert(ch3 == 1 ? &first : &second, 0, d);
                        break;
                    case 2:
                        puts("Position?");
                        scanf(" %zu%*c", &pos);
                        puts("Data?");
                        scanf(" %d%*c", &d);
                        insert(ch3 == 1 ? &first : &second, pos, d);
                        break;
                    case 3:
                        puts("Data?");
                        scanf(" %d%*c", &d);
                        insert(ch3 == 1 ? &first : &second, ~(size_t)0, d);
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
                        d = delet(ch3 == 1 ? &first : &second, 0);
                        if(d == -1) puts("List empty.");
                        else printf("%d\n", d);
                        break;
                    case 2:
                        puts("Position?");
                        scanf(" %zu%*c", &pos);
                        d = delet(ch3 == 1 ? &first : &second, pos);
                        if(d == -1) puts("List empty.");
                        else printf("%d\n", d);
                        break;
                    case 3:
                        d = delet(ch3 == 1 ? &first : &second, ~(size_t)0);
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
                traverse(ch3 == 1 ? &first : &second);
                break;
            case 4:
                reverse_traverse(ch3 == 1 ? &first : &second);
                break;
            case 5:
                concat(&first, &second);
                break;
            default:
                puts("Incorrect Choice!");
                break;
            }
            putchar('\n');
        } while(ch1);
        putchar('\n');
    } while(ch3);
    return 0;
}
/* end of dlinklst.c */

/* OUTPUT

Which linked list?
 ( 0) Exit
 ( 1) First
 ( 2) Second

    1
    What would you like to do?
     ( 0) Back to previous menu
     ( 1) Insert
     ( 2) Delete
     ( 3) Traverse
     ( 4) Reverse Traverse
     ( 5) Concatenate

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

    4
    50 86 43

        2
        Delete from where?
         ( 0) Back to previous menu
         ( 1) Beginning
         ( 2) Middle
         ( 3) End

        3
        50

        0

    3
    43 86

    0

    2

    1

    1
    42

    3
    51

    0

    3
    42 51

    0

    1

    5

    3
    43 86 42 51

0
Bye!

*/
