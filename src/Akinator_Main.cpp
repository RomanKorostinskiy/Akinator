#include "../include/Akinator.h"

int main(int argc, char* argv[])
{
    char* filename = nullptr;
    GetSaveFileName(&filename, argc, argv);
    FILE* save_file = fopen(filename, "r");

    size_t size_of_file = GetSizeOfFile(save_file);
    char* buffer = (char*) calloc(size_of_file, sizeof(char));
    fread(buffer, sizeof(char), size_of_file, save_file);

    tnode* root = (tnode*) calloc(1, sizeof(tnode));

    MakeTreeFromFile(root, buffer, size_of_file);
    fclose(save_file);

#ifdef TREE_DUMP
    TreeDump(root, "MakeTreeFromFile" );
#endif

    Guessing(root, filename);

#ifdef TREE_DUMP
    TreeDump(root, __FUNCTION__ );
#endif

    TreeDtor(root);
    free(buffer);

    return 0;
}