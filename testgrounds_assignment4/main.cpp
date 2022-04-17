#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

int main()
{
//    FILE *fp;
//    fp = tmpfile();
//    char writeToFile[50] = "Creating a temporary file";
//
//    if (fp==NULL)
//    {
//        perror("Error creating temporary file");
//        exit(1);
//    }
//
//    fputs(writeToFile,fp);
//    rewind(fp);
//
//    char readFromFile[50];
//    fgets(readFromFile, sizeof(readFromFile), fp);
//    cout << readFromFile;
//    fclose(fp);

    //int value1 = 5;
    //int value2 = 10;

    string value1 = "Abra Kadabra";
    string value2 = "Helllo to all of good night haza";

    if(value1 > value2){
        cout << value1 << " is greater" << endl;
    }
    else if (value1 < value2){
        cout << value2 << " is greater" << endl;
    }

    return 0;
}