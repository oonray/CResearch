#include <lcthw/dbg.h>
#include <lcthw/bstree.h>
#include <stdlib.h>
#include <lcthw/bstrlib.h>

static int default_compare(void *a,void *b){
    return bstrcmp((bstring)a,(bstring)b);
}

Bstree *Bstree_create(Bstree_compare compare){
    Bstree *map = calloc(1,sizeof(Bstree));
    check_mem(map);

    map->compare = compare == NULL ? default_compare : compare;
    return map;
error:
    if(map){
        Bstree_destroy(map);
    }
    return NULL;
}

static int Bstree_destroy_cb(BstreeNode *node){
    free(node);
    return 0;
}

void Bstree_destroy(Bstree *map){
    if(map){
        Bstree_traverse(map,Bstree_destroy_cb);
        free(map);
    }
}

static inline BstreeNode *BstreeNode_create(BstreeNode *parent,void *key,void *data){
    BstreeNode *node = calloc(1,sizeof(BstreeNode));
    check_mem(node);

    node->key=key;
    node->data=data;
    node->parent=parent;
    return node;
error:
    return NULL;
}

static inline void Bstree_setnode(Bstree *map,BstreeNode *node, void *key,void *data){
    int cmp = map->compare(node->key,key);
    if(cmp<=0){
        if(node->left){
            Bstree_setnode(map,node->left,key,data);
        }else{
            node->left = BstreeNode_create(node,key,data);
        }
    }else{
        if(node->right){
            Bstree_setnode(map,node->right,key,data);
        }else{
            node->right = BstreeNode_create(node,key,data);
        }
    }
}

int Bstree_set(Bstree *map,void *key,void *data){
    if(map->root == NULL){
        map->root = BstreeNode_create(NULL,key,data);
        check_mem(map->root);
    }else{
        Bstree_setnode(map,map->root,key,data);
    }
    return 0;
error:
    return 1;
}

static inline BstreeNode *Bstree_getnode(Bstree *map,BstreeNode *node, void *key){
    int cmp = map->compare(node->key,key);
    if(cmp==0){
        return node;
    }else if(cmp <0){
        if(node->left){
            return Bstree_getnode(map,node->left,key);
        }else{return NULL;}
    }else{
        if(node->right){
            return Bstree_getnode(map,node->right,key);
        }else{return NULL;}
    }
}

void *Bstree_get(Bstree *map,void *key){
    if(map->root == NULL){
        return NULL;
    }else{
        BstreeNode *node = Bstree_getnode(map,map->root,key);
        return node == NULL ? NULL:node->data;
    }
}

static inline int Bstree_traverse_nodes(BstreeNode *node,Bstree_traverse_cb traverse_cb){
    int rc = 0;
    if(node->left){
        rc = Bstree_traverse_nodes(node->left,traverse_cb);
        if(rc != 0){
            return rc;
        }
    }
    if(node->right){
        rc = Bstree_traverse_nodes(node->right,traverse_cb);
        if(rc != 0){
            return rc;
        }
    }
    return traverse_cb(node);
}

int Bstree_traverse(Bstree *map,Bstree_traverse_cb traverse_cb){
    if(map->root){
        return Bstree_traverse_nodes(map->root,traverse_cb);
    }
    return 0;
}

static inline BstreeNode *Bstree_find_min(BstreeNode *node){
    while(node->left){
        node = node->left;
    }
    return node;
}


static inline void Bstree_replace_node_in_parent(Bstree *map,BstreeNode *node,BstreeNode *new_value){
    if(node->parent){
        if(node == node->parent->left){
            node->parent->left=new_value;
        }else{
            node->parent->right = new_value;
        }
    }else{
        map->root = new_value;
    }
}

static inline void Bstree_swap(BstreeNode *a,BstreeNode *b){
    void *temp = NULL;
    temp = b->key;
    b->key = a->key;
    a->key = temp;
    temp = b->data;
    b->data = a->data;
    a->data = temp;
}

static inline BstreeNode *Bstree_node_delete(Bstree *map,BstreeNode *node,void *key){
    int cmp = map->compare(node->key,key);
    if(cmp <0){
        if(node->left){
            return Bstree_node_delete(map,node->left,key);
        }else{
            return NULL;
        }
    }else if(cmp>0){
       if(node->right){
            return Bstree_node_delete(map,node->right,key);
       }else{
            return NULL;
       }
    }else{
        if(node->left && node->right){
            BstreeNode *successor = Bstree_find_min(node->right);
            Bstree_swap(successor,node);
            Bstree_replace_node_in_parent(map,successor,successor->right);
            return successor;
        }else if(node->left){
           Bstree_replace_node_in_parent(map,node,node->left);
        }else if(node->right){
            Bstree_replace_node_in_parent(map,node,node->right);
        }else{
            Bstree_replace_node_in_parent(map,node,NULL);
        }
        return node;
    }
}

void *Bstree_delete(Bstree *map,void *key){
    void *data = NULL;

    if(map->root){
        BstreeNode *node = Bstree_node_delete(map,map->root,key);
        if(node){
            data = node->data;
            free(node);
        }
    }
    return data;
}
