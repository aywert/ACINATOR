#include"acinator_functions.h"

int ctor_node(node_t* node_ptr, int value)
{
    assert(node_ptr);

    node_ptr->data  = value;
   
    node_ptr->right = 0;
    node_ptr->left  = 0;  

    return 0; 
}

int dtor_node(node_t* node_ptr)
{
    assert(node_ptr);
    printf("dead here\n");
    free(node_ptr);
    printf("dead here2");
    return 0; 
}

int node_dump(node_t* node_ptr)
{
    assert(node_ptr);
    printf("(");
    printf("%d", node_ptr->data);

    if (node_ptr->left)  node_dump(node_ptr->left);
    else printf("()");

    if (node_ptr->right) node_dump(node_ptr->right);
    else printf("()");

    printf(")");

    return 0;
}

int print_node_graph(node_t* node_ptr, char argv[])
{
    FILE* file = fopen(argv, "w");
    fprintf(file, "digraph list\n{\nrankdir=HR;\n\t");

    generate_graph(node_ptr, file);

    fprintf(file, "}");
    fclose(file); file = NULL;
    system("dot -T png log_folder_acinator//acinator_graph.dot -o  log_folder_acinator//acinator_graph.png");
    return 0;
}

int generate_graph(node_t* node_ptr, FILE* file)
{
    static int label = 0;
    printf("label = %d\n", label);
    fprintf(file, "%d [shape=record, label = \" data = %d| {left = %p| right = %p}\"];\n\t", (int)&node_ptr->data, node_ptr->data, node_ptr->left, node_ptr->right);
    if (label != 0)
    {
        fprintf(file, "%d -> %d\n\t", label, (int)&node_ptr->data);
    }

    if (node_ptr->left)
    {
        label = (int)&node_ptr->data;
        generate_graph(node_ptr->left, file);
    }
    //else fprintf(file, "()");

    if (node_ptr->right) 
    {
        label = (int)&node_ptr->data;
        generate_graph(node_ptr->right, file);
    }
    //else printf("()");
    return 0;
}