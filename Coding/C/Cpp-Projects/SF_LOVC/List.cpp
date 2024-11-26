#include "List.h"

Record* Create_node(Student student) {
    Record* temp = (Record*)malloc(sizeof(Record));
    temp->student = student;
    temp->next = nullptr;
    return temp;
}

void Append(Record*& Header, Student student) {
    Record* new_node = Create_node(student);
    if (Header == nullptr) {
        Header = new_node;
    } else {
        Record* temp = Header;
        while (temp->next != nullptr) temp = temp->next;
        temp->next = new_node;
    }
}

void Display_Student_List(Record* Header) {
    Record* temp = Header;
    if (temp == nullptr) {
        printf("Student not found!\n\n");
        return;
    }
    if (temp->next == nullptr) {
        printf("Student Information:\n\n");
        printf("ID: %s, First Name: %s, Last Name: %s, Age: %s\n",
        temp->student.Key, temp->student.First_name,
        temp->student.Last_name, temp->student.Age);
        return;
    }
    printf("Students Information:\n\n");
    int student_number = 1;
    while (temp != nullptr) {
        printf("Student %d:\n", student_number++);
        printf("ID: %s, First Name: %s, Last Name: %s, Age: %s\n",
        temp->student.Key, temp->student.First_name,
        temp->student.Last_name, temp->student.Age);
        temp = temp->next;
    }
}