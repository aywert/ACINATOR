#include"acinator_functions.h"

int main(int argc, char* argv[])
{
    str_node_t* root = start_reading_acinator_data(argv[argc-1]);
    //str_node_t* root = start_reading_acinator_data("log_folder_acinator//acinator_data_reserv.txt");
    print_node_graph(root, argv[argc-2]);

    start_acinator(root);

    start_recording_acinator_data(argv[argc-1], root);
    return 0;
}