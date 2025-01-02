#include "File_Functions.h"

void Set_Header(char Filename[], int field, int value) {
    Theader header;
    FILE *file = fopen(Filename, "rb+");
    fread(&header, sizeof(Theader), 1, file);
    switch (field) {
        case 1: header.Block_number = value; break;
        case 2: header.Insertion_number = value; break;
        case 3: header.Deletion_number = value; break;
    }
    fseek(file, 0, SEEK_SET);
    fwrite(&header, sizeof(Theader), 1, file);
    fclose(file);
}

int Get_Header(char Filename[], int field) {
    Theader header;
    FILE *file = fopen(Filename, "rb");
    fread(&header, sizeof(Theader), 1, file);
    fclose(file);
    switch (field) {
        case 1: return header.Block_number;
        case 2: return header.Insertion_number;
        case 3: return header.Deletion_number;    }
    return -1;
}

void Read_dir(char Filename[], int index, Tblock &Buffer) {
    FILE *file = fopen(Filename, "rb");
    fseek(file, sizeof(Theader) + sizeof(Tblock) * index, SEEK_SET);
    fread(&Buffer, sizeof(Tblock), 1, file);
    fclose(file);
}

void Write_dir(char Filename[], int index, Tblock Buffer) {
    FILE *file = fopen(Filename, "rb+");
    fseek(file, sizeof(Theader) + sizeof(Tblock) * index, SEEK_SET);
    fwrite(&Buffer, sizeof(Tblock), 1, file);
    fclose(file);
}
void ReadField(char Filename[], Tblock temp_block, int &index, char temp_string[]) {
    int field_index=0 ;
    while (temp_block.arr[index] != FIELD_SEPARATOR && temp_block.arr[index] != DELETION_SEPARATOR && temp_block.arr[index] != RECORD_SEPARATOR) {
        temp_string[field_index++] = temp_block.arr[index++];
    }
    temp_string[field_index] = '\0';
    index++;

}
void read_record(char Filename[], int block_number, int &record_index, Patient& patient , bool& Deleted) {
    FILE* file = fopen(Filename, "rb");
    Deleted = false ;
    Tblock temp_block;
    Read_dir(Filename, block_number, temp_block);

    char temp_string[MAX_String_LENGTH];

    ReadField(Filename, temp_block, record_index, temp_string);
    strcpy(patient.Key, temp_string);

    ReadField(Filename, temp_block, record_index, temp_string);
    strcpy(patient.First_name, temp_string);

    ReadField(Filename, temp_block, record_index, temp_string);
    strcpy(patient.Last_name, temp_string);

    ReadField(Filename, temp_block, record_index, temp_string);
    strcpy(patient.Department, temp_string);
    int field_index=0 ;
    while (temp_block.arr[record_index] != FIELD_SEPARATOR && temp_block.arr[record_index] != DELETION_SEPARATOR && temp_block.arr[record_index] != RECORD_SEPARATOR) {
        temp_string[field_index++] = temp_block.arr[record_index++];
    }
    temp_string[field_index] = '\0';
    if (temp_block.arr[record_index++] == DELETION_SEPARATOR)
    {
        Deleted = true ;
    }
    
    strcpy(patient.Age, temp_string);

    fclose(file);
    
}


