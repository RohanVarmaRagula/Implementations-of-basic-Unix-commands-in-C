#include<iostream>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>
using namespace std;

int main(int argc, char *argv[]) {
    if (argv[1][0] == '-') {
        char buff[10];
        sscanf(argv[1], "-%s", buff);
        int sig = atoi(buff);
        for (int i=2;i<argc;i++) {
            int pid = atoi(argv[i]);
            kill(pid, sig);
        }
    } else {
        for (int i=1;i<argc;i++) {
            int pid = atoi(argv[i]);
            kill(pid, SIGTERM);
        }
    }
}