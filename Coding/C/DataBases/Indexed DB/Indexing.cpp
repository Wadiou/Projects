#include "Indexing.h"

void Set_IHeader(char Filename[], int value) {
    Iheader header;
    FILE *file = fopen(Filename, "rb+");
    fread(&header, sizeof(Iheader), 1, file);
    header.Record_numbers = value ;
    fseek(file, 0, SEEK_SET);
    fwrite(&header, sizeof(Iheader), 1, file);
    fclose(file);
}
int Get_IHeader(char Filename[]) {
    Iheader header;
    FILE *file = fopen(Filename, "rb");
    fread(&header, sizeof(Iheader), 1, file);
    fclose(file);
    return header.Record_numbers ;
}
void Read_ID_Tab(char Filename[], Element *&Elems) {
    FILE *file = fopen(Filename, "rb");
    int Block_number = Get_IHeader(Filename);
    fseek(file, sizeof(Iheader), SEEK_SET);
    Elems = new Element[Block_number + 1];
    fread(Elems, sizeof(Element), Block_number, file);
    fclose(file);

}

void Write_ID_Tab(char Filename[], Element *Elems, int Block_number) {
    FILE *file = fopen(Filename, "rb+");
    Set_IHeader(Filename,Block_number);
    fseek(file, sizeof(Iheader), SEEK_SET);
    fwrite(Elems, sizeof(Element), Block_number, file);
    fclose(file);
}
void Search_Index(char Filename[], int ID, bool &found, int &block) {

    Element* elements = nullptr;
    int num_records = Get_IHeader(Filename);

    Read_ID_Tab(Filename, elements);

    found = false;
    int left = 0, right = num_records - 1;

    while (left <= right) {
        int mid = (right + left) / 2;

        if (elements[mid].Key == ID) {
            block = elements[mid].Block;
            found = true;
            break;
        } else if (elements[mid].Key < ID) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    if (!found) {
        block = elements[left].Block;
    }

    delete[] elements;
}

int Search_Index_Array(char Filename[], int ID ,bool &found) {
    Element* elements = nullptr;
    int num_records = Get_IHeader(Filename);
    found = false ;
    Read_ID_Tab(Filename, elements);

    int left = 0, right = num_records - 1;

    while (left <= right) {
        int mid = (right + left) / 2;
        if (elements[mid].Key == ID) {
            delete[] elements;
            found = true ;
            
            return mid;
        } else if (elements[mid].Key < ID) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    delete[] elements;
    return left;
}


void shift_index(char Filename[], int start, int length) {
    Element* elements = nullptr;
    int num_records = Get_IHeader(Filename);
    int updated_records = num_records + length;
    Set_IHeader(Filename, updated_records);
    Read_ID_Tab(Filename, elements);

    for (int i = num_records - 1; i >= start; i--) 
    {
        elements[i + length] = elements[i];
    }

    Write_ID_Tab(Filename, elements, updated_records);


    delete[] elements;
}

void fill_index(char Filename[], int index, int key, int block) {
    Element* elements = nullptr;
    int num_records = Get_IHeader(Filename);

    Read_ID_Tab(Filename, elements);
    elements[index].Key = key;
    elements[index].Block = block;

    Write_ID_Tab(Filename, elements, num_records);
    delete[] elements;
}

void add_index_to_table(char Filename[], int key, int block, bool shift) {
    int num_records = Get_IHeader(Filename);
    bool found ;

    int insert_index = Search_Index_Array(Filename, key , found);
    if (!found)
    {
        if (shift)
        {
            shift_index(Filename, insert_index, 1);
        }
        fill_index(Filename, insert_index, key, block);
    }
    
}

