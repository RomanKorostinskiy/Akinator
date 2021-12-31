#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct tnode
{
    char* data;

    tnode* left;
    tnode* right;
}tnode;

enum Returns {
    ROOT = -1,
};

const int MAX_ANSWER = 128;
const int MAX_PHRASE = 512;

//---------Akinator_Game_Func---------

int Guessing(tnode* node, char* filename);

int UpgradeTree(tnode* node);

int ScanAnswer(char* answer);

int ScanPhrase(char* array);

//---------Akinator_Tree_File_Func---------

int GetSaveFileName(char** filename, int argc, char* argv[]);

size_t GetSizeOfFile (FILE* fp);

int MakeTreeFromFile(tnode* node, char* buffer, size_t size);

int SaveTree(tnode* node, FILE* fp);

bool IWantSaveTree();

int FreeTree(tnode* node);

//---------Akinator_Dump---------

int TreeDump(tnode* root, const char* current_function);

int MakeGraphDumpTxt(tnode* root, const char* current_function, int dump_cnt);

int MakePngFromTxt(int dump_cnt);

int RecursiveTreeDump(tnode* node, FILE* dump_fp, int parents_num, bool left_node);

char* DumpFileName(int dump_cnt, const char* format);