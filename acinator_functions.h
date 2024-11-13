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
    str_node_t* parent;
    char data[acinator_str];
    str_node_t* left;
    str_node_t* right;
};


str_node_t* str_ctor_node(const char* string);
int dtor_node(str_node_t* node_ptr);
int give_definition(str_node_t* root, const char* string);
int print_acinator(const char* string);
str_node_t* start_reading_acinator_data(char argv[]);
int read_acinator_data(FILE* file, str_node_t* prev_node);
int start_acinator(str_node_t*);
int play_acinator(str_node_t* root);
int print_node_graph(str_node_t* node_ptr, char argv[]);
int generate_graph(str_node_t* node_ptr, FILE* file);

#endif