#include <stdio.h>
#include <limits.h>
#include <unistd.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include "hls.h"

void print_err(const char *program, const char *path) {
    fprintf(stderr, "%s: cannot access %s: \n", program, path);
    switch (errno) {
        case EACCES:
            fprintf(stderr, "\n");
            break;
        case ENOENT:
            fprintf(stderr, "\n");
            break;
        case ENOTDIR:
            fprintf(stderr, "\n");
            break;
        default:
            fprintf(stderr, "\n");
            break;
    }
}

int main(int argc, char *argv[]) {
    struct stat sb;
    int start = 1;
    int long_format;

    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-' && argv[i][1] == 'l' && argv[i][2] == '\0') {
            long_format = 1;
            start++;
        } else {
            break;
        }
    }

    if (start == argc) {
        if (lstat(".", &sb) == 0 && S_ISDIR(sb.st_mode)) {
            print_directory_contents(".", long_format);
        } else {
            print_err(argv[0], ".");
        }
    } else {
        for (int i = start; i < argc; i++) {
            if (lstat(argv[i], &sb) == 0) {
                if (argc == optind + 1) {
                    print_directory_contents(argv[i], long_format);
                } else {
                    if (S_ISDIR(sb.st_mode)) {
                        printf("%s:\n", argv[i]);
                    }
                    print_directory_contents(argv[i], long_format);
                    if (i < argc - 1) {
                        printf("\n");
                    }
                }
            } else {
                print_err(argv[0], argv[i]);
            }
        }
    }
    return 0;
}

//     if (argc == 1) {
//          
//     } else {
//         for (int i = 1; i < argc; i++) {
//             if (lstat(argv[i], &sb) == 0) {
//                 // Print the directory name only if there are multiple arguments
//                 // or if it is a directory
//                 if (argc > 2 ) {
//                     printf("%s:\n", argv[i]);
//                 }
//                 if_path(argv[i], argv[0]);
//                 if (argc > 2 && i < argc - 1) {
//                     printf("\n");
//                 }
//             } else {
//                 print_err(argv[0], argv[i]);
//             }
//         }
//     }
//     return 0;
// }
