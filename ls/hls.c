#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include "hls.h"

void print_err(const char *program, const char *path, const char *error_mess) {
    fprintf(stderr, "%s: cannot access '%s': %s\n", program, path, error_mess);
}

void if_path(const char *path, const char *program) {
    struct stat sb;
    if (lstat(argv[i], &sb) == 0) {
        if (S_ISDIR(sb.st_mode)) {
            printf("%s\n", path);
            print_directory_contents(path);
        } else if (S_ISREG(sb.st_mode)) {
            printf("%s\n", path);
        } else {
            print_err(program, path, "Not a regular file or dir");
        }
    } else {
        print_err(program, path, strerror(errno));
    }
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
