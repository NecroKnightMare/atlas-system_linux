#include "hls.h"
#include <stdio.h>
#include <sys/stat.h>
#include <errno.h>



void if_path(const char *path, const char *program, int hidden, int almost_all, int print_dir_name, int long_format)
{
    struct stat sb;

    if (lstat(path, &sb) == 0)
    {
        if (S_ISDIR(sb.st_mode))
        {
            print_directory_contents(path, hidden, almost_all, print_dir_name, 1, long_format);
        }
        else if (S_ISREG(sb.st_mode))
        {
            if (hidden || path[0] != '.')
            {
                if (long_format)
                {
                    print_file_info(path);
                }
                else
                {
                    printf("%s\n", path);
                }
            }
        }
        else
        {
            print_err(program, path);
        }
    }
    else
    {
        print_err(program, path);
    }
}
// Ariels code
// #include <stdio.h>
// #include <sys/stat.h>
// #include <errno.h>
// #include <string.h>
// #include "hls.h"

// void if_path(const char *path, const char *program) {
//     struct stat sb;
//     if (lstat(path, &sb) == 0) {
//         if (S_ISDIR(sb.st_mode)) {
//             // this prints dir name 
//             // printf("%s\n", path);
//             print_directory_contents(path, 0);
//         } else if (S_ISREG(sb.st_mode)) {
//             printf("%s\n", path);
//         } else {
//             print_err(program, path);
//         }
//     } else {
//         print_err(program, path);
//     }
// }