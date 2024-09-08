# include<stdio.h>
# include<string.h>

int main(int argc, char* argv[]) {
    if (argc < 2) 
        return 0;
    if (argc == 2)
        remove(argv[1]);
    else if (strcmp("-i", argv[1]) == 0) {
        for (int i = 2; i < argc; i ++) {
            printf("rm: remove file '%s'? ", argv[i]);
            char ch;
            scanf(" %c", &ch);
            if (ch == 'Y' || ch == 'y') 
                remove(argv[i]);
            else if (ch == 'N' || ch == 'n') 
                continue;
        }
    } else {
        for (int i = 1; i < argc; i ++) 
            remove(argv[i]);
    }

    return 0;
}