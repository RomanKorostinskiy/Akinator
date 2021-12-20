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

    Guessing(root);

    if (IWantSaveTree()) {
        save_file = fopen(filename, "w");
        SaveTree(root, save_file);
        fclose(save_file);
    }

    FreeTree(root);
    free(buffer);

    return 0;
}