#include "File_Functions.h"
#include "Generator.h"
#include "List.h"

int main() {
    char filename[] = "output/lovc_records.dat";
    int choice, num_records, value, start, end;
    Student student;
    int key;

    Record* student_header = nullptr;
    Record* range_header = nullptr;
    Record* all_header = nullptr;

    do {
        printf("\nMenu:\n");
        printf("1. Initialize the file with user input\n");
        printf("2. Initialize the file with random data\n");
        printf("3. Insert a student record\n");
        printf("4. Delete a student record\n");
        printf("5. Display a student's information by ID\n");
        printf("6. Display students within a range of IDs\n");
        printf("7. Display all students\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                initialize_file(filename);
                printf("File initialized with user input.\n");
                break;

            case 2:
                printf("Enter the number of random records: ");
                scanf("%d", &num_records);
                initialize_file_with_random_data(filename, num_records);
                printf("File initialized with %d random records.\n", num_records);
                break;

            case 3:
                printf("Enter student details to insert:\n");
                printf("ID: ");
                scanf("%s", student.Key);
                printf("First Name: ");
                scanf("%s", student.First_name);
                printf("Last Name: ");
                scanf("%s", student.Last_name);
                printf("Age: ");
                scanf("%s", student.Age);
                insert_record(filename, student);
                printf("Record inserted successfully.\n");
                break;

            case 4:
                printf("Enter the ID of the student to delete: ");
                scanf("%d", &key);
                Delete_record(filename, key);
                printf("Record deleted if it existed.\n");
                break;

            case 5:
                printf("Enter the ID of the student to display: ");
                scanf("%d", &value);
                student_header = nullptr;
                Search_by_range(filename, value, value, student_header); 
                Display_Student_List(student_header);
                break;

            case 6:
                printf("Enter the range (start end) to display students: ");
                scanf("%d %d", &start, &end);
                range_header = nullptr;
                Search_by_range(filename, start, end, range_header);
                Display_Student_List(range_header);
                break;

            case 7:
                all_header = nullptr;
                Search_by_range(filename, 0, 10000, all_header);
                Display_Student_List(all_header);
                break;

            case 0:
                printf("Exiting the program.\n");
                break;

            default:
                printf("Invalid choice! Please try again.\n");
                break;
        }
    } while (choice != 0);

    return 0;
    system("pause") ;
}
