#include "thread.h"
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//1-я задача
int** addOneToMatrix(size_t size, int **query, int querySize) {
    int **matrix = (int **)malloc(size * sizeof(int *));
    for (size_t i = 0; i < size; i++) {
        matrix[i] = (int *)malloc(size * sizeof(int));
    }

    // заполнение нулями
    for (size_t i = 0; i < size; i++) {
        for (size_t j = 0; j < size; j++) {
            matrix[i][j] = 0;
        }
    }

    for (size_t i = 0; i < querySize; i++) {
        int row1 = query[i][0];
        int col1 = query[i][1];
        int row2 = query[i][2];
        int col2 = query[i][3];

        for (size_t x = row1; x <= row2; x++) {
            for (size_t y = col1; y <= col2; y++) {
                matrix[x][y]++;
            }
        }
    }

    // Вывод матрицы
    for (size_t i = 0; i < size; i++) {
        for (size_t j = 0; j < size; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    return matrix; // Return the matrix
}

//2-я задача
int countNeighbors(int board[ROWS_1][COLS_1], int i, int j) {
    int count = 0;
    for (int x = -1; x <= 1; x++) {
        for (int y = -1; y <= 1; y++) {
            int nx = (i + x + ROWS_1) % ROWS_1;
            int ny = (j + y + COLS_1) % COLS_1;
            count += board[nx][ny];
        }
    }
    count -= board[i][j];
    return count;
}

void printBoard(int board[ROWS_1][COLS_1]) {
    for (int i = 0; i < ROWS_1; i++) {
        for (int j = 0; j < COLS_1; j++) {
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }
}
void nextGeneration(int board[ROWS_1][COLS_1]) {
    int next[ROWS_1][COLS_1];
    for (int i = 0; i < ROWS_1; i++) {
        for (int j = 0; j < COLS_1; j++) {
            int neighbors = countNeighbors(board, i, j);
            if (board[i][j] == 1) {
                if (neighbors < 2 || neighbors > 3) {
                    next[i][j] = 0;
                } else {
                    next[i][j] = 1;
                }
            } else {
                if (neighbors == 3) {
                    next[i][j] = 1;
                } else {
                    next[i][j] = 0;
                }
            }
        }
    }
    for (int i = 0; i < ROWS_1; i++) {
        for (int j = 0; j < COLS_1; j++) {
            board[i][j] = next[i][j];
        }
    }
}
void printMatrix(int matrix[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void sortArray(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int findMedian(int arr[], int n) {
    sortArray(arr, n);
    return arr[n / 2];
}

void applyMedianFilter(int matrix[ROWS][COLS], int filterSize) {
    int paddedMatrix[ROWS + filterSize - 1][COLS + filterSize - 1];
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            paddedMatrix[i + filterSize / 2][j + filterSize / 2] = matrix[i][j];
        }
    }

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            int window[filterSize * filterSize];
            int k = 0;
            for (int x = -filterSize / 2; x <= filterSize / 2; x++) {
                for (int y = -filterSize / 2; y <= filterSize / 2; y++) {
                    window[k++] = paddedMatrix[i + x][j + y];
                }
            }
            matrix[i][j] = findMedian(window, filterSize * filterSize);
        }
    }
}
int compare(const void *a, const void *b) {
    Domain *domain1 = (Domain *)a;
    Domain *domain2 = (Domain *)b;
    return strcmp(domain1->domain, domain2->domain);
}
void countDomen(char* cpdomains[]) {
    Domain domains[MAX_COUNT];
    int domainCount = 0;
    for (int i = 0; i < MAX_COUNT; i++) {
        char *token = strtok(cpdomains[i], " ");
        if (token == NULL) break;
        int count = atoi(token);
        token = strtok(NULL, " ");
        char *domain = token;

        while (domain) {
            Domain domainData;
            strcpy(domainData.domain, domain);
            domainData.count = count;
            domains[domainCount++] = domainData;

            char *dot = strchr(domain, '.');
            while (dot) {
                *dot = '\0';
                strcpy(domainData.domain, domain);
                domainData.count = count;
                domains[domainCount++] = domainData;
                *dot = '.';
                dot = strchr(dot + 1, '.');
            }

            token = strtok(NULL, " ");
            domain = token;
        }
    }

    qsort(domains, domainCount, sizeof(Domain), compare);

    for (int i = 0; i < domainCount; i++) {
        int total_count = domains[i].count;
        while (i + 1 < domainCount && strcmp(domains[i].domain, domains[i+1].domain) == 0) {
            total_count += domains[i+1].count;
            i++;
        }
        printf("%d %s\n", total_count, domains[i].domain);
    }
}

int countSubmatrices(int matrix[ROWS][COLS]) {
    int nums[ROWS][COLS];
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (matrix[i][j] == 0) {
                nums[i][j] = 0;
            } else {
                nums[i][j] = (j > 0 ? nums[i][j - 1] : 0) + 1;
            }
        }
    }

    int count = 0;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            for (int k = j; k < COLS; k++) {
                int min_val = nums[i][j];
                for (int l = i; l < ROWS; l++) {
                    min_val = (nums[l][k] < min_val ? nums[l][k] : min_val);
                    count += min_val;
                }
            }
        }
    }

    return count;
}

