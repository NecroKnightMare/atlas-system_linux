#include <dirent.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

/**
* main- pass filename arguments to program
* 
* ls program to list contents of curr
* dir without listing hidden files
*
* Return: 0 if opened, 1 if not
**/

void _hls (const char *argv[])
{

    
}
int main(int argc, const char *argv[])
{
    DIR *dir;
    struct dirent *entry;
    struct stat sb;

    if (argc == 1) {
        dir = opendir(".");
        if (dir == NULL) {
            perror("opendir");
            exit(1);
        }
        /* Read directory entries  added cond for hidden files to not show*/
        while ((entry = readdir(dir)) != NULL)
        {
            if (entry->d_name[0] != '.') {
                printf("%s  ", entry->d_name);
                }
            }
            printf("\n");
            /* Close the directory */
            closedir(dir);
        } else {
        for (int i = 1; i < argc; i++) {
            if (lstat(argv[i], &sb) == 0 && S_ISDIR(sb.st_mode)) {
                dir = opendir(argv[0]);
                if (dir == NULL) {
                    fprintf(stderr, "%s ", argv[0]);
                    perror(argv[i]);
                    continue;
                }
                while ((entry = readdir(dir)) != NULL) {
                    if (entry->d_name[0] != '.') {
                        printf("%s ", entry->d_name);
                    }
                }
                printf("\n");
                /* Close the directory */
                closedir(dir);
            } else {
                sprintf(stderr, "%s: %s: Not a directory\n", argv[0], argv[i]);
            }
        }
    }
    return 0;
}