void SkipRecord(char Filename[], Tblock &temp_block ,int &i ) {
    while (temp_block.arr[i] != RECORD_SEPARATOR && temp_block.arr[i] != DELETION_SEPARATOR) 
    {
        ++i; 
    }
    i++ ;
}
void Set_Delete(char Filename[], Tblock &temp_block ,int &i )
{
    while (temp_block.arr[i] != RECORD_SEPARATOR) 
    {
        ++i; 
    }
    temp_block.arr[i] = DELETION_SEPARATOR ;
}
void Search_in_block(char Filename[], int block_number, int key, bool& found, bool& Deleted, int& index) {
    FILE* file = fopen(Filename, "rb");

    Tblock temp_block;
    Read_dir(Filename, block_number, temp_block);

    char current_key[MAX_Number_LENGTH];
    int key_value, i = 0;

    found = false;
    Deleted = false;

    while (i < temp_block.Last_index) {
        index = i;

        ReadField(Filename, temp_block, i, current_key);
        key_value = convertKeyToInt(current_key);


        if (key_value < key) {
            SkipRecord(Filename, temp_block, i);
            continue;
        } else if (key_value == key) {
            found = true;
            SkipRecord(Filename, temp_block, i);

            if (temp_block.arr[--i] == DELETION_SEPARATOR) {
                Deleted = true;

            }

            fclose(file);
            return;
        } else {
            break;
        }
    }

    fclose(file);

}
void handle_overflow(char Filename[], char IndexFile[], Tblock& temp_block, Tindex& index, char patient_info[], int& Block_number) {
    char first_element[MAX_String_LENGTH * 6], last_element[MAX_String_LENGTH * 6], temp_last_element[MAX_String_LENGTH * 6];
    int last_element_index;
    bool found , Deleted ;

    extract_first_last(temp_block, first_element, last_element);
    strcpy(temp_last_element, last_element);
    Search_in_block(Filename, index.Block_number, extract_key_from_field(last_element), found, Deleted, last_element_index);

    int last_index = last_element_index + strlen(patient_info);
    shift_elements(temp_block, index.Block_index, strlen(patient_info), last_index);
    fill_element(temp_block, patient_info, index.Block_index);

    extract_first_last(temp_block, first_element, last_element);
    int last_key = extract_key_from_field(last_element);
    add_index_to_table(IndexFile, last_key, index.Block_number, false);

    temp_block.next = Block_number;
    Write_dir(Filename, index.Block_number, temp_block);

    index.Block_number = Block_number;
    fill_element(temp_block, temp_last_element, 0);
    temp_block.arr[strlen(temp_last_element)] = '\0';
    temp_block.Last_index = strlen(temp_last_element);
    temp_block.next = -1;
    add_index_to_table(IndexFile, extract_key_from_field(temp_last_element), Block_number, true);
    Write_dir(Filename, index.Block_number, temp_block);
    Set_Header(Filename, 1, ++Block_number);
}
void insert_into_block(char Filename[], char IndexFile[], Tblock& temp_block, Tindex& index, char patient_info[], int current_key) {
    char first_element[MAX_String_LENGTH * 6], last_element[MAX_String_LENGTH * 6], temp_last_element[MAX_String_LENGTH * 6];
    int last_element_index;
    bool found , Deleted ;

    extract_first_last(temp_block, first_element, last_element);
    strcpy(temp_last_element, last_element);
    Search_in_block(Filename, index.Block_number, extract_key_from_field(last_element), found, Deleted, last_element_index);

    int last_index = last_element_index + strlen(patient_info);
    shift_elements(temp_block, index.Block_index, strlen(patient_info), last_index);
    fill_element(temp_block, patient_info, index.Block_index);

    extract_first_last(temp_block, first_element, last_element);
    int last_key = extract_key_from_field(last_element);
    add_index_to_table(IndexFile, last_key, index.Block_number, false);
    strcpy(patient_info, temp_last_element);

    Write_dir(Filename, index.Block_number, temp_block);
}
void finalize_insertion(char Filename[], char IndexFile[], Tblock& temp_block, Tindex& index, char patient_info[], int current_key) {
    char first_element[MAX_String_LENGTH * 6], last_element[MAX_String_LENGTH * 6];
    bool found , Deleted ;

    Search_in_block(Filename, index.Block_number, current_key, found, Deleted, index.Block_index);
    if (!found) {
        shift_elements(temp_block, index.Block_index, strlen(patient_info), temp_block.Last_index + strlen(patient_info));
        fill_element(temp_block, patient_info, index.Block_index);

        extract_first_last(temp_block, first_element, last_element);
        int last_key = extract_key_from_field(last_element);
        add_index_to_table(IndexFile, last_key, index.Block_number, false);
        Write_dir(Filename, index.Block_number, temp_block);
    }
}

