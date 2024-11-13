#include"tree_functions.h"

node_t* ctor_node(int value)
{
    node_t* tempor_ptr_node = (node_t*)calloc(sizeof(node_t), 1);

    tempor_ptr_node->data  = value;
    tempor_ptr_node->right = 0;
    tempor_ptr_node->left  = 0;  

    return tempor_ptr_node; 
}

int attach_node(node_t* root, node_t* node_ptr)
{
    if (compare_tree_value(root, node_ptr->data) > 0)
    {
        if (root->left == 0)
            root->left = node_ptr;
        else
        attach_node(root->left, node_ptr);

        return 0;
    }

    printf("root->data = %d\n", root->data);

    if (compare_tree_value(root, node_ptr->data) < 0)
    {
        if (root->right == 0)
            root->right = node_ptr;
        else
        attach_node(root->right, node_ptr);
        return 0;
    }

    if (compare_tree_value(root, node_ptr->data) == 0)
    {
        printf("same-value-node already exist\n");
        return 0;
    }

    return 0;
}

int compare_tree_value(node_t* root, int value)
{
    return root->data - value;
}

int dtor_node(node_t* node_ptr)
{
    assert(node_ptr);
    free(node_ptr); 
    node_ptr = NULL;
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
    
    fprintf(file, "%d [shape=\"rectangle\", style=\"rounded\", color=\"blue\", label = \" data = %d\n left = %p\n right = %p\"];\n\t", (int)&node_ptr->data, node_ptr->data, node_ptr->left, node_ptr->right);
    if (label != 0)
    {
        fprintf(file, "%d -> %d [color=\"blue\"]\n\t", label, (int)&node_ptr->data);
    }

    if (node_ptr->left)
    {
        label = (int)&node_ptr->data;
        generate_graph(node_ptr->left, file);
    }

    if (node_ptr->right) 
    {
        label = (int)&node_ptr->data;
        generate_graph(node_ptr->right, file);
    }

    return 0;
}