#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

void run(char * program, char ** argv) {
    if (!fork()) {
        exec(program, argv);
        exit(0);
    }
}

int main(int argc, char ** argv) {
    char buf[2048];
    char * p = buf, * last = buf;
    char * args_buf[128];
    char ** args = args_buf;
    for (int i = 1; i < argc; ++i) {
        * args ++ = argv[i];
    }
    char ** pa = args;
    while (read(0, p, 1) != 0) {
        if (* p == ' ' || * p == '\n') {
            * p = '\0';
        }
    }
}