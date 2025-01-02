#ifndef FILE_FUNCTIONS_H
#define FILE_FUNCTIONS_H

#include <stdio.h>
#include "Types.h"
#include "List.h"
#include <string.h>
#include "Secondary_Functions.h"
#include "Indexing.h"

void Set_Header(char Filename[], int field, int value) ;
int Get_Header(char Filename[], int field) ;
void Read_dir(char Filename[], int index, Tblock &Buffer) ;
void Write_dir(char Filename[], int index, Tblock Buffer) ;
void Search_by_range(char Filename[], char IndexFile[], int start, int end, Record*& Header);
void Search_for_record(char Filename[], char IndexFile[], int key, Record*& Header) ;
void Search_all(char Filename[] , char IndexFile[],Record*& Header) ;
void insert_record(char Filename[], char IndexFile[], Patient patient);
void Delete_record (char Filename[],char IndexFile[] ,  int key);

#endif