#include <iostream>
#include <algorithm>
#include <queue>
#include <limits>
#include <ctime>

using namespace std;
struct MinHeapNode
{
    int element;
    int k;
};
struct comp
{
    bool operator()(const MinHeapNode lhs, const MinHeapNode rhs) const
    {
        return lhs.element > rhs.element;
    }
};
FILE* openFile(char* fileName, char* mode)
{
    FILE* fp = fopen(fileName, mode);
    if (fp == NULL)
    {
        perror("Error detected while opening the file.\n");
        exit(EXIT_FAILURE);
    }
    return fp;
}
void mergeFiles(char *output_file, int n, int k)
{
    FILE* in[k];
    for (int j = 0; j < k; j++)
    {
        char fileName[2];
        // convert i to string
        snprintf(fileName, sizeof(fileName), "%d", j);
        int i;
        in[i] = openFile(fileName, "r");
    }
    FILE *out = openFile(output_file, "w");
    MinHeapNode harr[k];
    priority_queue<MinHeapNode, vector<MinHeapNode>, comp> pq;
    for (int i = 0; i < k; i++)
    {
        if (fscanf(in[i], "%d ", &harr[i].element) != 1)
            break;
        harr[i].k = i;
        pq.push(harr[i]);
    }
    int count = 0;
    while (count != k)
    {
        MinHeapNode root = pq.top();
        pq.pop();
        fprintf(out, "%d ", root.element);

        if (fscanf(in[root.k], "%d ", &root.element) != 1 )
        {
            root.element = numeric_limits<int>::max();
            count++;
        }
        // Replace root with next element of input file
        pq.push(root);
    }
    // close input and output files
    for (int i = 0; i < k; i++)
        fclose(in[i]);
    fclose(out);
}
void createInitialRuns(char *input_file, int run_size, int num_ways)
{
    // For big input file
    FILE *in = openFile(input_file, "r");
    // output scratch files
    FILE* out[num_ways];
    char fileName[2];
    for (int i = 0; i < num_ways; i++)
    {
        // convert i to string
        snprintf(fileName, sizeof(fileName), "%d", i);
        // Open output files in write mode.
        out[i] = openFile(fileName, "w");
    }
    int* arr = new int[run_size];
    bool more_input = true;
    int next_output_file = 0;
    int i;
    while (more_input)
    {
        for (i = 0; i < run_size; i++)
        {
            if (fscanf(in, "%d ", &arr[i]) != 1)
            {
                more_input = false;
                break;
            }
        }
        sort(arr, arr + i);
        for (int j = 0; j < i; j++)
            fprintf(out[next_output_file], "%d ", arr[j]);
        next_output_file++;
    }
    // deallocate memory
    delete arr;
    // close input and output files
    for (int i = 0; i < num_ways; i++)
        fclose(out[i]);
    fclose(in);
}
// Program to demonstrate external sorting
int main()
{
    // No. of partitions of input file
    int num_ways = 10;
    // The size of each partition
    int run_size = 1000;
    char input_file[] = "input.txt";
    char output_file[] = "output.txt";
    FILE* in = openFile(input_file, "w");
    srand(time(NULL));
    // generate input
    for (int i = 0; i < num_ways * run_size; i++)
        fprintf(in, "%d ", rand());
    fclose(in);
    createInitialRuns(input_file, run_size, num_ways);
    mergeFiles(output_file, run_size, num_ways);
    return 0;
}