#include "List.h"

Record* Create_node(const Patient& patient, const Tindex& index) {
    Record* temp = (Record*)malloc(sizeof(Record));
    if (temp == nullptr)
    {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }
    temp->patient = patient;
    temp->index = index;
    temp->next = nullptr;
    return temp;
}

void Append(Record*& Header, const Patient& patient, const Tindex& index) {
    Record* new_node = Create_node(patient, index);
    if (Header == nullptr) 
    {
        Header = new_node;
    }
    else 
    {
        Record* temp = Header;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}

void Display_patient_List(const Record* Header) {
    const Record* temp = Header;
    if (temp == nullptr) 
    {
        printf("No patients found!\n\n");
        return;
    }
    if (temp->next == nullptr) 
    {
        printf("Patient Information:\n\n");
        printf("ID: %s, First Name: %s, Last Name: %s, Department: %s, Age: %s\n",
               temp->patient.Key, temp->patient.First_name,
               temp->patient.Last_name, temp->patient.Department,
               temp->patient.Age);
        printf("Located at Block Number: %d, Block Index: %d\n\n",
               temp->index.Block_number, temp->index.Block_index);
        return;
    }
    int patient_number = 1;
    while (temp != nullptr) 
    {
        printf("Patient %d:\n", patient_number++);
        printf("ID: %s, First Name: %s, Last Name: %s, Department: %s, Age: %s\n",
               temp->patient.Key, temp->patient.First_name,
               temp->patient.Last_name, temp->patient.Department,
               temp->patient.Age);
        printf("Located at Block Number: %d, Block Index: %d\n\n",
               temp->index.Block_number, temp->index.Block_index);
        temp = temp->next;
    }
}