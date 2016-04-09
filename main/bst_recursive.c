/* bst-recursive.c */
/* Date  : 22 February 2016
 * Author: Ankit Pati
 */

#include <stdio.h>
#include <stdlib.h>

typedef int data;

typedef struct Node{
    data d;
    struct Node *left, *right;
} *node;

node root = NULL;

/* count nodes */
size_t count_core(node n, size_t c)
{
    return n ? c + 1 + count_core(n->left, 0) + count_core(n->right, 0) : c;
}

size_t count()
{
    return count_core(root, 0);
}
/* end of count nodes */

/* count leaf */
size_t count_leaf_core(node n, size_t c)
{
    return n ? n->left || n->right ? c + count_leaf_core(n->left, 0) +
                                       count_leaf_core(n->right, 0) : c + 1 : c;
}

size_t count_leaf()
{
    return count_leaf_core(root, 0);
}
/* end of count leaf */

/* recursive preorder */
void pre_ord_core(node n)
{
    if(!n) return;
    printf("%d ", n->d);
    pre_ord_core(n->left);
    pre_ord_core(n->right);
}

void pre_ord()
{
    pre_ord_core(root);
}
/* end of recursive preorder */

/* recursive inorder */
void in_ord_core(node n)
{
    if(!n) return;
    in_ord_core(n->left);
    printf("%d ", n->d);
    in_ord_core(n->right);
}

void in_ord()
{
    in_ord_core(root);
}
/* end of recursive inorder */

/* recursive postorder */
void post_ord_core(node n)
{
    if(!n) return;
    post_ord_core(n->left);
    post_ord_core(n->right);
    printf("%d ", n->d);
}

void post_ord()
{
    post_ord_core(root);
}
/* end of recursive postorder */

/* recursive insert */
void insert_core(node prev, node c, data d)
{
    if(!c){
        c = malloc(sizeof(*c));
        if(!c) exit(12);
        c->left = c->right = NULL;
        c->d = d;

             if(!prev      ) root        = c;
        else if(d < prev->d) prev->left  = c;
        else if(d > prev->d) prev->right = c;
    }
    else if(d < c->d) insert_core(c, c->left, d);
    else if(d > c->d) insert_core(c, c->right, d);
}

void insert(data d)
{
    insert_core(NULL, root, d);
}
/* end of recursive insert */

/* recursive delete */
node min_parent(node c) /* parent of minimum node (inorder successor) */
{
    return c->left && c->left->left ? min_parent(c->left) : c;
}

data delet_core(node prev, node c, data d)
{
    node temp;

    if(!c) return -1;

    else if(d < c->d) return delet_core(c, c->left , d);
    else if(d > c->d) return delet_core(c, c->right, d);

    else if(c->right && c->left){
        temp = min_parent(c->right);

             if(c == root      ) root        = temp->left ? temp->left : temp;
        else if(prev->left == c) prev->left  = temp->left ? temp->left : temp;
        else                     prev->right = temp->left ? temp->left : temp;

        if(temp->left){
            prev = temp->left->right;

            temp->left->left  = c->left ;
            temp->left->right = c->right;

            temp->left = prev;
        }
        else temp->left = c->left;
    }

    else{
             if(c == root       ) root        = c->right ? c->right : c->left;
        else if(prev->right == c) prev->right = c->right ? c->right : c->left;
        else                      prev->left  = c->right ? c->right : c->left;
    }

    d = c->d;
    free(c);
    return d;
}

data delet(data d)
{
    return delet_core(NULL, root, d);
}
/* end of recursive delete */

/* recursive find */
node find_core(node c, data d)
{
    return c ? d < c->d ? find_core(c->left, d) : d > c->d ?
                                              find_core(c->right, d) : c : NULL;
}

node find(data d)
{
    return find_core(root, d);
}
/* end of recursive find */

/* AVL checking code */
size_t height(node n)
{
    return n ? (height(n->left) > height(n->right) ?
                                    height(n->left) : height(n->right)) + 1 : 0;
}

int isavl_core(node n)
{
    size_t hleft, hright, hdiff;

    if(!n) return 1;

    hleft  = height(n->left );
    hright = height(n->right);
    hdiff  = hleft > hright ? hleft - hright : hright - hleft;

    if(hdiff > 1) return 0;

    return isavl_core(n->left) && isavl_core(n->right);
}

int isavl()
{
    return isavl_core(root);
}
/* end of AVL checking code */

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
        puts("( 7) Check AVL");

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
        case 7:
            printf("Tree is%s AVL.\n", isavl() ? "" : " not");
            break;
        default:
            puts("Incorrect Choice!");
            break;
        }
    } while(ch);

    return 0;
}
/* end of bst-recursive.c */

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

7
Tree is not AVL.

2
30

4
Preorder : 50 40 33 25 20 35 34 36 60 70 65 80
Inorder  : 20 25 33 34 35 36 40 50 60 65 70 80
Postorder: 20 25 34 36 35 33 40 65 80 70 60 50

3
33
Node: 25 <- 33 -> 35

2
20

2
33

2
36

1
41

1
59

4
Preorder : 50 40 34 25 35 41 60 59 70 65 80
Inorder  : 25 34 35 40 41 50 59 60 65 70 80
Postorder: 25 35 34 41 40 59 65 80 70 60 50

7
Tree is AVL.

0

*/
