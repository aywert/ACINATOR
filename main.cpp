#include"acinator_functions.h"

int main(int argc, char* argv[])
{
    node_t* acin_1 = ctor_node(10);
    node_t* acin_2 = ctor_node(20);
    node_t* acin_3 = ctor_node(30);
    node_t* acin_4 = ctor_node(40);
    node_t* acin_5 = ctor_node(50);
    node_t* acin_6 = ctor_node(60);
    node_t* acin_7 = ctor_node(35);
    node_t* acin_8 = ctor_node(355);
    node_t* acin_9 = ctor_node(55);

    // acin_4->right = acin_5;
    // acin_5->right = acin_6;
    // acin_4->left  = acin_2;
    // acin_2->right = acin_3;
    // acin_2->left  = acin_1;

    attach_node(acin_4, acin_3);
    attach_node(acin_4, acin_1);
    attach_node(acin_4, acin_2);
    attach_node(acin_4, acin_5);
    attach_node(acin_4, acin_6);
    attach_node(acin_4, acin_7);
    attach_node(acin_4, acin_8);
    attach_node(acin_4, acin_9);
    
    print_node_graph(acin_4, argv[argc-1]);
    printf("dead");
    node_dump(acin_4);
    dtor_node(acin_1);
    dtor_node(acin_2);
    dtor_node(acin_3);
    dtor_node(acin_5);
    dtor_node(acin_6);
    dtor_node(acin_7);
    dtor_node(acin_8);
    dtor_node(acin_9);

    return 0;
}