#include "File_Functions.h"
#include "Generator.h"
#include "List.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TerminalTitle.h"

int main() {
    show_project_title() ;

    char filename[] = "output/lovc_records.dat";
    char IndexFile[] = "output/lovc_index.dat";
    int choice, num_records, value, start, end;
    double factor = 0.75;
    Patient patient;
    int key;

    Record* patient_header = nullptr;
    Record* range_header = nullptr;
    Record* all_header = nullptr;

    do {
        printf("\nMenu:\n");
        printf("1. Initialize the file with user input\n");
        printf("2. Initialize the file with random data\n");
        printf("3. Insert a patient record\n");
        printf("4. Delete a patient record\n");
        printf("5. Display a patient's information by ID\n");
        printf("6. Display patients within a range of IDs\n");
        printf("7. Display all patients\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the fill factor (e.g., 0.75): ");
                scanf("%lf", &factor);
                initialize_file(filename, IndexFile, factor);
                printf("File initialized with user input.\n");
                break;

            case 2:
                printf("Enter the fill factor (e.g., 0.75): ");
                scanf("%lf", &factor);
                printf("Enter the number of random records: ");
                scanf("%d", &num_records);
                initialize_file_with_random_data(filename, IndexFile, num_records, factor);
                printf("File initialized with %d random records.\n", num_records);
                break;

            case 3:
                printf("Enter patient details to insert:\n");
                printf("ID: ");
                scanf("%s", patient.Key);
                printf("First Name: ");
                scanf("%s", patient.First_name);
                printf("Last Name: ");
                scanf("%s", patient.Last_name);
                printf("Department: ");
                scanf("%s", patient.Department);
                printf("Age: ");
                scanf("%s", patient.Age);
                insert_record(filename, IndexFile, patient);
                printf("Record inserted successfully.\n");
                break;

            case 4:
                printf("Enter the ID of the patient to delete: ");
                scanf("%d", &key);
                Delete_record(filename, IndexFile, key);
                printf("Record deleted if it existed.\n");
                break;

            case 5:
                printf("Enter the ID of the patient to display: ");
                scanf("%d", &value);
                patient_header = nullptr;
                Search_for_record(filename, IndexFile, value, patient_header);
                if (patient_header) {
                    Display_patient_List(patient_header);
                } else {
                    printf("No record found with ID %d.\n", value);
                }
                break;

            case 6:
                printf("Enter the range (start end) to display patients: ");
                scanf("%d %d", &start, &end);
                range_header = nullptr;
                Search_by_range(filename, IndexFile, start, end, range_header);
                if (range_header) {
                    Display_patient_List(range_header);
                } else {
                    printf("No records found in the range [%d, %d].\n", start, end);
                }
                break;

            case 7:
                all_header = nullptr;
                Search_all(filename,IndexFile,all_header) ;
                if (all_header) {
                    Display_patient_List(all_header);
                } else {
                    printf("No records found.\n");
                }
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
}
