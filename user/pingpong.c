#include <kernel/types.h>
#include <kernel/stat.h>
#include <user/user.h>

int main(int argc, char *argv[]) {
    int pipe1[2];
    int pipe2[2];

    if (pipe(pipe1) != 0 || pipe(pipe2) != 0) {
        fprintf(2, "Pipe is not created!\n");
        exit(1);
    }

    int pid = fork();
    if (pid > 0) {
        write(pipe1[1], "c", 1);
        char checkParent[1];
        read(pipe2[0], &checkParent[0], 1);
        printf("%d: received pong\n", getpid());
    } else if (pid == 0) {
        char check[1];
        if (read(pipe1[0], &check[0], 1) != 1) {
            fprintf(2, "Error reading from pipe\n");
        }
        printf("%d: received ping\n", getpid());
        write(pipe2[1], "d", 1);
        exit(0);
    } else {
        fprintf(2, "Child process is not created\n");
        exit(1);
    }
    exit(0);
}
