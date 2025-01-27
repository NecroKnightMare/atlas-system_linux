#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include "hls.h"

// make sure to remember edge case like null values
//  (e.g., sending null to a field that expects a string)
// invalid values (e.g., sending "potato" to an integer field)
//  empty strings entered when you expect a string
// regex characters like (.*)
//   etc when inputted into a search field that uses
//       regex in the backend (are they escaped correctly)
// 

void print_directory_contents(const char *directory, int long_format) {
    DIR *dir;

    if (open_directory(directory, &dir) == 0){
        read_directory_entries(dir, directory, long_format);
        closedir(dir);
    }
}

int open_directory(const char *directory, DIR **dir) {
    *dir = opendir(directory);
    if (*dir == NULL) {
        perror(": cannot open directory test");
        return -1;
    }
    return 0;
}

void read_directory_entries(DIR *dir, const char *directory, int long_format) {
    (void)directory;
    
    struct dirent *entry;
    struct stat statbuf;
    char path[PATH_MAX];

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_name[0] != '.') {
            if (long_format) {
                snprintf(path, sizeof(path), "%s/%s", ".", entry->d_name);
                if (lstat(path, &statbuf) == 0) {
                    // found in library
                    longlistfmt_t longlist;
                    if (longlistfmt_init(&longlist, entry->d_name, &statbuf) == 0) {
                        longlistfmt_print(&longlist);
                    }
                } else {
                    // add error messge if needed
                    perror("");
                }
                } else {
                printf("%s ", entry->d_name);
                }
            }
        }
        if (!long_format){
            printf("/n");
    }
}