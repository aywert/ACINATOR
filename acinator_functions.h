#ifndef ACINATOR
#define ACINATOR
#include"stdio.h"
#include"stdlib.h"
#include"assert.h"
#include"string.h"
#include"D:\STUDYC\My_labraries\colours.h"

const int acinator_str = 30;

enum ACINATOR_PRINT_MODE
{
    QUESTION = 0,
    STATEMENT = 1,
};

struct str_node_t
{
    str_node_t* parent;
    char data[acinator_str];
    str_node_t* left;
    str_node_t* right;
};


str_node_t* str_ctor_node(const char* string);
int dtor_node(str_node_t* node_ptr);
str_node_t* start_reading_acinator_data(char argv[]);
int start_acinator(str_node_t*);
int play_acinator(str_node_t* root);
int print_node_graph(str_node_t* node_ptr, char argv[]);

#endif