#ifndef TYPES_H
#define TYPES_H

#define FIELD_SEPARATOR '|'
#define RECORD_SEPARATOR '&'
#define DELETION_SEPARATOR '$'
#define MAX_Block_LENGTH 1000
#define MAX_String_LENGTH 50
#define MAX_Number_LENGTH 10

struct Tblock {
    char arr[MAX_Block_LENGTH];
    int next;
    int Last_index;
};

struct Student {
    char First_name[MAX_String_LENGTH];
    char Last_name[MAX_String_LENGTH];
    char Key[MAX_Number_LENGTH];
    char Age[MAX_Number_LENGTH];
};

struct Theader {
    int Block_number;
    int Insertion_number;
    int Deletion_number;
};
struct Tindex
{
    int Block_number ,
    Block_index ;
};

struct Record {
    Student student;
    Record* next;
};

#endif 
