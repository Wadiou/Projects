#ifndef FILE_H
#define FILE_H

#include "Types.h"
#include <stdlib.h>
#include <stdio.h>

Record* Create_node(Student student) ;
void Append(Record*& Header, Student student) ;
void Display_Student_List(Record* Header) ;

#endif