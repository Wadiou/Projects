#ifndef SECONDARY_FUNCTIONS_H
#define SECONDARY_FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Types.h"

bool Read_info (Student &student) ;
void Convertion(Student student, char temp_string[MAX_String_LENGTH * 5]);
int convertKeyToInt(const char *key) ;
int compare_students(const void* a, const void* b) ;
void shift_elements(char buffer[MAX_Block_LENGTH * 2], int value) ;
void copy_elements_to_buffer(char buffer[MAX_Block_LENGTH * 2], Tblock temp_block, int T_start, int &B_start) ;
void copy_elements_to_block(char student_info[MAX_String_LENGTH * 5], Tblock &temp_block, int &T_start, int &remaining, int S_start) ;
void fill_block(char buffer[MAX_Block_LENGTH * 2], Tblock &temp_block, int T_start, int &filled) ;

#endif