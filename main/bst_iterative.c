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
    size_t top, cnt;
    node c, stack[MAX_NODES];

    for(top = cnt = 0, c = root; top || c; c = stack[--top])
        if(c){
            ++cnt;
            stack[top++] = c->right;
            stack[top++] = c->left ;
        }

    return cnt;
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

void pre_ord(node root)
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

void in_ord(node root)
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

void post_ord(node root)
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

void delet(data d)
{
    node del_parent, min_parent, c, m;

    for(c = root; c && c->d != d; c = d < c->d ? c->left : c->right)
        del_parent = c;

    if(!c) return;

    if(!c->right) m = c->left;
    else{
        for(min_parent = c, m = c->right; m->left; m = m->left) min_parent = m;

        m->left = c->left;
        min_parent->left = m->right;

        if(c->right != m) m->right = c->right;
    }

    if(c == root)
        root = m;
    else if(del_parent->left == c)
        del_parent->left = m;
    else
        del_parent->right = m;

    free(c);
}

node find(data d)
{
    node c;
    for(c = root; c && c->d != d; c = d < c->d ? c->left : c->right);
    return c;
}

/* mirroring code */
node m_root = NULL;

void m_insert(data d)
{
    node c, prev, newnode;

    newnode = malloc(sizeof(*newnode));
    if(!newnode) exit(12);
    newnode->d = d;
    newnode->right = newnode->left = NULL;

    if(!m_root){
        m_root = newnode;
        return;
    }

    for(c = m_root; c; c = (c->d > d ? c->right : c->left)){
        if(c->d == d){
            free(newnode);
            return;
        }
        prev = c;
    }

    if(prev->d > d)
        prev->right = newnode;
    else
        prev->left = newnode;
}

void m_delet(data d)
{
    node del_parent, min_parent, c, m;

    for(c = m_root; c && c->d != d; c = d < c->d ? c->right : c->left)
        del_parent = c;

    if(!c) return;

    if(!c->left) m = c->right;
    else{
        for(min_parent = c, m = c->left; m->right; m = m->right) min_parent = m;

        m->right = c->right;
        min_parent->right = m->left;

        if(c->left != m)
            m->left = c->left;
    }

    if(c == m_root)
        m_root = m;
    else if(del_parent->right == c)
        del_parent->right = m;
    else
        del_parent->left = m;

    free(c);
}

node m_find(data d)
{
    node c;
    for(c = m_root; c && c->d != d; c = d < c->d ? c->right : c->left);
    return c;
}

void m_init()
{
    unsigned top;
    node c, stack[MAX_NODES];

    for(top = 0, c = root; top || c; c = stack[--top])
        if(c){
            m_insert(c->d);
            stack[top++] = c->right;
            stack[top++] = c->left ;
        }
}
/* end of mirroring code */

/* AVL code */
size_t height(node root)
{
    size_t i, front, rear, ht;
    node c, queue[MAX_NODES];

    ht = front = rear = 0;

    if(root) queue[rear++] = root;

    for(;;){
        if(rear == front) return ht;
        else ++ht;

        for(i = rear - front; i; --i){
            c = queue[front++];
            if(c->left ) queue[rear++] = c->left ;
            if(c->right) queue[rear++] = c->right;
        }
    }

    return 0;
}

node checkavl() /* return NULL; if AVL */
{
    size_t top;
    node c, prev, stack[MAX_NODES];

    if(!root) return NULL;

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
            if(1 < (height(c->left) > height(c->right) ?
                height(c->left ) - height(c->right) :
                height(c->right) - height(c->left ) )
            ) return c;

            --top;
        }

        prev = c;
    }

    return NULL;
}

void rr(node parent, node c)
{
    node child, tmp;
    child = c->right;
    if(c == root) root = child;
    else if(parent->left  == c)
        parent->left  = child;
    else
        parent->right = child;
    tmp = child->left;
    child->left = c;
    c->right = tmp;
}

void ll(node parent, node c)
{
    node child, tmp;
    child = c->left;
    if(c == root) root = child;
    else if(parent->left  == c)
        parent->left  = child;
    else
        parent->right = child;
    tmp = child->right;
    child->right = c;
    c->left = tmp;
}

void avl_insert(data d)
{
    node c, i, parent;

    insert(d);
    if(!(c = checkavl())) return;

    for(i = root; i != c; i = d < i->d ? i->left : i->right) parent = i;

    if(height(c->left) > height(c->right)){
        if(c->left->right && c->left->right->d == d) rr(c, c->left);
        ll(parent, c);
    }
    else{
        if(c->right->left && c->right->left->d == d) ll(c, c->right);
        rr(parent, c);
    }
}
/* end of AVL code */

int main()
{
    int ch;
    data d;
    node c;

    puts("What would you like to do?");
    puts("( 0) Exit");
    puts("( 1) Insert");
    puts("( 2) Delete");
    puts("( 3) Find");
    puts("( 4) Traverse");
    puts("( 5) Count Nodes");
    puts("( 6) Count Leaves");
    puts("( 7) Check AVL");
    puts("( 8) AVL Insert");
    puts("( 9) Mirror Tree");
    puts("(10) Mirror Insert");
    puts("(11) Mirror Delete");
    puts("(12) Mirror Find");
    puts("(13) Mirror Traverse");

    do{
        printf("?> ");
        fflush(stdout);
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
            printf("Preorder : "); pre_ord (root); putchar('\n');
            printf("Inorder  : "); in_ord  (root); putchar('\n');
            printf("Postorder: "); post_ord(root); putchar('\n');
            break;
        case 5:
            printf("Node Count: %zu\n", count());
            break;
        case 6:
            printf("Leaf Count: %zu\n", count_leaf());
            break;
        case 7:
            printf("Tree is%s AVL.\n", checkavl() ? " not" : "");
            break;
        case 8:
            puts("Value?");
            scanf(" %d%*c", &d);
            avl_insert(d);
            break;
        case 9:
            m_init();
            break;
        case 10:
            puts("Value?");
            scanf(" %d%*c", &d);
            m_insert(d);
            break;
        case 11:
            puts("Value?");
            scanf(" %d%*c", &d);
            m_delet(d);
            break;
        case 12:
            puts("Value?");
            scanf(" %d%*c", &d);
            c = m_find(d);
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
        case 13:
            printf("Preorder : "); pre_ord (m_root); putchar('\n');
            printf("Inorder  : "); in_ord  (m_root); putchar('\n');
            printf("Postorder: "); post_ord(m_root); putchar('\n');
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
( 5) Count Nodes
( 6) Count Leaves
( 7) Check AVL
( 8) AVL Insert
( 9) Mirror Tree
(10) Mirror Insert
(11) Mirror Delete
(12) Mirror Find
(13) Mirror Traverse

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
