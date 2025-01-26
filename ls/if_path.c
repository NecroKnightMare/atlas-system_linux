#include <stdio.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include "hls.h"

void if_path(const char *path, const char *program) {
    struct stat sb;
    if (lstat(path, &sb) == 0) {
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