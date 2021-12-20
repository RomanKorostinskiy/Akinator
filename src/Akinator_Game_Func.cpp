#include "../include/Akinator.h"

int Guessing(tnode* node)
{
    char answer[MAX_ANSWER];

    printf("Ваш персонаж %s?\n", node->data);

    ScanAnswer(answer);

    if (strcmp(answer, "да") == 0) {
        if (node->left == nullptr)
            printf("Угадал\n");
        else
            Guessing(node->left);
    } else if (strcmp(answer, "нет") == 0) {
        if (node->right == nullptr) {
            printf("Жаль\n");
            UpgradeTree(node);
        }
        else
            Guessing(node->right);
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

    node->right->data = node->data; //нет

    printf("Что вы загадали(не более 256 символов)?\n");
    ScanPhrase(array);

    len = strlen(array);
    node->left->data = (char*)calloc(len + 1, sizeof(char));
    strcpy(node->left->data, array); //да

    printf("Чем %s отличается от %s(не более 256 символов)?\n", node->left->data, node->right->data);
    ScanPhrase(array);

    len = strlen(array);
    node->data = (char*)calloc(len + 1, sizeof(char));
    strcpy(node->data, array); //признак

    return 0;
}

int ScanAnswer(char* answer)
{
    while (true){
        scanf("%s", answer);

        if (strcmp(answer, "да") == 0 || strcmp(answer, "нет") == 0){
            break;
        } else
            printf("Ответ должен быть \"да\" или \"нет\"\n");
    }

    while (true) { //адекватно? (scanf оставляет после себя несчитанные символы)
        int c = getchar();

        if (c == '\n') {
            break;
        }
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