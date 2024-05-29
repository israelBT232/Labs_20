#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int main(int argc, char *argv[]) {
    SetConsoleOutputCP(CP_UTF8);
    if (argc < 4) {
        printf("Использование: программа <исходный_файл> <новый_файл> <N>\n");
        return 1;
    }

    char *inputFileName = argv[1];
    char *outputFileName = argv[2];
    int N = atoi(argv[3]);

    FILE *inputFile = fopen(inputFileName, "r");
    FILE *outputFile = fopen(outputFileName, "w");

    if (inputFile == NULL || outputFile == NULL) {
        printf("Ошибка открытия файлов.\n");
        return 1;
    }

    int num;
    while (fscanf(inputFile, "%d", &num) == 1) {
        if (num < N) {
            fprintf(outputFile, "%d\n", num);
        }
    }

    fclose(inputFile);
    fclose(outputFile);

    printf("Файл успешно создан с числами, меньшими чем %d.\n", N);

    return 0;
}
