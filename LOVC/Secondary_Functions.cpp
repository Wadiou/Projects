#include "Secondary_Functions.h"
bool Read_info (Student &student){
    printf("Enter The ID of the student (-1 to stop) : ") ;
    scanf("%s" , student.Key) ;
    if (strcmp(student.Key , "-1") == 0)
    {
        return true ;
    }
    printf("Enter The First name of the student : ") ;
    scanf("%s" , student.First_name) ;
    printf("Enter The Last name of the student : ") ;
    scanf("%s" , student.Last_name) ;
    printf("Enter The Last Age of the student : ") ;
    scanf("%s" , student.Age) ;
    printf("\n") ;
    return false ;
}
void Convertion(Student student, char temp_string[MAX_String_LENGTH * 5]) {
    int i = 0;
    for (int j = 0; student.Key[j] != '\0'; j++) temp_string[i++] = student.Key[j];
    temp_string[i++] = FIELD_SEPARATOR;
    for (int j = 0; student.First_name[j] != '\0'; j++) temp_string[i++] = student.First_name[j];
    temp_string[i++] = FIELD_SEPARATOR;
    for (int j = 0; student.Last_name[j] != '\0'; j++) temp_string[i++] = student.Last_name[j];
    temp_string[i++] = FIELD_SEPARATOR;
    for (int j = 0; student.Age[j] != '\0'; j++) temp_string[i++] = student.Age[j];
    temp_string[i++] = RECORD_SEPARATOR;
    temp_string[i] = '\0';
}

int convertKeyToInt(const char *key) {
    return atoi(key);
}
int compare_students(const void* a, const void* b) {
    int key_a = convertKeyToInt(((Student*)a)->Key);
    int key_b = convertKeyToInt(((Student*)b)->Key);
    return key_a - key_b;
}
void shift_elements(char buffer[MAX_Block_LENGTH * 2], int value) {
    int i = value;
    for (; buffer[i] != '\0'; i++) {
        buffer[i - value] = buffer[i];
    }
    buffer[i - value] = '\0';
}

void copy_elements_to_buffer(char buffer[MAX_Block_LENGTH * 2], Tblock temp_block, int T_start, int &B_start) {
    int i = 0;
    for (; i < temp_block.Last_index - T_start; i++) {
        buffer[i + B_start] = temp_block.arr[T_start + i];
    }
    buffer[i + B_start] = '\0';
    B_start += i;
}

void copy_elements_to_block(char student_info[MAX_String_LENGTH * 5], Tblock &temp_block, int &T_start, int &remaining, int S_start) {
    int length = strlen(student_info), i = 0;
    temp_block.Last_index = T_start;
    for (; i < MAX_Block_LENGTH - T_start - 1 && i < length; i++) {
        temp_block.arr[T_start + i] = student_info[i + S_start];
        temp_block.Last_index++;
    }
    if (i == MAX_Block_LENGTH - T_start - 1) {
        temp_block.arr[temp_block.Last_index] = '\0';
        T_start = 0;
    }

    if (i == length) {

        if (i != MAX_Block_LENGTH - T_start - 1) {
            T_start += i;
        }
        remaining = 0;
    } else {
        remaining = length - (MAX_Block_LENGTH - T_start - 1);
    }
}
void fill_block(char buffer[MAX_Block_LENGTH * 2], Tblock &temp_block, int T_start, int &filled) {
    int i = 0;
    temp_block.Last_index = T_start;
    filled = 0;
    for (; i < MAX_Block_LENGTH - T_start - 1 && buffer[i] != '\0'; i++) {
        temp_block.arr[T_start + i] = buffer[i];
        temp_block.Last_index++;
        filled++;
    }
    temp_block.arr[temp_block.Last_index] = '\0';
}