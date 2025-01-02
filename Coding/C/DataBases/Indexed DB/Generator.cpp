#include "Generator.h"

int reverse_number(int num) {
    int reversed = 0;
    while (num > 0) {
        reversed = reversed * 10 + (num % 10);
        num /= 10;
    }
    return reversed;
}
void generate_random_patient(Patient* patient) {
    int random_id = rand() % 10000; 
    int random_age = 18 + rand() % 10;
    random_id = reverse_number(random_id) ;
    random_age = reverse_number(random_age) ;
    int i = 0;
    do {
        patient->Key[i++] = (random_id % 10) + '0';
        random_id /= 10;
    } while (random_id > 0);
    patient->Key[i] = '\0';

    i = 0;
    do {
        patient->Age[i++] = (random_age % 10) + '0';
        random_age /= 10;
    } while (random_age > 0);
    patient->Age[i] = '\0';

    const char* first_names[] = {"Abdelwadoud", "Yasser", "Omar", "Yusuf", "Hassan", "Ali", "Abdelnour", "Zakaria"};
    const char* last_names[] = {"Tali", "Laroug", "Sersoub", "Chemakh", "Bachtoti", "Chourfi", "Dhib", "Merouani"};
    const char* departments[] = {"Cardiology", "Neurology", "Orthopedics", "Pediatrics", "Oncology", "Dermatology", "Psychiatry", "Radiology"};
    strcpy(patient->First_name, first_names[rand() % 8]);
    strcpy(patient->Last_name, last_names[rand() % 8]);
    strcpy(patient->Department, departments[rand() % 8]);

}

void initialize_file_with_random_data(char Filename[], char IndexFilename[], int num_records, double factor) {
    FILE* file = fopen(Filename, "wb");

    Theader temp_header;
    temp_header.Block_number = 0;
    temp_header.Insertion_number = 0;
    temp_header.Deletion_number = 0;
    fwrite(&temp_header, sizeof(Theader), 1, file);
    fclose(file);

    FILE* index_file = fopen(IndexFilename, "wb");

    Iheader temp_Iheader;
    temp_Iheader.Record_numbers = 0;
    fwrite(&temp_Iheader, sizeof(Iheader), 1, index_file);

    Patient* patients = (Patient*)malloc(num_records * sizeof(Patient));
    char temp_string[MAX_String_LENGTH * 6];

    srand(time(NULL));

    printf("Debug: Generating %d random patients.\n", num_records);

    
    for (int i = 0; i < num_records; i++) {
        generate_random_patient(&patients[i]);
    }
    qsort(patients, num_records, sizeof(Patient), compare_patients);
    for (int i = 0; i < num_records; i++) {
        printf("Patient %d: Key=%s, First Name=%s, Last Name=%s, Department=%s, Age=%s\n",
               i, patients[i].Key, patients[i].First_name, patients[i].Last_name,
               patients[i].Department, patients[i].Age);
    }
    printf("Debug: Patients sorted by Key.\n");

    Tblock temp_block;
    temp_block.Last_index = 0;
    temp_block.next = -1;
    int block_number = 0;

    Element element;
    int i = 0;
    for (; i < num_records; i++) {
        Convertion(patients[i], temp_string);
        int Remaining_size = MAX_Block_FILL * factor - 1 - temp_block.Last_index ;
        if (Remaining_size < strlen(temp_string)) {
            temp_block.arr[temp_block.Last_index] = '\0';
            temp_block.next = -1;
            element.Block = block_number;
            element.Key = convertKeyToInt(patients[i-1].Key);
            fseek(index_file,sizeof(Iheader)+sizeof(Element)*block_number,SEEK_SET) ;
            fwrite(&element, sizeof(Element), 1, index_file);
            temp_Iheader.Record_numbers++;
            Write_dir(Filename, block_number, temp_block);
            block_number++;
            temp_block.Last_index = 0;
        }

        for (int j = 0; temp_string[j] != '\0'; j++) {
            temp_block.arr[temp_block.Last_index++] = temp_string[j];
        }
    }

    temp_block.arr[temp_block.Last_index] = '\0';
    temp_block.next = -1;
    element.Block = block_number;
    element.Key = convertKeyToInt(patients[--i].Key);
    fseek(index_file,sizeof(Iheader)+sizeof(Element)*block_number,SEEK_SET) ;
    fwrite(&element, sizeof(Element), 1, index_file);
    temp_Iheader.Record_numbers++;
    Write_dir(Filename, block_number, temp_block);
    block_number++;

    Set_Header(Filename, 1, block_number);
    Set_Header(Filename,2,num_records) ;
    Set_IHeader(IndexFilename, block_number);
    fclose(index_file);
    free(patients);
    Element* elements = nullptr;
    Read_ID_Tab(IndexFilename, elements);
    if (elements) {
        printf("Index table contents.\n");
        for (int j = 0; j < temp_Iheader.Record_numbers; j++) {
            printf("Element %d: Key=%d, Block=%d\n", j, elements[j].Key, elements[j].Block);
        }
        delete[] elements;
    }
}



