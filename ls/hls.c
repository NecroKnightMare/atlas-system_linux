#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include "hls.h"

void print_err(const char *program, const char *path, const char *error_mess) {
    fprintf(stderr, "%s: cannot access '%s': %s\n", program, path, error_mess);
}

int main(int argc, const char *argv[]) {
    if (argc == 1) {
        print_directory_contents(".");
    } else {
        for (int i = 1; i < argc; i++) {
            if_path(argv[i], argv[0]);
        }
    }
    return 0;
}
