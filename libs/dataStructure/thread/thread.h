//
// Created by kent on 29.05.2024.
//

#include <corecrt.h>

#define ROWS_1 4
#define COLS_1 3
#define ROWS 3
#define COLS 3
#define MAX_DOMAIN_LENGTH 256
#define MAX_COUNT 10000

typedef struct {
    char domain[MAX_DOMAIN_LENGTH];
    int count;
} Domain;

typedef struct tree {
    int digit;
    struct tree *right;
    struct tree *left;
} Tree;

//метод для решения 1-й задачи (добавление единиц в матрицу)
int** addOneToMatrix(size_t size, int **query, int querySize);

void nextGeneration(int board[ROWS_1][COLS_1]);

void printBoard(int board[ROWS_1][COLS_1]);

int countNeighbors(int board[ROWS_1][COLS_1], int i, int j);

void applyMedianFilter(int matrix[ROWS][COLS], int filterSize);

int findMedian(int arr[], int n);

void sortArray(int arr[], int n);

void printMatrix(int matrix[ROWS][COLS]);

void countDomen(char* cpdomains[]);

int compare(const void *a, const void *b);

int countSubmatrices(int matrix[ROWS][COLS]);

char * increaseAndDecreaseByIandD(char* pattern, char* result);


void printTreeInOrder(Tree* node);

int returnMaxDigit(const int *nums, size_t size);

Tree* buildTree(const int *nums, int left, int right);

Tree* createNode(int value);

void swap(char* a, char* b);

void permute(char* s, int* indices, int n);
