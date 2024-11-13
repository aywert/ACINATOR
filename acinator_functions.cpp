#include"acinator_functions.h"

//TODO definition
//TODO comparison

str_node_t* start_reading_acinator_data(char argv[])
{
    assert(argv);
    
    FILE* acinator_data = fopen(argv, "r");
    assert(acinator_data);

    char buffer[acinator_str] = {};
    //"\"%[^\"]"
    fscanf(acinator_data, "%s\n", buffer);
    printf("buffer = %s\n", buffer);
    fscanf(acinator_data, "\"%[^\"]\"", buffer);
    printf("buffer = %s\n", buffer);
    str_node_t* root = str_ctor_node(buffer);
    read_acinator_data(acinator_data, root);

    fclose(acinator_data);
    return root;
}

int read_acinator_data(FILE* file, str_node_t* prev_node)
{
    char buffer[acinator_str] = {};
    int verifier = fscanf(file, "%s\n", buffer);
    printf("buffer = %s\n", buffer);

    if (verifier == EOF)
        return 0;

    if (strcmp(buffer, "{") == 0)
    {
        fscanf(file, "\"%[^\"]\"", buffer);
        printf("buffer = %s\n", buffer);
        str_node_t* root = str_ctor_node(buffer);

        if (prev_node->left == 0)
        {
            prev_node->left = root;
            root->parent = prev_node;
        }

        else if (prev_node->right == 0)
        {
            prev_node->right = root;
            root->parent = prev_node;
        }
        
        else
        {
            printf(RED("Error in binary tree\n"));
            return 0;
        }
       

        read_acinator_data(file, root);
    }

    if (strcmp(buffer, "}") == 0)
    {
        read_acinator_data(file, prev_node->parent);
    }    

    return 0;
}

str_node_t* str_ctor_node(const char* string)
{
    assert(string);
    str_node_t* tempor_ptr_node = (str_node_t*)calloc(sizeof(str_node_t), 1);
    assert(tempor_ptr_node);
    for (int i = 0; i < acinator_str; i++)
    {
        tempor_ptr_node->data[i] = string[i];
    }

    tempor_ptr_node->right = 0;
    tempor_ptr_node->left  = 0;  

    return tempor_ptr_node; 
}

int dtor_node(str_node_t* node_ptr)
{
    assert(node_ptr);
    free(node_ptr); 
    node_ptr = NULL;
    return 0; 
}

int print_node_graph(str_node_t* node_ptr, char argv[])
{
    assert(node_ptr);
    assert(argv);
    FILE* file = fopen(argv, "w");
    fprintf(file, "digraph list\n{\nrankdir=HR;\n\t");

    generate_graph(node_ptr, file);

    fprintf(file, "}");
    fclose(file); file = NULL;
    system("dot -T png log_folder_acinator//acinator_graph.dot -o  log_folder_acinator//acinator_graph.png");
    return 0;
}

