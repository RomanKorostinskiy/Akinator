#include "../include/Akinator.h"

int TreeDump(tnode* root, const char* current_function)
{
    static int dump_cnt = 0;

    MakeGraphDumpTxt(root, current_function, dump_cnt);

    MakePngFromTxt(dump_cnt);

    dump_cnt++;

    return dump_cnt;
}

int MakeGraphDumpTxt(tnode* root, const char* current_function, int dump_cnt)
{
    FILE* dump_fp = nullptr;

    char* dump_filename =  DumpFileName(dump_cnt, "txt");

    dump_fp = fopen(dump_filename, "w");

    if (dump_fp == nullptr)
    {
        printf("In function MakeGraphDumpTxt: can't open file\n");
        exit(-1);
    }

    free(dump_filename);
    fclose(dump_fp);

    return 0;
}

int MakePngFromTxt(int dump_cnt)
{
    char* txt_to_png = nullptr;
    txt_to_png = (char*) calloc(200, sizeof(char));

    char* txt_dump_filename =  DumpFileName(dump_cnt, "txt");

    char* png_dump_filename =  DumpFileName(dump_cnt, "png");

    sprintf(txt_to_png, "cd ../ListDump/ && dot %s -T png -o %s", txt_dump_filename, png_dump_filename);

    system(txt_to_png);

    free(txt_to_png);
    free(txt_dump_filename);
    free(png_dump_filename);

    return 0;
}

char* DumpFileName(int dump_cnt, const char* format)
{
    char* dump_file_name = nullptr;

    dump_file_name = (char*) calloc(50, sizeof(char));

    if(dump_file_name == nullptr)
    {
        printf("In function DumpFileName: can't dump_file_name is nullptr");
        return nullptr;
    }

    sprintf(dump_file_name, "../TreeDump/TreeDump%d.%s", dump_cnt, format);

    return dump_file_name;
}