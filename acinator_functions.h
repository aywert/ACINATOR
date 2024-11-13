#ifndef ACINATOR
#define ACINATOR
#include"stdio.h"
#include"stdlib.h"
#include"assert.h"
#include"string.h"
#include"D:\STUDYC\My_labraries\colours.h"

const int acinator_str = 30;

struct str_node_t
{
    char data[acinator_str];
    str_node_t* left;
    str_node_t* right;
};

int give_definition(str_node_t* root, const char* string);
int print_acinator(const char* string);
str_node_t* read_acinator_data(FILE* acinator_data);
int play_acinator(str_node_t*);
int generate_gameplay(str_node_t* root);
int print_node_graph(str_node_t* node_ptr, char argv[]);
int generate_graph(str_node_t* node_ptr, FILE* file);
str_node_t* str_ctor_node(const char* string);
int dtor_node(str_node_t* node_ptr);

#endif