int generate_graph(str_node_t* node_ptr, FILE* file)
{
    assert(node_ptr);
    assert(file);
    static int label = 0;
    
    fprintf(file, "%d [shape=\"rectangle\", style=\"rounded\", color=\"blue\", label = \" %s\n left = %p\n right = %p\"];\n\t", (int)&node_ptr->data, node_ptr->data, node_ptr->left, node_ptr->right);
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

int give_definition(str_node_t* root, const char* string)
{
    assert(root);
    assert(string);
    return 0;
}

int start_acinator(str_node_t* root)
{
    assert(root);
    printf(GREEN("=======================================\n"));
    printf(GREEN("ACINATOR is welcoming you!\n"));
    printf(GREEN("=======================================\n"));

    print_acinator("I'm glad to meet you my friend. Wanna play?");
    
    char buffer[acinator_str];
    do
    {
        printf("Enter Yes/No: ");
        scanf("%s", &buffer[0]);
        if (strcmp(buffer, "No") == 0)
        {
            print_acinator("You never gonna know...");
            return 0;
        }
    } while(strcmp(buffer, "Yes") != 0);

    play_acinator(root);

    return 0;
}

int play_acinator(str_node_t* root)
{
    assert(root);
    print_acinator(root->data);
    char buffer[acinator_str];
    do
    {
        printf("Enter Yes/No/Found: ");
        scanf("%s", &buffer[0]);
        if (strcmp(buffer, "No") == 0)
        {
            if (root->left == 0)
            {
                print_acinator("Game is on the stage of development. See ya...");
                return 0;
            }
            play_acinator(root->left);
            break;
        }

        if (strcmp(buffer, "Yes") == 0)
        {
            if (root->right == 0)
            {
                print_acinator("Game is on the stage of development. See ya...");
                return 0;
            }
            play_acinator(root->right);
            break;
        }

        if (strcmp(buffer, "Found") == 0)
        {
            print_acinator("I know everything. Be afraid");
            return 0;
        }
    } while(1);

    return 0;
}

int print_acinator(const char* string)
{
    assert(string);
    printf("                 " RED_BKG("   ")" \n"                                                                                                     
                "                  " RED_BKG("   ")"\n"                                                                  
                "                  " RED_BKG("     ")"\n"                         
                "                    " RED_BKG("   ")WHITE_BKG("               ")"\n"                       
                "                      " RED_BKG("  ")WHITE_BKG("                  ")".                   \n"                       
                "                       " WHITE_BKG("                         ")"                  \n"                      
                "                   :" WHITE_BKG("                   ")YELLOW_BKG("      ")WHITE_BKG("     ")"                \n"                     
                "                 ." WHITE_BKG("                      ")YELLOW_BKG("    ")WHITE_BKG("       ")"                    \n"                     
                "                 " WHITE_BKG("           ")WHITE_BKG("                      ")"\n"                     
                "                 " WHITE_BKG("         ")AQUA_BKG("                       ")"\n"                   
                "                 " WHITE_BKG("      ")YELLOW_BKG("|||||||||||||||||||||||")"            \n"                    
                "                 " WHITE_BKG("   ")PALE_YELLOW_BKG("....")YELLOW_BKG_B("|")BLACK_BKG("\\______/")YELLOW_BKG("||||")BLACK_BKG("\\______/")YELLOW_BKG("||")"              %s\n"                   
                "                 " WHITE_BKG("  ")YELLOW_BKG_B("::")PALE_YELLOW("==&:")YELLOW_BKG_B("|")WHITE_BKG("  ")BLACK_BKG("  ")YELLOW_BKG("----====.")WHITE_BKG("  ")BLACK_BKG("  ")YELLOW_BKG("|||")" \n"                  
                "                  ." WHITE_BKG("  ")YELLOW_BKG_B(":-=")PALE_YELLOW(":")YELLOW_BKG_B("|")WHITE_BKG("    ")YELLOW_BKG("---| |==.")WHITE_BKG("    ")YELLOW_BKG("||")"   \n"                  
                "                   ." WHITE_BKG("  ")YELLOW_BKG_B("-=")PALE_YELLOW("=-")YELLOW_BKG_R("''''''/  \\'''''''")YELLOW_BKG("|\\")"                    \n"                   
                "                     .." YELLOW_BKG_B("||")PALE_YELLOW("--")YELLOW_BKG("||")BLACK_BKG("    ")YELLOW_BKG_R("*-*")BLACK_BKG("   ")YELLOW_BKG("|||||")"                   \n"                  
                "                       " YELLOW_BKG_R("\\\\\\||")BLACK_BKG("   ")YELLOW_BKG_R("|_^^_|")BLACK_BKG("   ")YELLOW_BKG_R("||//")"                   \n"                 
                "                        " YELLOW_BKG_R("\\\\||")BLACK_BKG("  ")YELLOW_BKG_R("|``")BLACK_BKG("  ")YELLOW_BKG_R("``|")BLACK_BKG("  ")YELLOW_BKG_R("||//")"                 \n  "                  
                "                    " BLUE_BKG_V("\\\\\\_     ")YELLOW_BKG_R("\\||||||/")VIOLET_BKG_B(" //")"                      \n"                  
                "                         " BLUE_BKG_V("\\\\_   /")YELLOW_BKG_R("\\---/")VIOLET_BKG_B("   ")"                      \n"                 
                "                           " BLUE_BKG_V("\\__ ///")YELLOW_BKG_R("\\|/")VIOLET_BKG_B("   ")"      \n"                                    
                "                      " BLUE_BKG_V("//=======--")YELLOW_BKG_B("==||\\==")VIOLET_BKG_B("---=====")"      \n"                  
                "                    " BLUE_BKG_V("\\=/=/=/=/=/=-+")YELLOW_BKG_B("+++++++")VIOLET_BKG_B("---=====")"      \n"                
                "               " BLUE_BKG_V("\\/=/=/=/=/=/=/=/=-+")YELLOW_BKG_B("++++++++")VIOLET_BKG_B("---=+=+=+=")"      \n"                 
                "             " BLUE_BKG_V("\\/=/=/=/=/=/=/=/=/=/-+")YELLOW_BKG_B("+++++")VIOLET_BKG_B("---=+=+=+=+=+=")"      \n"               
                "            " BLUE_BKG_V("\\/=/=|=|=|=|=|=|=|=/=/-+")YELLOW_BKG_B("++")VIOLET_BKG_B("---=+=+=+")YELLOW_BKG_B("||||")VIOLET_BKG_B("=+=*-..")"      \n"              
                "            " BLUE_BKG_V("\\/=|=|=|=|=/=-=-=-=/=/-+--")VIOLET_BKG_B("-=+=+=+")YELLOW_BKG_B("||___||_")VIOLET_BKG_B("=+=*-..")"          \n"             
                "            " BLUE_BKG_V("||=\\=|=|=|=\\=-=-=-=/=/-+")YELLOW_BKG_R("=+=+===_\\")YELLOW_BKG_B("||____||_")VIOLET_BKG_B("=+=*-..")"      \n"            
                "            " BLUE_BKG_V("\\\\=\\=|=|=|=\\=\\=-=-=/=/-+--")VIOLET_BKG_B("-=")YELLOW_BKG_R("+\\=\\\\==_=_=\\\\")YELLOW_BKG_B("||_")VIOLET_BKG_B("=+=*-..")"      \n"           
                "            " BLUE_BKG_V("\\\\=\\=\\=\\=\\=+=+=-=-=/=/")YELLOW_BKG_B("||||")VIOLET_BKG_B("-=+=+")YELLOW_BKG_R("\\\\==_=_=_=")YELLOW_BKG_B("||_")VIOLET_BKG_B("=+=*-..")"      \n"          
                "               " BLUE_BKG_V("\\\\=\\===+=+=+=+/=/")YELLOW_BKG_B("||___||")BLUE_BKG_V("_")VIOLET_BKG_B("_=+")YELLOW_BKG_B("_||")YELLOW_BKG_R("_=_=")YELLOW_BKG_B("||_")VIOLET_BKG_B("=+=*-..")"      \n"         
                "                 " BLUE_BKG_V("\\\\=\\===+=+/=/")YELLOW_BKG_B("||____")YELLOW_BKG_R("=+=+")VIOLET_BKG_B("__=+")YELLOW_BKG_B("_||")YELLOW_BKG_R("=>")YELLOW_BKG_B("||_")VIOLET_BKG_B("=+=*-..")" \n"        
                "                 " BLUE_BKG_V("\\\\=\\==+=+=/=/")YELLOW_BKG_B("||___")YELLOW_BKG_R("=_=_=_=_=_=")YELLOW_BKG_R("//")YELLOW_BKG_B("||")VIOLET_BKG_B("=+=*-..")" \n"       
                "                   " BLUE_BKG_V("\\\\=\\==+=+=/=/")YELLOW_BKG_B("||___")YELLOW_BKG_R("=/=//+")VIOLET_BKG_B("=+=")YELLOW_BKG_B("||")VIOLET_BKG_B("=+=*-..")" \n"     
                "                       " BLUE_BKG_V("\\\\=\\==+=/=/")YELLOW_BKG_B("||_||")VIOLET_BKG_B("---=-==+=")VIOLET_BKG_B("=+=*-..")" \n"     
                "                        " BLUE_BKG_V("\\\\=\\==+=/=/")YELLOW_BKG_B("||")VIOLET_BKG_B("---=-==+=")VIOLET_BKG_B("=+=*-..")" \n"    
                "                        " BLUE_BKG_V("\\\\=\\==+=/=/+=/=/")VIOLET_BKG_B("--==+=")VIOLET_BKG_B("=+=*-..")" \n"   
                "                          " BLUE_BKG_V("\\=\\==+=\\=\\+=\\=\\+\\=")VIOLET_BKG_B("--==+=+=")" \n"  
                "                           " BLUE_BKG_V("\\=\\==+=\\=\\+=\\=\\+\\=+\\=")VIOLET_BKG_B("-=+=")" \n" 
                "                             " VIOLET_BKG_B("-=")BLUE_BKG_V("\\=\\==+=\\=\\+=\\+\\=+\\=")" \n"
                "                              " VIOLET_BKG_B("--==+=+")BLUE_BKG_V("\\=\\+=\\+=\\+\\=")" \n"      
                "                                " VIOLET_BKG_B("--==+=--=-==+")BLUE_BKG_V("\\+\\=")" \n"       
                "           " BLUE_BKG_V("\\+=++")"                  " VIOLET_BKG_B("-=+=--=-==+")BLUE_BKG_V("\\")" \n"         
                "       " BLUE_BKG_V("\\+=\\+")"                        " BLUE_BKG_V("\\++=")VIOLET_BKG_B("-+-==+")" \n"          
                "     " BLUE_BKG_V("\\+=\\+=\\+\\+")"                      " BLUE_BKG_V("\\++=\\==")VIOLET_BKG_B("-++")" \n"           
                "      " BLUE_BKG_V("\\+=\\+=\\++\\+")" " BLUE_BKG_V("\\+=\\+=\\++=\\+")"    " VIOLET_BKG_B("=+-")BLUE_BKG_V("=\\=\\==+=")VIOLET_BKG_B("+")" \n"           
                "                " BLUE_BKG_V("\\++=\\+==\\+=")VIOLET_BKG_B("+-==+--")BLUE_BKG_V("\\+=")VIOLET_BKG_B("=-+-=-=+")" \n"             
                "                  " BLUE_BKG_V("\\++=\\+==\\+=\\++=\\+==\\+=\\+")" \n"              
                "                     " VIOLET_BKG_B("+-==-")BLUE_BKG_V("\\+=\\+=\\++=\\+")" \n"               
                "                          " BLUE_BKG_V("+=\\+==\\+=\\+")" \n", string               
             );
    return 0;
}