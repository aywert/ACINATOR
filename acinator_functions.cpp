#include"acinator_functions.h"

//TODO comparison ?


char NO[] = "NO";
char EMPTY[] = "";
static int read_acinator_data(FILE* file, str_node_t* prev_node);
static int record_acinator_data(FILE* file, str_node_t* prev_node);
static int generate_graph(str_node_t* node_ptr, FILE* file);
static int print_acinator(const char* string, ACINATOR_PRINT_MODE mode);
static int give_definition(str_node_t* root);
static str_node_t* acinator_find_node(str_node_t* root, const char* buffer);
static int find_free_cell(char* characteristic_array[]);
static char** find_definition(str_node_t* found_node, char* characteristic_array[]);
static ACINATOR_RECORDING request_new_node(str_node_t* node);
static int start_recording_acinator_data(char argv[], str_node_t* root);
static int compare_definition(str_node_t* root);
static int acinator_tree_dtor(str_node_t* root);

str_node_t* start_reading_acinator_data(char argv[])
{
    assert(argv);
    
    FILE* acinator_data = fopen(argv, "r");
    assert(acinator_data);

    char buffer[acinator_str] = {};
    
    fscanf(acinator_data, "%s\n", buffer);
    //printf("buffer = %s\n", buffer);
    fscanf(acinator_data, "\"%[^\"]\"", buffer);
    //printf("buffer = %s\n", buffer);
    str_node_t* root = str_ctor_node(buffer);
    read_acinator_data(acinator_data, root);

    fclose(acinator_data);
    return root;
}

static int start_recording_acinator_data(char argv[], str_node_t* root)
{
    assert(argv);
    FILE* acinator_data = fopen(argv, "w");
    assert(acinator_data);

    fprintf(acinator_data,"{\n");
    fprintf(acinator_data, "\"%s\"\n", root->data);
    record_acinator_data(acinator_data, root);

    fclose(acinator_data);

    return 0;
}

static int record_acinator_data(FILE* file, str_node_t* root)
{
    if (root->left)
    {
        fprintf(file,"{\n");
        fprintf(file, "\"%s\"\n", root->left->data);
        record_acinator_data(file, root->left);
    }

    if (root->right)
    {
        fprintf(file,"{\n");
        fprintf(file, "\"%s\"\n", root->right->data);
        record_acinator_data(file, root->right);
    }

    fprintf(file,"}\n");
    return 0;
}

