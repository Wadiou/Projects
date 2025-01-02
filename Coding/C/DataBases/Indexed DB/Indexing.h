#ifndef INDEXING_H
#define INDEXING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Types.h"

void Set_IHeader(char Filename[], int value);
int Get_IHeader(char Filename[]) ;
void Read_ID_Tab(char Filename[], Element *&Elems) ;
void Write_ID_Tab(char Filename[], Element *Elems, int Block_number);
void Search_Index(char Filename[], int ID ,bool &found, int& block) ;
void add_index_to_table(char Filename[], int key, int block, bool shift) ;
#endif 