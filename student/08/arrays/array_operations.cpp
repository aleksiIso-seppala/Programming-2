#include "array_operations.hh"

int greatest_v1(int* itemptr, int size){

    int* pointer = nullptr;
    pointer = itemptr;
    int largest_number = *itemptr;
    while(pointer < itemptr+size){
        if (largest_number < *pointer){
            largest_number = *pointer;
        }
        ++pointer;
        continue;
    }
    return largest_number;
}

int greatest_v2(int* itemptr, int* endptr){

    int* pointer = nullptr;
    pointer = itemptr;
    int largest_number = *itemptr;
    while(pointer < endptr){
        if (largest_number < *pointer){
            largest_number = *pointer;
        }
        ++pointer;
        continue;
    }
    return largest_number;
}

void copy(int* itemptr, int* endptr, int* targetptr){

    for(; itemptr != endptr; ++itemptr, ++targetptr){

        *targetptr = *itemptr;
        continue;
    }
    return;

}

void reverse(int* leftptr, int* rightptr){

    for(--rightptr; leftptr < rightptr; ++leftptr, --rightptr){

        int tmp = *leftptr;
        *leftptr = *rightptr;
        *rightptr = tmp;
    }
}
