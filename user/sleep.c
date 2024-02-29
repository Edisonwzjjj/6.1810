//
// Created by ZIJUN WANG on 6/2/2024.
//
#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fcntl.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{

    if(argc != 2){
        fprintf(2, "Usage: sleep seconds\n");
        exit(1);
    }

    int sec = atoi(argv[1]);
    sleep(sec);

    exit(0);
}

