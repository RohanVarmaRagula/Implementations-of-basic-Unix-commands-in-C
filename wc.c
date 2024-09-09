# include<stdio.h>
# include<ctype.h>

int newline = 0, wc = 0, byteCount = 0;

void WC(char* path) {
    FILE *file = fopen(path, "r");
    
    if (file == NULL) {
        printf("Error opening file\n");
        return;
    }

    int curr_newline = 0, curr_wc = 0, curr_byteCount = 0;
    int isWord = 0;

    char ch;
    while((ch = fgetc(file)) != EOF) {
        curr_byteCount ++;

        if (ch == '\n') {
            curr_newline ++;
            isWord = 0;
        } else if (isspace(ch)) {
            isWord = 0;
        } else if (isWord == 0) {
            curr_wc ++;
            isWord = 1;
        }
    }

    printf("%d %d %d %s\n", curr_newline, curr_wc, curr_byteCount, path);

    newline += curr_newline;
    wc += curr_wc;
    byteCount += curr_byteCount;
}

int main(int argc, char* argv[]) {
    
    for (int i = 1; i < argc; i ++) 
        WC(argv[i]);

    if (argc > 2) 
        printf("%d %d %d total\n", newline, wc, byteCount);

    return 0;
}