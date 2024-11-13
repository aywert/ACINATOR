#ifndef BIN_TREE
#define BIN_TREE

#include"stdio.h"
#include"stdlib.h"
#include"assert.h"

struct node_t
{
    int data;
    node_t* left;
    node_t* right;
};

node_t* ctor_node(int value);
int attach_node(node_t* root, node_t* node);
int compare_tree_value(node_t* root, int value);
int node_dump(node_t* node_ptr);
int print_node_graph(node_t* node_ptr, char argv[]);
int generate_graph(node_t* node_ptr, FILE* file);
int dtor_node(node_t* node_ptr);

#endif