char * increaseAndDecreaseByIandD(char* pattern, char* result) {
    int n = strlen(pattern);
    int nums[10] = {0};
    char num[n+1];

    int currentMin = 0, currentMax = 9, index = 0;

    for (int i = 0; i <= n; i++) {
        if (i == n || pattern[i] == 'I') {
            result[i] = '\0';
            while (nums[currentMin]) currentMin++;
            nums[currentMin] = 1;
            num[index++] = '0' + currentMin;
            for (int j = index - 1; j >= 0; j--) {
                for (int k = num[j + 1] ? num[j + 1] - '0' : currentMax; k > num[j] - '0'; k--) {
                    if (!nums[k]) {
                        nums[k] = 1;
                        num[j] = '0' + k;
                        for (int l = j + 1; l < index; l++) {
                            for (int m = currentMin; m <= currentMax; m++) {
                                if (!nums[m]) {
                                    nums[m] = 1;
                                    num[l] = '0' + m;
                                    break;
                                }
                            }
                        }
                        currentMin = 0;
                        index = n;
                        break;
                    }
                }
            }
        } else {
            result[i] = '9';
            nums[9] = 1;
            for (int j = n - i; j > 0; j--) {
                for (int k = '0' + currentMax; k >= '0'; k--) {
                    if (!nums[k - '0']) {
                        result[i+j] = k;
                        nums[k - '0'] = 1;
                        currentMax = k - '0' - 1;
                        break;
                    }
                }
            }
        }
    }
}
int returnMaxDigit(const int *nums, size_t size) {
    int max = 0;
    for (int i = 0; i < size; i++) {
        if (nums[i] > max) {
            max = nums[i];
        }
    }
    return max;
}

Tree* createNode(int value) {
    Tree* newNode = (Tree*)malloc(sizeof(Tree));
    newNode->digit = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Tree* buildTree(const int *nums, int left, int right) {
    if (left > right) {
        return NULL;
    }

    int maxIndex = left;
    for (int i = left + 1; i <= right; i++) {
        if (nums[i] > nums[maxIndex]) {
            maxIndex = i;
        }
    }

    Tree* root = createNode(nums[maxIndex]);
    root->left = buildTree(nums, left, maxIndex - 1);
    root->right = buildTree(nums, maxIndex + 1, right);

    return root;
}

void printTreeInOrder(Tree* node) {
    if (node == NULL) {
        return;
    }
    printTreeInOrder(node->left);
    printf("%d ", node->digit);
    printTreeInOrder(node->right);
}

void swap(char* a, char* b) {
    char t = *a;
    *a = *b;
    *b = t;
}

void permute(char* s, int* indices, int n) {
    for (int i = 0; i < n; i++) {
        if (indices[i] != i) {
            swap(&s[i], &s[indices[i]]);
            int temp = indices[i];
            indices[i] = indices[temp];
            indices[temp] = temp;
        }
    }
}


