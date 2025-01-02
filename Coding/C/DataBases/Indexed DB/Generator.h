#ifndef GENERATOR_H
#define GENERATOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <time.h>
#include "Types.h"
#include "File_Functions.h"
#include "Secondary_Functions.h"
#include "Indexing.h"

void initialize_file_with_random_data(char Filename[], char IndexFilename[], int num_records, double factor);
void initialize_file(char Filename[], char IndexFilename[], double factor) ;

#endif 
