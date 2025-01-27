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

void print_err(const char *program, const char *path, const char *error_mess) {
    fprintf(stderr, "%s: cannot access %s: %s\n", program, path, error_mess);
}

int main(int argc, char * const argv[]) {
    struct stat sb;
    int opt;
    int long_format;

    while ((opt = getopt(argc, argv, "l")) != -1) {
        switch (opt) {
            case 'l':
                long_format = 1;
                break;
            default:
                fprintf(stderr, "%s \n", argv[0]);
                return 1;
        }
    }

    if (optind == argc) {
        if (lstat(".", &sb) == 0 && S_ISDIR(sb.st_mode)) {
            print_directory_contents(".", long_format);
        } else {
            print_err(argv[0], ".", strerror(errno));
        }
    } else {
        for (int i = optind; i < argc; i++) {
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
                print_err(argv[0], argv[i], strerror(errno));
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
