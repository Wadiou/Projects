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
        case 3: return header.Deletion_number;
    }
    return -1;
}

bool Read_dir(char Filename[], int index, Tblock &Buffer) {
    FILE *file = fopen(Filename, "rb");
    int Blocks_number = Get_Header(Filename, 1);
    if (index + 1 > Blocks_number) {
        fclose(file);
        return false;
    }
    fseek(file, sizeof(Theader) + sizeof(Tblock) * index, SEEK_SET);
    fread(&Buffer, sizeof(Tblock), 1, file);
    fclose(file);
    return true;
}

void Write_dir(char Filename[], int index, Tblock Buffer) {
    FILE *file = fopen(Filename, "rb+");
    fseek(file, sizeof(Theader) + sizeof(Tblock) * index, SEEK_SET);
    fwrite(&Buffer, sizeof(Tblock), 1, file);
    fclose(file);
}
bool ReadField(char Filename[], Tblock &temp_block, int &block_index, int &i, char temp_string[], int &field_index, int block_num , bool &Deleted) {
    Deleted = false ;
    while (temp_block.arr[i] != FIELD_SEPARATOR && temp_block.arr[i] != RECORD_SEPARATOR && temp_block.arr[i] != DELETION_SEPARATOR && i < temp_block.Last_index) {
        temp_string[field_index++] = temp_block.arr[i++];
        if (i >= temp_block.Last_index) {
            block_index++;
            if (block_index >= block_num) {
                return false;
            }
            Read_dir(Filename, block_index, temp_block);
            i = 0;
        }
    }
    temp_string[field_index] = '\0';
    if (temp_block.arr[i++] == DELETION_SEPARATOR )
    {
        Deleted = true ;
    }
    
    return true;
}