void insert_record(char Filename[], char IndexFile[], Patient patient) {
    FILE* file = fopen(Filename, "rb+");
    FILE* Indexfile = fopen(IndexFile, "rb+");
    int current_key = convertKeyToInt(patient.Key);
    Tindex index;
    bool found, Deleted;

    Search_Index(IndexFile, current_key, found, index.Block_number);

    if (found) {
        fclose(file);
        fclose(Indexfile);
        return;
    }

    Tblock temp_block;
    fseek(file, sizeof(Theader) + sizeof(Tblock) * index.Block_number, SEEK_SET);
    Read_dir(Filename, index.Block_number, temp_block);

    char patient_info[MAX_String_LENGTH * 6];
    Convertion(patient, patient_info);

    int Block_number = Get_Header(Filename, 1);
    char first_element[MAX_String_LENGTH * 6], last_element[MAX_String_LENGTH * 6];

    while (strlen(patient_info) > MAX_Block_FILL - 1 - temp_block.Last_index) {
        if (temp_block.next == -1) {
            Search_in_block(Filename, index.Block_number, current_key, found, Deleted, index.Block_index);
            if (!found) {
                handle_overflow(Filename, IndexFile, temp_block, index, patient_info, Block_number);
            }
            return;
        } else {
            Search_in_block(Filename, index.Block_number, current_key, found, Deleted, index.Block_index);
            if (!found) {
                insert_into_block(Filename, IndexFile, temp_block, index, patient_info, current_key);
            } else {
                return;
            }
            index.Block_number = temp_block.next;
            Read_dir(Filename, index.Block_number, temp_block);
        }
    }

    if (strlen(patient_info) <= MAX_Block_FILL - 1 - temp_block.Last_index) {
        finalize_insertion(Filename, IndexFile, temp_block, index, patient_info, current_key);
    }

    fclose(file);
    fclose(Indexfile);
}



void Delete_record(char Filename[], char IndexFile[], int key) {
    Tindex index;
    bool found, Deleted;
    Tblock temp_block;

    Search_Index(IndexFile, key, found, index.Block_number);

    Search_in_block(Filename, index.Block_number, key, found, Deleted, index.Block_index);

    if (found && !Deleted) {

        Read_dir(Filename, index.Block_number, temp_block);
        Set_Delete(Filename, temp_block, index.Block_index);
        Write_dir(Filename, index.Block_number, temp_block);
    } else if (Deleted) {
        printf("Key %d already marked as deleted.\n", key);
    } else {
        printf("Key %d not found in block %d.\n", key, index.Block_number);
    }
   
}

void Search_for_record(char Filename[], char IndexFile[], int key, Record*& Header) {
    bool found, Deleted;
    Tindex index;
    Search_Index(IndexFile, key, found, index.Block_number);
    Tblock temp_block;
    Read_dir(Filename, index.Block_number, temp_block);
    Search_in_block(Filename, index.Block_number, key, found, Deleted, index.Block_index);
    int saved_index = index.Block_index ;

    if (found && !Deleted) {
        Patient temp_patient;
            read_record(Filename, index.Block_number, saved_index, temp_patient,Deleted);
            Append(Header, temp_patient,index);
    }
}


void Search_by_range(char Filename[], char IndexFile[], int start, int end, Record*& Header) {
    bool found;
    int element_start, element_end;
    Element* elements = nullptr;
    int num_records = Get_IHeader(IndexFile);
    Tindex index;
    Read_ID_Tab(IndexFile, elements);

    for (int element_index = 0; element_index < num_records; element_index++) {
        Tblock temp_block;
        index.Block_number = elements[element_index].Block;
        Read_dir(Filename, index.Block_number, temp_block);
        int key_value, i = 0, saved_index;
        bool Deleted = false;

        while (i < temp_block.Last_index) {
            char temp_string[MAX_String_LENGTH];
            Patient temp_patient;
            index.Block_index = i;
            saved_index = i;
            int field_index = 0;
            ReadField(Filename, temp_block, i, temp_string);
            key_value = convertKeyToInt(temp_string);


            if (key_value < start) {
                SkipRecord(Filename, temp_block, i);
                continue;
            } else if (key_value > end) {
                break;
            }

            read_record(Filename, index.Block_number, saved_index, temp_patient, Deleted);
            i = saved_index;
            if (!Deleted) {
                Append(Header, temp_patient, index);
            }
        }
    }

    delete[] elements;
}

void Search_all(char Filename[] , char IndexFile[],Record*& Header)
{
    Element *elements = nullptr;
    Read_ID_Tab(IndexFile,elements) ;
    int Block_number = Get_IHeader(IndexFile) ;
    Tblock temp_block ;
    int last_block_key = elements[Block_number -1].Key ;
    Search_by_range(Filename,IndexFile,0,last_block_key,Header) ;
}