void initialize_file(char Filename[], char IndexFilename[], double factor) {
    FILE* file = fopen(Filename, "wb");

    Theader temp_header;
    temp_header.Block_number = 0;
    temp_header.Insertion_number = 0;
    temp_header.Deletion_number = 0;
    fwrite(&temp_header, sizeof(Theader), 1, file);
    fclose(file);

    FILE* index_file = fopen(IndexFilename, "wb");

    Iheader temp_Iheader;
    temp_Iheader.Record_numbers = 0;
    fwrite(&temp_Iheader, sizeof(Iheader), 1, index_file);

    Patient temp_patient;
    Tblock temp_block;
    char temp_string[MAX_String_LENGTH * 6];

    temp_block.Last_index = 0;
    temp_block.next = -1;
    int block_number = 0 , last_key;

    Element element; 

    while (true) {
        printf("Enter patient details (enter a termination signal to stop):\n\n");

        if (Read_info(temp_patient)) {
            break; 
        }

        Convertion(temp_patient, temp_string);
        last_key = convertKeyToInt(temp_patient.Key) ;
        if (MAX_Block_FILL * factor - 1 - temp_block.Last_index < strlen(temp_string)) {
            temp_block.arr[temp_block.Last_index] = '\0';
            temp_block.next = -1;
            element.Block = block_number;
            element.Key = last_key;
            fseek(index_file,sizeof(Iheader)+sizeof(Element)*block_number,SEEK_SET) ;
            fwrite(&element, sizeof(Element), 1, index_file);
            temp_Iheader.Record_numbers++;
            Write_dir(Filename, block_number, temp_block);
            block_number++;
            temp_block.Last_index = 0;
        }

        for (int i = 0; temp_string[i] != '\0'; i++) {
            temp_block.arr[temp_block.Last_index++] = temp_string[i];
        }

        Set_Header(Filename, 2, Get_Header(Filename, 2) + 1);
    }


    temp_block.arr[temp_block.Last_index] = '\0';
    temp_block.next = -1;
    element.Block = block_number;
    element.Key = last_key;
    fseek(index_file,sizeof(Iheader)+sizeof(Element)*block_number,SEEK_SET) ;
    fwrite(&element, sizeof(Element), 1, index_file);
    temp_Iheader.Record_numbers++;
    Write_dir(Filename, block_number, temp_block);
    block_number++;
    

    Set_Header(Filename, 1, block_number); 
    Set_IHeader(IndexFilename, block_number);

    fclose(index_file);
    printf("Manual initialization completed successfully.\n");
    Element* elements = nullptr;
    Read_ID_Tab(IndexFilename, elements);
    if (elements) {
        printf("Index table contents.\n");
        for (int j = 0; j < temp_Iheader.Record_numbers; j++) {
            printf("Element %d: Key=%d, Block=%d\n", j, elements[j].Key, elements[j].Block);
        }
        delete[] elements;
    }
}
