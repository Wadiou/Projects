#ifndef FILE_H
#define FILE_H

#include "Types.h"
#include <stdlib.h>
#include <stdio.h>

Record* Create_node(const Patient& patient, const Tindex& index) ;
void Append(Record*& Header, const Patient& patient, const Tindex& index);
void Display_patient_List(const Record* Header);

#endif