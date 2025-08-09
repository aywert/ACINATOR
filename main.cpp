#include"acinator_functions.h"

int main(int argc, char* argv[])
{
    str_node_t* root = start_reading_acinator_data(argv[argc-1]);
    
    print_node_graph(root, argv[argc-2]);

    start_acinator(root, argv[argc-1]);
    return 0;
}