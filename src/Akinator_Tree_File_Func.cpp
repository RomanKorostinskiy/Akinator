#include "../include/Akinator.h"

int GetSaveFileName(char** filename, int argc, char* argv[])
{
    if (argc == 2) {
        *filename = argv[1];

        return 0;
    } else {
        printf("In function GetSaveFileName: wrong arguments\n");
        exit(-1);
    }
}

size_t GetSizeOfFile (FILE* fp)
{
    fseek(fp, 0, SEEK_END);
    size_t size_of_file = ftell(fp);
    rewind(fp);

    return size_of_file;
}

int MakeTreeFromFile(tnode* node, char* buffer, size_t size)
{
    static int i = 0;

    if (buffer[i] == '{') {
        i++;

        int len = 0;
        char array[512];

        while (buffer[i + len] != '{' && buffer[i + len] != '}') {
            array[len] = buffer[i + len];
            len++;
        }
        array[len] = '\0';

        node->data = (char*)calloc(len + 1, sizeof(char));
        strcpy(node->data, array);

        i = i + len;
    }

    if (buffer[i] == '{') {
        node->left = (tnode*)calloc(1, sizeof(tnode));
        MakeTreeFromFile(node->left, buffer, size);

        node->right = (tnode*)calloc(1, sizeof(tnode));
        MakeTreeFromFile(node->right, buffer, size);
    }

    if (buffer[i] == '}') {
        i++;
        return 0;
    }

    return 0;
}

int SaveTree(tnode* node, FILE* fp)
{
    fprintf(fp, "{%s", node->data);

    if (node->left != nullptr && node->right != nullptr) {
        SaveTree(node->left, fp);
        SaveTree(node->right, fp);
    }

    fprintf(fp, "}");

    return 0;
}

bool IWantSaveTree()
{
    char answer[MAX_ANSWER];

    printf("Вашего персонажа ещё нет в базе ответов.\n"
           "Хотите пополнить базу?\n");
    ScanAnswer(answer);

    if (strcmp(answer, "нет") == 0)
        return false;
    else if (strcmp(answer, "да") == 0)
        return true;

    return false;
}

int TreeDtor(tnode* node)
{
    free(node->data);

    if (node->left != nullptr && node->right != nullptr) {
        TreeDtor(node->left);
        TreeDtor(node->right);
    }

    free(node);

    return 0;
}