static int read_acinator_data(FILE* file, str_node_t* prev_node)
{
    assert(file);
    
    char buffer[acinator_str] = {};
    int verifier = fscanf(file, "%s\n", buffer);
    //printf("buffer = %s\n", buffer);

    if (verifier == EOF)
        return 0;

    assert(prev_node);

    if (strcmp(buffer, "{") == 0)
    {
        fscanf(file, "\"%[^\"]\"", buffer);
        //printf("buffer = %s\n", buffer);
        str_node_t* root = str_ctor_node(buffer);

        if (prev_node->left == 0)
        {
            prev_node->left = root;
            root->parent   = prev_node;
            root->location = 0; 
        }

        else if (prev_node->right == 0)
        {
            prev_node->right = root;
            root->parent = prev_node;
            root->location = 1; 
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

static int acinator_tree_dtor(str_node_t* root)
{
    if (root->left)
    {
        acinator_tree_dtor(root->left);
    }

    if (root->right)
    {
        acinator_tree_dtor(root->left);
    }

    dtor_node(root); root = NULL;
    return 0;
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

static int generate_graph(str_node_t* node_ptr, FILE* file)
{
    assert(node_ptr);
    assert(file);
    static int label = 0;
    
    fprintf(file, "%d [shape = Mrecord; style = filled; fillcolor=\"#FBEE21\"; color = \"#000000\"; fontcolor = \"#000000\"; label = \"{ %s| parent = %p| left = %p| right = %p| location = %d}\"];\n\t", (int)&node_ptr->data, node_ptr->data, node_ptr->parent, node_ptr->left, node_ptr->right, node_ptr->location);
    if (node_ptr->parent != 0)
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

int give_definition(str_node_t* root)
{
    assert(root);

    printf("Enter a word to define in \"\": \n");

    char buffer[acinator_str] = {};
    while(getchar() != '\n');
    scanf("\"%[^\"]\"", buffer);
    
    str_node_t* found_node = acinator_find_node(root, buffer);
    if (!found_node)
    {
        print_acinator("I ain't eating this shit. Mind \"\" or check the database", STATEMENT);
        return 0;
    }
    else
        printf("we found %s!\n", found_node->data);
    char** characteristic_array  = (char**)calloc(sizeof(str_node_t**), acinator_str);

    find_definition(found_node, characteristic_array);

    char string[acinator_str*acinator_str] = {};
    int index = 0;

    while(found_node->data[index] != '\0')
    {
        string[index] = found_node->data[index];
        index++;
    }
    string[index++] = ' '; 
    string[index++] = 'i'; 
    string[index++] = 's';
    string[index++] = ' ';
    int flag = 0;
    for (int i = acinator_str-1; i >= 0 ; i--)
    {
        if(characteristic_array[i] != 0)
        {
            int j = 0;
            while(characteristic_array[i][j] != '\0')
            {
                string[index++] = characteristic_array[i][j++];
            }
            if (flag)
            {
                if (i == 0) 
                    string[index++] = '.'; 
                else
                    string[index++] = ',';
                flag = 0;
            }

            if (j <= 2)
                flag = 1;
                
            string[index++] = ' ';
        }
    }
    free(characteristic_array); characteristic_array = NULL;
    print_acinator(string, STATEMENT);
    return 0;
}

static char** find_definition(str_node_t* found_node, char* characteristic_array[])
{
    assert(found_node);
    assert(characteristic_array);

    if (found_node->parent == 0)
        return 0;
    characteristic_array[find_free_cell(characteristic_array)] = found_node->parent->data;

    
    if (found_node->location == 0)
        characteristic_array[find_free_cell(characteristic_array)] = NO;
    else 
        characteristic_array[find_free_cell(characteristic_array)] = EMPTY;  
    find_definition(found_node->parent, characteristic_array);
    return characteristic_array;
}

static int find_free_cell(char* characteristic_array[])
{
    for (int i = 0; i < acinator_str; i++)
    {
        if (characteristic_array[i] == NULL)
            return i;
    }

    return 0;
}

static str_node_t* acinator_find_node(str_node_t* root, const char* buffer)
{
    assert(buffer);
    int decider = strcmp(buffer, root->data);
    str_node_t* found_node = 0;

    if (decider != 0)
    {
        if (root->left)
        {
            found_node = acinator_find_node(root->left, buffer);
            if (found_node != 0)
                return found_node;
        }

        if (root->right)
        {
            found_node = acinator_find_node(root->right, buffer);
            if (found_node != 0)
                return found_node;
        }

        return 0;
    }
    else
        return root;
}

ACINATOR_RECORDING start_acinator(str_node_t* root, char argv[])
{
    assert(root);
    assert(argv);
    printf(GREEN("=======================================\n"));
    printf(GREEN("ACINATOR is welcoming you!\n"));
    printf(GREEN("=======================================\n"));

    while(1) 
    {
        print_acinator("I'm glad to meet you, my friend. Wanna play", QUESTION);

        char buffer[acinator_str] = {};
        do
        {
            printf("Enter Yes/No/Define/Compare: ");
            scanf("%s", &buffer[0]);

            if (strcmp(buffer, "No") == 0)
            {
                print_acinator("You never gonna know...", STATEMENT);
                acinator_tree_dtor(root);
                return ACINATOR_NOT_RECORD;
            }

            if (strcmp(buffer, "Define") == 0)
            {
                print_acinator("WHAAT is it, pity man", QUESTION);
                give_definition(root);
            }

            if (strcmp(buffer, "Compare") == 0)
            {
                print_acinator("Again you with your stupid questions? What you've got this time", QUESTION);
                compare_definition(root);
            }

        } while(strcmp(buffer, "Yes") != 0);

        if (play_acinator(root) == ACINATOR_RECORD)
        {
            start_recording_acinator_data(argv, root);
        }

    }

    return ACINATOR_NOT_RECORD;
}

static int compare_definition(str_node_t* root)
{
    assert(root);
    char buffer_1[acinator_str] = {};
    char buffer_2[acinator_str] = {};
   
    printf("Enter two items to compare in \"\":\n");

    while(getchar() != '\n');
    printf("First is: ");
    scanf("\"%[^\"]\"", buffer_1);

    while(getchar() != '\n');
    printf("Second is: ");
    scanf("\"%[^\"]\"", buffer_2);

    //finding the charatiristic array for buffer_1

    str_node_t* found_node_1 = acinator_find_node(root, buffer_1);
    if (!found_node_1)
    {
        print_acinator("I ain't eating this shit. Mind \"\" or check the database", STATEMENT);
        return 0;
    }
    else
        printf("we found %s!\n", found_node_1->data);
    char** characteristic_array_1  = (char**)calloc(sizeof(str_node_t**), acinator_str);

    find_definition(found_node_1, characteristic_array_1);

    //finding the charatiristic array for buffer_2
    str_node_t* found_node_2 = acinator_find_node(root, buffer_2);
    if (!found_node_2)
    {
        print_acinator("I ain't eating this shit. Mind \"\" or check the database", STATEMENT);
        return 0;
    }
    else
        printf("we found %s!\n", found_node_2->data);
    char** characteristic_array_2  = (char**)calloc(sizeof(str_node_t**), acinator_str);

    find_definition(found_node_2, characteristic_array_2);

    // main body of the function
    
    char starting_string[acinator_str*10] = {};
    char* string = strcat(starting_string, found_node_1->data);
    string = strcat(string, " is like ");
    string = strcat(string, found_node_2->data);
    string = strcat(string, ", because they're both: ");

    int index_1 = 0;
    int index_2 = 0;
    while(characteristic_array_1[acinator_str - 1 - index_1++] == 0);
    while(characteristic_array_2[acinator_str - 1 - index_2++] == 0);

    while ((acinator_str - index_1) != 0 && (acinator_str - index_2) != 0)
    {
        printf("first = %s\n", characteristic_array_1[acinator_str - index_1]);
        printf("second = %s\n", characteristic_array_2[acinator_str - index_2]);
        if (strcmp(characteristic_array_1[acinator_str - index_1], characteristic_array_2[acinator_str - index_2]) != 0)
        {
            string = strcat(string, "but ");
            string = strcat(string, found_node_1->data);
            string = strcat(string, " is ");
            string = strcat(string, characteristic_array_1[acinator_str - index_1]);
            string = strcat(string, " ");
            string = strcat(string, characteristic_array_1[acinator_str - index_1 - 1]);
            string = strcat(string, ", when ");
            string = strcat(string, found_node_2->data);
            string = strcat(string, " is ");
            string = strcat(string, characteristic_array_2[acinator_str - index_2]);
            string = strcat(string, " ");
            string = strcat(string, characteristic_array_2[acinator_str - index_2 - 1]);
           

            print_acinator(string, STATEMENT);

            return 0;
        }

        else 
        {
            string = strcat(string, characteristic_array_1[acinator_str - index_1]);
            string = strcat(string, " ");
            string = strcat(string, characteristic_array_1[acinator_str - index_1 - 1]);
            string = strcat(string, ", ");
            index_1 += 2;
            index_2 += 2;
        }
    }

    return 0;
}

static ACINATOR_RECORDING request_new_node(str_node_t* node)
{
    assert(node);
    print_acinator("What was it", QUESTION);

    printf("Please enter the name of it in \"\": ");
    char new_answer[acinator_str] = {};

    while(getchar()!='\n');
    scanf("\"%[^\"]\"", new_answer);
    
    char string[acinator_str*2] = {};
    char* string_1 = strcat(string, "What is the defference between ");
    char* string_2 = strcat(string_1, node->data);
    char* string_3 = strcat(string_2, " and ");
    char* string_4 = strcat(string_3, new_answer);
    print_acinator(string_4, QUESTION);

    printf("Unlike %s, %s is(format\"\"): ", node->data, new_answer);
    char new_question[acinator_str] = {};
    while(getchar()!='\n');
    scanf("\"%[^\"]\"", new_question);
    
    str_node_t* new_question_node = str_ctor_node(new_question);
    str_node_t* new_answer_node   = str_ctor_node(new_answer);

    if (node->location == ACINATOR_RIGHT)
        node->parent->right = new_question_node;
    else
        node->parent->left  = new_question_node;

    new_question_node->parent   = node->parent;
    new_question_node->right    = new_answer_node;
    new_question_node->left     = node;
    new_question_node->location = node->location;

    new_answer_node->parent   = new_question_node;
    new_answer_node->location = ACINATOR_RIGHT;

    node->parent   = new_question_node;
    node->left     = 0;
    node->right    = 0;
    node->location = ACINATOR_LEFT;

    print_acinator("Should i record changes", QUESTION);\
    char buffer[acinator_str] = {};
    do
    {
        printf("Enter Yes/No: ");
        scanf("%s", &buffer[0]);
        printf("%s", buffer);
        if (strcmp(buffer, "No") == 0)
        {
            return ACINATOR_NOT_RECORD;
        }

        if (strcmp(buffer, "Yes") == 0)
        {
            return ACINATOR_RECORD;
        }

    } while(1);
}

ACINATOR_RECORDING play_acinator(str_node_t* root)
{
  assert(root);

  print_acinator(root->data, QUESTION);
  char buffer[acinator_str];
  do
  {
    printf("Enter Yes/No/Found: ");
    scanf("%s", &buffer[0]);
    if (strcmp(buffer, "No") == 0)
    {
      if (root->left == 0)
      {
        if(request_new_node(root) == ACINATOR_RECORD)
            return ACINATOR_RECORD;
        else
            return ACINATOR_NOT_RECORD;
      }
      return play_acinator(root->left);
      break;
    }

    if (strcmp(buffer, "Yes") == 0)
    {
      if (root->right == 0)
      {
        print_acinator("I know everything. Be afraid", STATEMENT);
        return ACINATOR_NOT_RECORD;
      }

      return play_acinator(root->right);
      break;
    }

    if (strcmp(buffer, "Found") == 0)
    {
      print_acinator("I know everything. Be afraid", STATEMENT);
      return ACINATOR_NOT_RECORD;
    }

  } while(1);

  return ACINATOR_NOT_RECORD;
}

static int print_acinator(const char* string, ACINATOR_PRINT_MODE mode)
{
    assert(string);
    char parametr = '\0'; 
    if (mode == QUESTION)
    {
        parametr = '?';
    }
    printf(
"                 " RED_BKG("   ")" \n"                                                                                                     
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
"                 " WHITE_BKG("   ")PALE_YELLOW_BKG("....")YELLOW_BKG_B("|")BLACK_BKG("\\______/")YELLOW_BKG("||||")BLACK_BKG("\\______/")YELLOW_BKG("||")"              %s%c\n"                   
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
"                          " BLUE_BKG_V("+=\\+==\\+=\\+")" \n", string, parametr               
);
    return 0;
}