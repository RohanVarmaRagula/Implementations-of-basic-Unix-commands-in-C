#include<stdio.h>
#include<dirent.h>
#include<string.h>

// d_type = 4 : directory
// d_type = 8 : file

void ls(char *path) {
    int count = 0;
    DIR *dir = opendir(path);
    struct dirent *d;
    while((d = readdir(dir)) != NULL) {
        if (strcmp(d->d_name, ".") == 0) continue;
        if (strcmp(d->d_name, "..") == 0) continue;
        count ++;
        printf("%s ", d->d_name);
    } 
    closedir(dir);
    if (count != 0)
        printf("\n");
}
void lsa(char *path) {
    DIR *dir = opendir(path);
    struct dirent *d;
    while((d = readdir(dir)) != NULL) {
        printf("%s ", d->d_name);
    }
    closedir(dir); 
    printf("\n");
}
void lsR(char *path) {
    DIR *dir = opendir(path);
    printf("%s:\n", path);
    ls(path);
    printf("\n");
    struct dirent *d;
    while((d = readdir(dir)) != NULL) {
        if (strcmp(".", d->d_name) == 0) continue;
        if (strcmp("..", d->d_name) == 0) continue;
        if (d->d_type == DT_DIR) {
            char new_path[1024];
            snprintf(new_path, sizeof(new_path), "%s/%s", path, d->d_name);
            lsR(new_path);
        }
    }
    closedir(dir);
}




int main(int argc, char *argv[]) {
    char path[1024] = ".";
    if (argc == 1) {
        ls(path);
    } else if (argc == 2) {
        if (strcmp(argv[1], "-a") == 0) {
            lsa(path);
        } else if (strcmp(argv[1], "-l") == 0) {
            // ls -l
        } else if (strcmp(argv[1], "-R") == 0) {
            lsR(path);
        } else {
            snprintf(path, sizeof(path), "./%s", argv[1]);
            ls(path);
        }
    }
}
