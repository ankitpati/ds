/* bst-iterative.c */
/* Date  : 22 February 2016
 * Author: Ankit Pati
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 100

typedef int data;

typedef struct Node{
    data d;
    struct Node *left, *right;
} *node;

node root = NULL;

size_t count()
{
    size_t top, ret;
    node c, stack[MAX_NODES];

    for(top = ret = 0, c = root; top || c; c = stack[--top])
        if(c){
            ++ret;
            stack[top++] = c->right;
            stack[top++] = c->left ;
        }

    return ret;
}

size_t count_leaf()
{
    size_t top, leaf;
    node c, stack[MAX_NODES];

    for(top = leaf = 0, c = root; top || c; c = stack[--top])
        if(c){
            if(!c->left && !c->right) ++leaf;
            stack[top++] = c->right;
            stack[top++] = c->left ;
        }

    return leaf;
}

void pre_ord()
{
    size_t top;
    node c, stack[MAX_NODES];

    for(top = 0, c = root; top || c; c = stack[--top])
        if(c){
            printf("%d ", c->d);
            stack[top++] = c->right;
            stack[top++] = c->left ;
        }
}

void in_ord()
{
    size_t top;
    node c, stack[MAX_NODES];

    for(top = 0, c = root; top || c; )
        if(c){
            stack[top++] = c;
            c = c->left;
        }
        else{
            c = stack[--top];
            printf("%d ", c->d);
            c = c->right;
        }
}

void post_ord()
{
    size_t top;
    node c, prev, stack[MAX_NODES];

    if(!root) return;

    top = 0;
    stack[top++] = root;
    prev = NULL;

    while(top){
        c = stack[top - 1];

        if(!prev || prev->left == c || prev->right == c){
                 if(c->left ) stack[top++] = c->left ;
            else if(c->right) stack[top++] = c->right;
        }

        else if(c->left == prev){
            if(c->right) stack[top++] = c->right;
        }

        else{
            printf("%d ", c->d);
            --top;
        }

        prev = c;
    }
}

void insert(data d)
{
    node c, prev, newnode;

    newnode = malloc(sizeof(*newnode));
    if(!newnode) exit(12);
    newnode->d = d;
    newnode->left = newnode->right = NULL;

    if(!root){
        root = newnode;
        return;
    }

    for(c = root; c; c = (c->d > d ? c->left : c->right)){
        if(c->d == d){
            free(newnode);
            return;
        }
        prev = c;
    }

    if(prev->d > d)
        prev->left = newnode;
    else
        prev->right = newnode;
}

data delet(data d)
{
    node del_parent, min_parent, c, m;

    for(
        c = root;
        c && c->d != d;
        c = d < c->d ? c->left : c->right
    ) del_parent = c;

    if(!c) return -1;

    if(!c->right){
        m = c->left;
        goto finaldel;
    }

    for(min_parent = c, m = c->right; m->left; m = m->left) min_parent = m;

    m->left = c->left;
    min_parent->left = m->right;

    if(c->right != m)
        m->right = c->right;

finaldel:
    if(c == root)
        root = m;
    else if(del_parent->left == c)
        del_parent->left = m;
    else
        del_parent->right = m;

    d = c->d;
    free(c);
    return d;
}

node find(data d)
{
    node c;
    for(c = root; c && c->d != d; c = d < c->d ? c->left : c->right);
    return c;
}

int main()
{
    int ch;
    data d;
    node c;

    do{
        puts("What would you like to do?");
        puts("( 0) Exit");
        puts("( 1) Insert");
        puts("( 2) Delete");
        puts("( 3) Find");
        puts("( 4) Traverse");
        puts("( 5) Count Nodes");
        puts("( 6) Count Leaves");

        scanf(" %d%*c", &ch);

        switch(ch){
        case 0:
            break;
        case 1:
            puts("Value?");
            scanf(" %d%*c", &d);
            insert(d);
            break;
        case 2:
            puts("Value?");
            scanf(" %d%*c", &d);
            delet(d);
            break;
        case 3:
            puts("Value?");
            scanf(" %d%*c", &d);
            c = find(d);
                 if(!c) puts("Node not found.");
            else if(c->left && c->right)
                printf("Node: %d <- %d -> %d\n", c->left->d, c->d, c->right->d);
            else if(c->left)
                printf("Node: %d <- %d -> NULL\n", c->left->d, c->d);
            else if(c->right)
                printf("Node: NULL <- %d -> %d\n", c->d, c->right->d);
            else
                printf("Node: NULL <- %d -> NULL\n", c->d);
            break;
        case 4:
            printf("Preorder : "); pre_ord (); putchar('\n');
            printf("Inorder  : "); in_ord  (); putchar('\n');
            printf("Postorder: "); post_ord(); putchar('\n');
            break;
        case 5:
            printf("Node Count: %zu\n", count());
            break;
        case 6:
            printf("Leaf Count: %zu\n", count_leaf());
            break;
        default:
            puts("Incorrect Choice!");
            break;
        }
    } while(ch);

    return 0;
}
/* end of bst-iterative.c */

/* OUTPUT

Required Tree:
       50
     /    \
    40    60
    /      \
   30      70
  /  \     / \
 25  35   65 80
 /   / \
20  33 36
     \
     34

What would you like to do?
( 0) Exit
( 1) Insert
( 2) Delete
( 3) Find
( 4) Traverse

1
50

1
40

1
60

1
30

1
70

1
35

1
25

1
65

1
20

1
80

1
36

1
33

1
34

4
Preorder : 50 40 30 25 20 35 33 34 36 60 70 65 80
Inorder  : 20 25 30 33 34 35 36 40 50 60 65 70 80
Postorder: 20 25 34 33 36 35 30 40 65 80 70 60 50

5
Node Count: 13

6
Leaf Count: 5

2
30

4
Preorder : 50 40 33 25 20 35 34 36 60 70 65 80
Inorder  : 20 25 33 34 35 36 40 50 60 65 70 80
Postorder: 20 25 34 36 35 33 40 65 80 70 60 50

3
33
Node: 25 <- 33 -> 35

0

*/
