#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void handle_signal(int signum) {
    printf("\n");
    fflush(stdout);
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Неверное количество аргументов. Использование: %s <файл> <N>\n", argv[0]);
        return 1;
    }

    FILE* file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Не удается открыть файл %s для чтения\n", argv[1]);
        return 1;
    }

    int N = atoi(argv[2]);
    if (N <= 0) {
        printf("Значение N должно быть больше нуля\n");
        fclose(file);
        return 1;
    }

    char line[1024];
    int lineCount = 0;

    signal(SIGINT, handle_signal);

    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
        fflush(stdout);

        lineCount++;
        if (lineCount == N) {
            lineCount = 0;
            signal(SIGINT, handle_signal);
            sleep(1);
        }
    }

    fclose(file);

    return 0;
}
