#include <iostream>
#include <dirent.h>
#include <sys/types.h>
#include <string.h>
#include <pwd.h>
#include <iomanip> 

using namespace std;

DIR* dir = opendir("/proc");

void print_info(char *pid, char* username = NULL) {
    string path = "/proc/" + string(pid) + "/status";
    FILE* status_file = fopen(path.c_str(), "r");
    char buff[1024];
    char name[256], uid[256];
    while(fgets(buff, sizeof(buff), status_file)) {
        if (strncmp(buff, "Name:" , 5) == 0)
            sscanf(buff, "Name: %s", name);
        if (strncmp(buff, "Uid:", 4) == 0)
            sscanf(buff, "Uid: %s", uid);
    }
    fclose(status_file);

    uid_t UID = atoi(uid);
    passwd *p = getpwuid(UID);

    if (username == NULL or strcmp(p->pw_name, username) == 0)
        cout << left << setw(7) << pid 
             << left << setw(7) << p->pw_name 
             << name << endl;
}

void ps(char *username = NULL) {
    cout << left << setw(7) << "PID"
         << left << setw(7) << "USER"
         << "COMMAND" << endl;
    struct dirent *entry;
    while((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_DIR and atoi(entry->d_name) > 0)
            print_info(entry->d_name, username);
    }
}

int main(int argc, char* argv[]) {
    if (argc == 1) 
        ps();
    else if (argc == 2) {
        if (argv[1][0] == '-' and argv[1][1] == 'u') {
            char username[1024];
            sscanf(argv[1], "-u%s", username);
            ps(username);
        }
    }
    closedir(dir);
}