void SkipRecord(char Filename[], Tblock &temp_block, int &block_index, int &i ) {
    while (i < temp_block.Last_index && temp_block.arr[i] != RECORD_SEPARATOR && temp_block.arr[i] != DELETION_SEPARATOR) {
        if (++i >= temp_block.Last_index) {
            block_index++;
            Read_dir(Filename, block_index, temp_block);
            i = 0;
        }
    }
    i++ ;


}
void Search_by_range(char Filename[], int start, int end, Record*& Header) {
    FILE* file = fopen(Filename, "rb");
    if (!file) {
        perror("Failed to open file");
        return;
    }
    Tblock temp_block;
    int block_num = Get_Header(Filename, 1);
    int key_value, i;
    bool stop = false , Deleted;
    Student temp_student;
    char temp_string[MAX_String_LENGTH];

    for (int block_index = 0; block_index < block_num && !stop; block_index++) {
        Read_dir(Filename, block_index, temp_block);
        i = 0;

        while (i < temp_block.Last_index && !stop) {
            int field_index = 0;

            if (!ReadField(Filename, temp_block, block_index, i, temp_string, field_index, block_num,Deleted)) {
                stop = true;
                break;
            }
            strcpy(temp_student.Key, temp_string);
            key_value = convertKeyToInt(temp_student.Key);

            if (key_value < start) {
                SkipRecord(Filename, temp_block, block_index, i);
                continue;
            } else if (key_value > end) {
                stop = true;
                break;
            }

            field_index = 0;
            if (!ReadField(Filename, temp_block, block_index, i, temp_string, field_index, block_num,Deleted)) {
                stop = true;
                break;
            }
            strcpy(temp_student.First_name, temp_string);

            field_index = 0;
            if (!ReadField(Filename, temp_block, block_index, i, temp_string, field_index, block_num,Deleted)) {
                stop = true;
                break;
            }
            strcpy(temp_student.Last_name, temp_string);

            field_index = 0;
            if (!ReadField(Filename, temp_block, block_index, i, temp_string, field_index, block_num,Deleted)) {
                stop = true;
                break;
            }
            if (Deleted)
            {
                continue;
            }
            
            strcpy(temp_student.Age, temp_string);

            Append(Header, temp_student);
        }
    }

    fclose(file);
}
void Search_for_record(char Filename[], int key, Tindex &Index, bool &found , bool &Deleted) {
    FILE *file = fopen(Filename, "rb");
    if (!file) {
        perror("Failed to open file");
        return;
    }

    Tblock temp_block;
    int block_num = Get_Header(Filename, 1);
    int key_value, i;
    char current_key[MAX_Number_LENGTH];
    bool stop = false;

    found = false;

    for (int block_index = 0; block_index < block_num && !stop; block_index++) {
        Read_dir(Filename, block_index, temp_block);
        i = 0;

        while (i < temp_block.Last_index && !stop) {
            int field_index = 0;
            Index.Block_index = i;

            if (!ReadField(Filename, temp_block, block_index, i, current_key, field_index, block_num,Deleted)) {
                stop = true;
                break;
            }

            key_value = convertKeyToInt(current_key);

            if (key_value < key) {
                SkipRecord(Filename, temp_block, block_index, i);
                continue;
            } else if (key_value > key) {
                Index.Block_number = block_index;
                stop = true;
                break;
            } else {
                Index.Block_number = block_index;
                found = true;
                stop = true;
                while (i < temp_block.Last_index && temp_block.arr[i] != RECORD_SEPARATOR && temp_block.arr[i] != DELETION_SEPARATOR) {
                    if (++i >= temp_block.Last_index) {
                        block_index++;
                        Read_dir(Filename, block_index, temp_block);
                        i = 0;
                    }
                }
                if (temp_block.arr[i++] == DELETION_SEPARATOR )
                {
                    Deleted = true ;
                }
    
                break;
            }
        }
    }

    fclose(file);
}
void insert_record(char Filename[], Student student) {
    FILE *file = fopen(Filename, "rb+");
   
    Tindex Index ;
    bool found , Deleted;
    Search_for_record(Filename, convertKeyToInt(student.Key), Index, found, Deleted);

    if (!found) {
        Tblock temp_block;
        fseek(file, sizeof(Theader) + sizeof(Tblock) * Index.Block_number, SEEK_SET);
        Read_dir(Filename,  Index.Block_number, temp_block);

        char student_info[MAX_String_LENGTH * 5];
        Convertion(student, student_info);
        int student_info_len = strlen(student_info);
        int BN = Get_Header(Filename, 1);
        int B_start = 0, remaining = 0, current_block =  Index.Block_number;
        char buffer[MAX_Block_LENGTH * 2];
        buffer[0] = '\0';

        copy_elements_to_buffer(buffer, temp_block,  Index.Block_index, B_start);
        copy_elements_to_block(student_info, temp_block, Index.Block_index, remaining, 0);

        int filled = 0;
        if (remaining == 0 && Index.Block_index != 0) {

            fill_block(buffer, temp_block, temp_block.Last_index, filled);
            shift_elements(buffer, filled);
            Index.Block_index = 0;
        }

        Write_dir(Filename, Index.Block_number, temp_block);
        Set_Header(Filename, 2, Get_Header(Filename, 2) + 1);

        while (strlen(buffer) > 0) {
            current_block++;
            if (current_block > BN) {

                Set_Header(Filename, 1, current_block);
                temp_block.next = current_block ;
            }

            Read_dir(Filename, current_block, temp_block);
            if (current_block > BN) {
                temp_block.next = -1 ;
            }

            copy_elements_to_buffer(buffer, temp_block, 0, B_start);
            if (remaining > 0) {
                copy_elements_to_block(student_info, temp_block, Index.Block_index, remaining, student_info_len - remaining);
            }

            fill_block(buffer, temp_block, Index.Block_index, filled);
            Index.Block_index = 0 ;
            shift_elements(buffer, filled);
            Write_dir(Filename, current_block, temp_block);
        }
    }

    fclose(file);
}
void Delete_record (char Filename[],  int key)
{
    Tindex Index ;
    bool found , Deleted;
    Tblock temp_block ;
    Search_for_record(Filename,key,Index,found , Deleted);
    if (found && !Deleted)
    {
        Read_dir(Filename,Index.Block_number,temp_block) ;
        for (int i = Index.Block_index; true; i++)
        {
            if (i < temp_block.Last_index)
            {
                if (temp_block.arr[i] == RECORD_SEPARATOR)
                {
                    temp_block.arr[i] = DELETION_SEPARATOR ;
                    break;
                }
                
            }
            else
            {
                Index.Block_number ++ ;
                Read_dir(Filename,Index.Block_number,temp_block) ;
                i = 0 ;
            }
            
        }
        Write_dir(Filename,Index.Block_number,temp_block) ;
        
    }
    
}