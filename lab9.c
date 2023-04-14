#include <stdio.h>
#include <stdlib.h>

// RecordType
struct RecordType
{
    int id;
    char name;
    int order;
    struct RecordType* next;
};

// Fill out this structure
struct HashType
{
    struct RecordType* ptr;
};

// Compute the hash function
int hash(int x, int tableSize)
{
   return x % tableSize;
}

// parses input file to an integer array
int parseData(char *inputFileName, struct RecordType **ppData)
{
    FILE *inFile = fopen(inputFileName, "r");
    int dataSz = 0;
    int i, n;
    char c;
    struct RecordType *pRecord;
    *ppData = NULL;

    if (inFile)
    {
        fscanf(inFile, "%d\n", &dataSz);
        *ppData = (struct RecordType *)malloc(sizeof(struct RecordType) * dataSz);
        // Implement parse data block
        if (*ppData == NULL)
        {
            printf("Cannot allocate memory\n");
            exit(-1);
        }
        for (i = 0; i < dataSz; ++i)
        {
            pRecord = *ppData + i;
            fscanf(inFile, "%d ", &n);
            pRecord->id = n;
            fscanf(inFile, "%c ", &c);
            pRecord->name = c;
            fscanf(inFile, "%d ", &n);
            pRecord->order = n;
            pRecord->next = NULL;
        }

        fclose(inFile);
    }

    return dataSz;
}

// prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
    int i;
    printf("\nRecords:\n");
    for (i = 0; i < dataSz; ++i)
    {
        printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
    }
    printf("\n\n");
}

// insert record into the hash table
void insertRecord(struct HashType *hashTable, struct RecordType *record, int tableSize)
{
    int index = hash(record->id, tableSize);
    if (hashTable[index].ptr == NULL)
    {
        hashTable[index].ptr = record;
    }
    else
    {
        struct RecordType* current = hashTable[index].ptr;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = record;
    }
}

// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct HashType *hashTable, int tableSize)
{
	for (int i = 0; i < tableSize; i++)
	{
            printf("Index %d -> ", i);
            if (hashTable[i].ptr == NULL) 
            {
                printf("NULL\n");
            }
	
            else 
            {
            struct RecordType* current = hashTable[i].ptr;
            printf("%d, %c, %d", current->id, current->name, current->order);
            while (current->next != NULL) 
            {
                current = current->next;
                printf(" -> %d, %c, %d", current->id, current->name, current->order);
            }

            printf(" -> NULL\n");
        }
    }
}

int main(void)
{
    struct RecordType *pRecords;
    int recordSz = 0;

    recordSz = parseData("input.txt", &pRecords);
    printRecords(pRecords, recordSz);

    struct HashType *hashTable = NULL;
    int tableSize = 11;
    hashTable = (struct HashType*)calloc(sizeof(struct HashType), tableSize);

    for (int i = 0; i < recordSz; i++)
    {
        insertRecord(hashTable, &pRecords[i], tableSize);
    }

    displayRecordsInHash(hashTable, tableSize);

    free(pRecords);
    free(hashTable);

    return 0;
}
