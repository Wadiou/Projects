#include "Secondary_Functions.h"
#include "Generator.h"

void generate_random_student(Student* student) {
    int random_id = rand() % 10000; 
    int random_age = 18 + rand() % 10;
    int i = 0;
    do {
        student->Key[i++] = (random_id % 10) + '0';
        random_id /= 10;
    } while (random_id > 0);
    student->Key[i] = '\0';

    i = 0;
    do {
        student->Age[i++] = (random_age % 10) + '0';
        random_age /= 10;
    } while (random_age > 0);
    student->Age[i] = '\0';

    const char* first_names[] = {"Abdelwadoud", "Yasser", "Omar", "Yusuf", "Hassan", "Ali", "Abdelnour", "Zakaria"};
    const char* last_names[] = {"Tali", "Laroug", "Sersoub", "Chemakh", "Bachtoti", "Chourfi", "Dhib", "Merouani"};
    strcpy(student->First_name, first_names[rand() % 8]);
    strcpy(student->Last_name, last_names[rand() % 8]);
}

void initialize_file_with_random_data(char Filename[], int num_records) {
    FILE* file = fopen(Filename, "wb");

    Theader temp_header;
    temp_header.Block_number = 0;
    temp_header.Insertion_number = 0;
    temp_header.Deletion_number = 0;
    fwrite(&temp_header, sizeof(Theader), 1, file);
    fclose(file);

    Student* students = (Student*)malloc(num_records * sizeof(Student));
    char temp_string[MAX_String_LENGTH * 5];

    srand(time(NULL));

    for (int i = 0; i < num_records; i++) {
        generate_random_student(&students[i]);
    }

    qsort(students, num_records, sizeof(Student), compare_students);

    Tblock temp_block;
    temp_block.Last_index = 0;
    temp_block.next = -1;
    int block_number = 0;

    for (int i = 0; i < num_records; i++) {
        Convertion(students[i], temp_string);

        for (int j = 0; temp_string[j] != '\0'; j++) {
            if (temp_block.Last_index < MAX_Block_LENGTH - 1) {
                temp_block.arr[temp_block.Last_index++] = temp_string[j];
            } else {
                temp_block.arr[temp_block.Last_index] = '\0';
                temp_block.next = block_number + 1;
                Write_dir(Filename, block_number, temp_block);

                block_number++;
                temp_block.next = -1;
                temp_block.Last_index = 0;
                temp_block.arr[temp_block.Last_index++] = temp_string[j];
            }
        }
    }

    temp_block.arr[temp_block.Last_index] = '\0';
    Write_dir(Filename, block_number, temp_block);
    Set_Header(Filename, 1, block_number + 1);

    free(students);
}

void initialize_file (char Filename[]){
    FILE *file = fopen(Filename , "wb") ;

    Theader temp_header ;
    temp_header.Block_number = 0 ;
    temp_header.Insertion_number = 0 ;
    temp_header.Deletion_number = 0 ;

    fwrite(&temp_header,sizeof(Theader),1 ,file) ;

    Student temp_student ;
    Tblock temp_block ;
    char temp_string[MAX_String_LENGTH*5] ;

    temp_block.Last_index = 0 ;
    temp_block.next = -1 ;
    int block_number = 0 ;

    for (int i = 0; true; i++)
    {
        printf("Student Number %d : \n\n" , i) ;
        if (Read_info(temp_student))
        {
            break;
        }
        Convertion(temp_student,temp_string);
        
        for (int i = 0; temp_string[i] != '\0'; i++)
        {
            if (temp_block.Last_index < MAX_Block_LENGTH -1)
            {
                temp_block.arr[temp_block.Last_index] = temp_string[i] ;
                temp_block.Last_index ++ ;

            }
            else{
                temp_block.arr[MAX_Block_LENGTH -1] = '\0' ;
                temp_block.next = block_number +1 ;
                Write_dir(Filename,block_number,temp_block) ;
                Set_Header(Filename,1,Get_Header(Filename,1) + 1) ;
                temp_block.next = -1 ;
                temp_block.arr[0] = temp_string[i] ;
                temp_block.Last_index = 1 ;
                
            }
            
        }
        
        Set_Header(Filename,2,Get_Header(Filename,2) + 1) ;
        
    }
    temp_block.next = -1 ;
    Write_dir(Filename,block_number,temp_block) ;
    Set_Header(Filename,1,Get_Header(Filename,1) + 1) ;
    

}
