#include"acinator_functions.h"

int main(int argc, char* argv[])
{
    // const char* string_1 = "Living?";
    // str_node_t* node_1 = str_ctor_node(string_1);
    // const char* string_2 = "Human being?";
    // str_node_t* node_2 = str_ctor_node(string_2);
    // const char* string_3 = "KPM?";
    // str_node_t* node_3 = str_ctor_node(string_3);
    // const char* string_6 = "you won";
    // str_node_t* node_6 = str_ctor_node(string_6);
    // const char* string_7 = "Phystech Bio";
    // str_node_t* node_7 = str_ctor_node(string_7);
    // const char* string_4 = "DED?";
    // str_node_t* node_4 = str_ctor_node(string_4);
    // const char* string_5 = "Poltorashka?";
    // str_node_t* node_5 = str_ctor_node(string_5);
    // const char* string_8 = "DED";
    // str_node_t* node_8 = str_ctor_node(string_8);
    // const char* string_9 = "no DED";
    // str_node_t* node_9 = str_ctor_node(string_9);
    
    // node_1->right = node_2;
    // node_2->right = node_4;
    // node_2->left  = node_5; 
    // node_1->left  = node_3;
    // node_3->right = node_6; 
    // node_3->left  = node_7; 
    // node_4->right = node_8;
    // node_4->left  = node_9;
    // printf("char = %d\n", sizeof(char));
    // printf("int = %d\n", sizeof(int));
    // printf("int* = %d\n", sizeof(int*));
    // printf("double = %d\n", sizeof(double));
    // printf("double* = %d\n", sizeof(double*));
    // printf("long int* = %d\n", sizeof(long int));
    // printf("long long int = %d\n", sizeof(long long int));
    // printf("long double = %d\n", sizeof(long double));
    // printf("short int = %d\n", sizeof(short int));
    str_node_t* root = start_reading_acinator_data(argv[argc-1]);
    print_node_graph(root, argv[argc-2]);

    start_acinator(root);
    // print_node_graph(node_1, argv[argc-2]);
    return 0;
}