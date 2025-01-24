#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>
#include "hls.h"

int main(int argc, const char *argv[]) {
    struct stat sb;

    if (argc == 1) {
        print_directory_contents(".");
    } else {
        for (int i = 1; i < argc; i++) {
            if (lstat(argv[i], &sb) == 0) {
                if (S_ISDIR(sb.st_mode)) {
                    if (argc > 2) {
                        //printf("%s:\n", argv[i]);
                    }
                    print_directory_contents(argv[i]);
                } else if (S_ISREG(sb.st_mode)) {
                    fprintf(stderr, "%s: %s: Not a directory\n",  argv[0], argv[i]);
                }
            } else {
                perror(argv[i]);
            }
        }
    }
    return 0;
}

void print_directory_contents(const char *directory) {
    DIR *dir;

    if (open_directory(directory, &dir) == 0){
        read_directory_entries(dir);
        closedir(dir);
    }
}

int open_directory(const char *directory, DIR **dir) {
    *dir = opendir(directory);
    if (*dir == NULL) {
        perror("opendir");
        return -1;
    }
    return 0;
}

void read_directory_entries(DIR *dir) {
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_name[0] != '.') {
            printf("%s ", entry->d_name);
        }
    }
    printf("\n");
}