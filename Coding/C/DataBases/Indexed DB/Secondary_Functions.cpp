#include "Secondary_Functions.h"
bool Read_info (Patient &patient){
    printf("Enter The ID of the patient (-1 to stop) : ") ;
    scanf("%s" , patient.Key) ;
    if (strcmp(patient.Key , "-1") == 0)
    {
        return true ;
    }
    printf("Enter The First name of the patient : ") ;
    scanf("%s" , patient.First_name) ;
    printf("Enter The Last name of the patient : ") ;
    scanf("%s" , patient.Last_name) ;
    printf("Enter The Last Department of the patient : ") ;
    scanf("%s" , patient.Department) ;
    printf("Enter The Last Age of the patient : ") ;
    scanf("%s" , patient.Age) ;
    printf("\n") ;
    return false ;
}
void Convertion(Patient patient, char temp_string[MAX_String_LENGTH * 6]) {
    int i = 0;
    for (int j = 0; patient.Key[j] != '\0'; j++) temp_string[i++] = patient.Key[j];
    temp_string[i++] = FIELD_SEPARATOR;
    for (int j = 0; patient.First_name[j] != '\0'; j++) temp_string[i++] = patient.First_name[j];
    temp_string[i++] = FIELD_SEPARATOR;
    for (int j = 0; patient.Last_name[j] != '\0'; j++) temp_string[i++] = patient.Last_name[j];
    temp_string[i++] = FIELD_SEPARATOR;
    for (int j = 0; patient.Department[j] != '\0'; j++) temp_string[i++] = patient.Department[j];
    temp_string[i++] = FIELD_SEPARATOR;
    for (int j = 0; patient.Age[j] != '\0'; j++) temp_string[i++] = patient.Age[j];
    temp_string[i++] = RECORD_SEPARATOR;
    temp_string[i] = '\0';
}

int convertKeyToInt(const char *key) {
    return atoi(key);
}
int compare_patients(const void* a, const void* b){
    int key_a = convertKeyToInt(((Patient*)a)->Key);
    int key_b = convertKeyToInt(((Patient*)b)->Key);
    return key_a - key_b;
}
void shift_elements(Tblock& temp_block, int start, int length, int last) {
    for (int i = temp_block.Last_index - 1; i >= start; i--) {
        temp_block.arr[i + length] = temp_block.arr[i];
    }
    temp_block.Last_index = last;
    temp_block.arr[last] = '\0';
}


void fill_element(Tblock& block, const char* element, int start) {
    int i = 0;
    while (element[i] != '\0') {
        block.arr[start++] = element[i++];
    }

}
void extract_first_last(Tblock block, char* first_element, char* last_element) {
    int start = 0, end = block.Last_index - 2;
    int i = 0;
    while (block.arr[start] != RECORD_SEPARATOR && block.arr[start] != DELETION_SEPARATOR && start < block.Last_index) {
        first_element[i++] = block.arr[start++];
    }
    first_element[i++] = block.arr[start];
    first_element[i] = '\0';

    i = 0;
    while (end >= 0 && block.arr[end] != RECORD_SEPARATOR && block.arr[end] != DELETION_SEPARATOR) {
        --end;
    }
    ++end;
    while (end < block.Last_index && block.arr[end] != RECORD_SEPARATOR && block.arr[end] != DELETION_SEPARATOR) {
        last_element[i++] = block.arr[end++];
    }
    last_element[i++] = block.arr[end];
    last_element[i] = '\0';

}

void extract_field(const char* source, char* destination ){
    int i = 0;
    while (source[i] != FIELD_SEPARATOR) {
        destination[i] = source[i];
        i++;
    }
    destination[i] = '\0';
}
int extract_key_from_field(const char* element) {
    char temp_string[MAX_String_LENGTH];
    extract_field(element, temp_string);
    return convertKeyToInt(temp_string);
}


