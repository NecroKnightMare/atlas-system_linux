#include <stdio.h>
#include <dirent.h>
#include "hls.c"

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