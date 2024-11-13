#ifndef ACINATOR
#define ACINATOR
#include"stdio.h"
#include"stdlib.h"
#include"assert.h"
#include"D:\STUDYC\My_labraries\colours.h"

const int acinator_str = 30;

struct str_node_t
{
    char data[acinator_str];
    str_node_t* left;
    str_node_t* right;
};

int play_acinator(str_node_t*);
int print_node_graph(str_node_t* node_ptr, char argv[]);
int generate_graph(str_node_t* node_ptr, FILE* file);
str_node_t* str_ctor_node(const char* string);
int dtor_node(str_node_t* node_ptr);

#endif