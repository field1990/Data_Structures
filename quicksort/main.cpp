#include <iostream>
#include <iomanip>

using namespace std;

//Printing out contents of array
void dump_array(int* array, int len) {
    for(int i = 0; i < len; i++){
        cout << setw(3) << array[i];
    }
    cout << endl;
}

int split(int* array, int first, int last){

    //Pick a pivot point
    int pivot = array[first];

    //Start left element to the first element, the right to the last
    //Start searching for numbers less than and greater than the pivot
    int left = first;
    int right = last;

    //Keep searching until alll elements are in their correct spots
    while (left < right) {

        //Switch the greater than and less than symbols down below to have things go in descending order instead

        //Move all numbers less than the pivot to the left
        while(pivot < array[right]){
            right--;
        }

        //Move all numbers greater than the pivot to the right
        while(pivot >= array[left]){
            left++;
        }

        //if two were found out of place (order), swap them
        if(left < right){
            int temp = array[left];
            array[left] = array[right];
            array[right] = temp;
            //swap(array[left], array[right]);
        }
    }

    //Now move the pivot between the two sublists
    array[first] = array[right];
    array[right] = pivot;

    return right;
}

void quick_sort(int* array, int first, int last){

    //How to determine it is sorted?
    //When sorting an array of one element, first == last
    //When sorting an array of no elements, first > last

    if(first < last) {
        //Split into sublists
        //"pos" is the position of the "pivot point"
        int pos = split(array, first, last);

        //Sort the left sublist (less than sub array)
        quick_sort(array, first, pos - 1);

        //Sort the right sublist (greater than sub array)
        quick_sort(array, pos + 1, last);
    }
}

int main() {

    int nums[] = {3, 6, 8, 10, 5, 9, 4, 7, 1, 2};
    int len = sizeof(nums)/sizeof(int);

    cout << "Before Sorting..." << endl;
    dump_array(nums, len);

    quick_sort(nums, 0, len - 1);

    cout << "After Sorting..." << endl;
    dump_array(nums, len);

    return 0;
}