#ifndef SECONDARY_FUNCTIONS_H
#define SECONDARY_FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Types.h"

bool Read_info (Patient &patient) ;
void Convertion(Patient patient, char temp_string[MAX_String_LENGTH * 6]);
int convertKeyToInt(const char *key) ;
int compare_patients(const void* a, const void* b) ;
void shift_elements(Tblock& temp_block, int start, int length, int last);
void fill_element(Tblock& block, const char* element, int start) ;
void extract_first_last(Tblock block, char* first_element, char* last_element) ;
void extract_field(const char* source, char* destination ) ;
int extract_key_from_field(const char* element) ;
#endif