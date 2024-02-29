#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fcntl.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
    int pid;
    int p[2];
    pipe(p);

    if (!fork()) {
        //child
        pid = getpid();
        char buf[2];
        if (read(p[0], buf, 1) != 1) {
            fprintf(2, "failed to read in child\n");
            exit(1);
        }
        close(p[0]);
        printf("%d: received ping\n", pid);
        if (write(p[1], buf, 1) != 1) {
            fprintf(2, "failed to write in child\n");
            exit(1);
        }
        close(p[1]);
        exit(0);
    } else {
        pid = getpid();
        char buf[2];
        char info[2] = 'a';
        buf[1] = 0;

        if (write(p[1], info, 1) != 1) {
            fprintf(2, "failed to write in parent\n");
            exit(1);
        }

        close(p[1]);
        wait(0);
        if (read(p[0], info, 1) != 1) {
            fprintf(2, "failed to read in parent\n");
            exit(1);
        }
        printf("%d: received pong\n", pid);
        close(p[0]);
        exit(0);
    }

    exit(0);
}

