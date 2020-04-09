#ifndef _lcthw_bstree_h
#define _lcthw_bstree_h

typedef int (*Bstree_compare) (void *a, void *b);

typedef struct BstreeNode {
    void *key;
    void *data;
    struct BstreeNode *left;
    struct BstreeNode *right;
    struct BstreeNode *parent;
} BstreeNode;

typedef struct Bstree{
    int count; 
    Bstree_compare compare;
    BstreeNode *root;
} Bstree;

typedef int (*Bstree_traverse_cb) (BstreeNode *node);

Bstree *Bstree_create(Bstree_compare compare);
void Bstree_destroy(Bstree *map);

int Bstree_set(Bstree *map,void *key,void *data);
void *Bstree_get(Bstree *map,void *key);

int Bstree_traverse(Bstree *map,Bstree_traverse_cb traverse_cb);
void *Bstree_delete(Bstree *map,void *key);

#endif
