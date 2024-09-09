#include <stdio.h>

void cat(char* path) {
    FILE *file = fopen(path, "r");

    if (file == NULL) {
        printf("Error opening the file\n");
        return;
    }

    char buff[1024];
    while (fgets(buff, sizeof(buff), file)) {
        printf("%s", buff);
    }

    fclose(file);
}

int main(int argc, char* argv[]) {
    for (int i = 1; i < argc; i ++) {
        cat(argv[i]);
    }
}