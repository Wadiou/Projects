#ifndef TYPES_H
#define TYPES_H

#define FIELD_SEPARATOR '|'
#define RECORD_SEPARATOR '&'
#define DELETION_SEPARATOR '$'
#define MAX_Block_LENGTH 100
#define MAX_Block_FILL 70
#define MAX_String_LENGTH 50
#define MAX_Number_LENGTH 10

struct Tblock {
    char arr[MAX_Block_LENGTH];
    int next;
    int Last_index;
};

struct Patient {
    char First_name[MAX_String_LENGTH];
    char Last_name[MAX_String_LENGTH];
    char Department[MAX_String_LENGTH];
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
    Tindex index ;
    Patient patient;
    Record* next;
};
struct Element {
    int Key, Block;
};
struct Iheader
{
    int Record_numbers ;
};

#endif 
