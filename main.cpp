#include"acinator_functions.h"

int main(int argc, char* argv[])
{
    node_t acin_1 = {};
    ctor_node(&acin_1, 10);
    node_t acin_2 = {};
    ctor_node(&acin_2, 20);
    node_t acin_3 = {};
    ctor_node(&acin_3, 30);
    node_t acin_4 = {};
    ctor_node(&acin_4, 40);
    node_t acin_5 = {};
    ctor_node(&acin_5, 50);
    node_t acin_6 = {};
    ctor_node(&acin_6, 60);

    acin_4.right = &acin_5;
    acin_5.right = &acin_6;
    acin_4.left  = &acin_2;
    acin_2.right = &acin_3;
    acin_2.left  = &acin_1;

    node_dump(&acin_4);
    print_node_graph(&acin_4, argv[argc-1]);
    dtor_node(&acin_4);

    return 0;
}