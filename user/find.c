#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"


void f(char * path, char * target) {
    char buf[512], * p;
    int fd;
    struct dirent dir;
    struct stat st;
    if ((fd = open(path, 0) < 0)) {
        fprintf(2, "find: cannot open %s\n", path);
        exit(1);
    }

    if (fstat(fd, &st) < 0) {
        fprintf(2, "find: cannot stat %s\n", path);
        exit(1);
    }

    switch (st.type) {
        case T_FILE:
            fprintf(2, "Usage: find dir file\n");
            exit(1);
        case T_DIR:
            if (strlen(path) + 1 + DIRSIZ + 1 > sizeof buf) {
                printf("find: path too long\n");
                break;
            }
            strcpy(buf, path);
            p = buf + strlen(buf);
            * p ++ = '/';

            while (read(fd, &dir, sizeof dir) == sizeof (dir)) {
                if (!dir.inum || !strcmp(dir.name, '.') || !strcmp(dir.name, "..")) {
                    continue;
                }
                memmove(p, dir.name, DIRSIZ);
                p[DIRSIZ] = 0;
                if (stat(buf, &st) < 0) {
                    printf("find: cannot stat %s\n", buf);
                    continue;
                }
                if (st.type == T_DIR) {
                    f(buf, target);
                } else if (st.type == T_FILE) {
                    if (!strcmp(dir.name, target)) {
                        printf("%s\n", buf);
                    }
                }
                break;
            }
    }
    close(fd);
}

int main() {
    if (argc != 3) {
        fprintf(2, "Usage: find dir file\n");
        exit(1);
    }

    char const *path = argv[1];
    char const *target = argv[2];
    find_helper(path, target);
    exit(0);
}