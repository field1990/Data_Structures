#include <iostream>
#include <iomanip>
using namespace std;
void dumparray(int *array, int len) {
    for (int i = 0; i < len; ++i) {
        cout << setw(3) << array[i];
    }
    cout << endl;
}
//Split function, the inarray, the length, two temporary arrays from the merge sort, split them into two other temporary arrays
//Don't need some of these when dealing with files
void split(int *inarray, int len, int *outarray1, int *outsize1, int *outarray2, int *outsize2) {

    *outsize1 = 0;
    *outsize2 = 0;

    // not needed for file version
    //This is to keep track of the index
    int in = 0;

    // The total number of subfiles
    //When number is even write to the first temporary file, odd write to the other file
    int subFiles = 0;

    //Read in first record

    int curr;
    int next = inarray[in++];

    // loop until no more records to split
    //Would be read until end of file for dealing with files
    // while there are records available, keep looping
    while ( in <= len){

        // extract one ordered sublist
        // and put into correct temp location
        //loop until no more records in the current ordered list
        do {
            curr = next;

            //read in the next record
            //Have to check end of file for files?
            if(in < len){
                next = inarray[in];
            }
            //Moves on to next position
            in++;

            // determine odd/even
            // put record in the correct location
            if(subFiles % 2 == 0){
                //even, write record to first temporary file
                outarray1[(*outsize1)++] = curr;
            } else {
                // odd, write to second temporary file
                outarray2[(*outsize2)++] = curr;
            }

        // do it while the value in the list is greater than the current or until the end of the array
        } while ((curr < next) && (in <= len));
        subFiles++;
    }

}

int merge(int *outarray, int *outsize, int *inarray1, int insize1, int *inarray2, int insize2) {

    // write out remaining records from the file that still has some

    // not needed in the file version
    int in1 = 0;
    int in2 = 0;

    // the total number of subfiles left after merge
    int subFiles = 0;

    *outsize = 0;

    //Read one record from each file
    int curr1;
    int curr2;
    int prev1;
    int prev2;
    // start at the beginning of each subarray
    curr1 = inarray1[in1++];
    curr2 = inarray2[in2++];

    //loop while both files have records, if file version looking for end of file
    // keep going while both arrays have elements
    while( in1 <= insize1 && in2 <= insize2 )
    {
        bool endOfSub1 = false;
        bool endOfSub2 = false;

        // loop through one sublist at a time
        // move through both arrays until an ordered
        // sublist is completed
        while( !endOfSub1 && !endOfSub2 )
        {
            //compare records
            // use the element from array 1, if it is lower
            if( curr1 <= curr2 )
            {
                // write out appropriate record

                // store the element in the merged array
                outarray[(*outsize)++] = curr1;

                // read the next one in
                // move to next element
                prev1 = curr1;
                //Check to see if I haven't crossed end of file if reading from a file
                if( in1 < insize1 )
                {
                    curr1 = inarray1[in1];
                }
                //Move to the next element
                in1++;
                // did I cross to a different sublist?
                // did we hit the end of a sublist?
                // or did we reach the end of file or in this case array
                if( (in1 > insize1) || (prev1 > curr1) )
                {
                    // That sublist has ended
                    endOfSub1 = true;
                }
            }
            // use the element from array 2, if it is lower
            if( curr2 <= curr1 )
            {
                // write out appropriate record
                // read the next one in
                // store the element in the merged array
                outarray[(*outsize)++] = curr2;
                // move to next element
                prev2 = curr2;
                if( in2 < insize2 )
                {
                    curr2 = inarray2[in2];
                }
                in2++;
                // did we hit the end of a sublist?
                if( (in2 > insize2) || (prev2 > curr2) )
                {
                    endOfSub2 = true;
                }
            }
        }

        // write out remaining records from the same sublist in the file that still has some
        // we finished with array 2, so dump the remaining ordered
        // elements from array 1 into the merged array
        while( !endOfSub1 )
        {
            // add to merged array
            outarray[(*outsize)++] = curr1;
            // move to next element
            prev1 = curr1;
            if( in1 < insize1 )
            {
                curr1 = inarray1[in1];
            }
            in1++;
            // are we at the end of the sublist yet?
            if( (in1 > insize1) || (prev1 > curr1) )
            {
                endOfSub1 = true;
            }
        }
        // we finished with array 1, so dump the remaining ordered
        // elements from array 2 into the merged array
        while( !endOfSub2 )
        {
            // add to merged array
            outarray[(*outsize)++] = curr2;
            // move to next element
            prev2 = curr2;
            if( in2 < insize2 )
            {
                curr2 = inarray2[in2];
            }
            in2++;
            // are we at the end of the ordered sublist yet?
            if( (in2 > insize2) || (prev2 > curr2) )
            {
                endOfSub2 = true;
            }
        }
        // we can now assume we have merged one complete sublist
        // so, let's move on to the next one, while we still have
        // elements in our arrays
        subFiles++;
    }
    // dump remaining elements from array 1
    // Are there any records left in the first array, or in the file when reading in a file
    while( in1 <= insize1 )
    {
        outarray[(*outsize)++] = curr1;
        // move to next element
        prev1 = curr1;
        if( in1 < insize1 )
        {
            curr1 = inarray1[in1];
        }
        in1++;
        // keep track of sublists within remaining elements
        if( (in1 > insize1) || (prev1 > curr1) )
        {
            subFiles++;
        }
    }
    // dump the remaining elements from array 2
    while( in2 <= insize2 )
    {
        outarray[(*outsize)++] = curr2;
        // move to next element
        prev2 = curr2;
        if( in2 < insize2 )
        {
            curr2 = inarray2[in2];
        }
        in2++;
        // we still need to keep track of sublists within the remaining elements
        if( (in2 > insize2) || (prev2 > curr2) )
        {
            subFiles++;
        }
    }
    //Return the number of subfiles back to the calling function
    return subFiles;
}
void mergesort(int* array, int len) {
    int subFiles = 0;
    //Two temporary arrays to hold things into
    int *temp1 = new int[len];
    int *temp2 = new int[len];

    //Have to know how many of these things are in the array to move through it, don't need to do it for files
    int tempsize1;
    int tempsize2;
    // keep splitting and merging until you have 1 subfile
    // loop until completely sorted
    do {
        // split
        split(array, len, temp1, &tempsize1, temp2, &tempsize2);

        // merge
        subFiles = merge(array, &len, temp1, tempsize1, temp2, tempsize2);
    // If you have one subfile, stop looping, you have a sorted list
    } while (subFiles != 1);
    //Free up temporary arrays when I'm done with them, in the case of files, close them
    delete [] temp1;
    delete [] temp2;
}
int main() {
    //int nums[] = {3,6,8,10,5,9,4,1,2,7};
    int nums[] = {5,3,9,0};
    int len = sizeof(nums)/sizeof(int);

    cout << "Before Sorting..." << endl;
    dumparray(nums, len);

    mergesort(nums, len);

    cout << "After Sorting..." << endl;
    dumparray(nums, len);
    return 0;
}