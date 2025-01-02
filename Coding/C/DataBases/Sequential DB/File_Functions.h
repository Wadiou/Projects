#ifndef FILE_FUNCTIONS_H
#define FILE_FUNCTIONS_H

#include <stdio.h>
#include "Types.h"
#include "List.h"
#include <string.h>
#include "Secondary_Functions.h"

void Set_Header(char Filename[], int field, int value) ;
int Get_Header(char Filename[], int field) ;
bool Read_dir(char Filename[], int index, Tblock &Buffer) ;
void Write_dir(char Filename[], int index, Tblock Buffer) ;
bool ReadField(char Filename[], Tblock &temp_block, int &block_index, int &i, char temp_string[], int &field_index, int block_num) ;
void SkipRecord(char Filename[], Tblock &temp_block, int &block_index, int &i ) ;
void Search_by_range(char Filename[], int start, int end, Record*& Header) ;
void Search_for_record(char Filename[], int key, Tindex &Index, bool &found , bool &Deleted ) ;
void insert_record(char Filename[], Student student) ;
void Delete_record (char Filename[],  int key) ;

#endif