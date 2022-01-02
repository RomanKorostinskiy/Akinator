#include "../include/Akinator.h"

int Guessing(tnode* node, char* filename)
{
    char answer[MAX_ANSWER];

    static tnode* root = node;

    printf("Ваш персонаж %s?\n", node->data);

    ScanAnswer(answer);

    if (strcmp(answer, "да") == 0) {
        if (node->left == nullptr)
            printf("Угадал\n");
        else
            Guessing(node->left, filename);
    } else if (strcmp(answer, "нет") == 0) {
        if (node->right == nullptr && IWantSaveTree()) {
            UpgradeTree(node);

            FILE* save_file = fopen(filename, "w");
            SaveTree(root, save_file);
            fclose(save_file);
        }
        else if (node->right != nullptr)
            Guessing(node->right, filename);
    } else
        printf("Ответ должен быть \"да\" или \"нет\"\n");

    return 0;
}

int UpgradeTree(tnode* node)
{
    char array[MAX_PHRASE];
    size_t len = 0;

    node->left = (tnode*)calloc(1, sizeof(tnode));
    node->right = (tnode*)calloc(1, sizeof(tnode));

    node->right->data = node->data;

    printf("Что вы загадали(не более 256 символов)?\n");
    ScanPhrase(array);

    len = strlen(array);
    node->left->data = (char*)calloc(len + 1, sizeof(char));
    strcpy(node->left->data, array);

    printf("Чем %s отличается от %s(не более 256 символов)?\n", node->left->data, node->right->data);
    ScanPhrase(array);

    len = strlen(array);
    node->data = (char*)calloc(len + 1, sizeof(char));
    strcpy(node->data, array);

#ifdef TREE_DUMP
    TreeDump(node, __FUNCTION__ );
#endif

    return 0;
}

int ScanAnswer(char* answer)
{
    while (true){
        ScanPhrase(answer);

        if (strcmp(answer, "да") == 0 || strcmp(answer, "нет") == 0){
            break;
        } else
            printf("Ответ должен быть \"да\" или \"нет\"\n");
    }

    return 0;
}

int ScanPhrase(char* array)
{
    int i = 0;

    while (true) {
        int c = getchar();

        if (i > MAX_PHRASE) {
            printf("In function ScanPhrase: too much letters\n");
            break;
        }

        if (c == '\n') {
            array[i] = '\0';
            break;
        } else {
            array[i] = (char) c;
            i++;
        }
    }

    return 0;
}