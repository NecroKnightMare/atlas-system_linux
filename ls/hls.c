#include <dirent.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

/**
* main- pass filename arguments to program
* 
* ls program to list contents of curr
* dir without listing hidden files
*
* Return: 0 if opened, 1 if not
**/

int main(int argc, char *argv[])
{
    DIR *dir;
    struct dirent *entry;

    if (argc == 1) {
        dir = opendir(".");
        if (dir == NULL) {
            perror("opendir");
            exit(1);
        }
        /* Read directory entries  added cond for hidden files to not show*/
        while ((entry = readdir(dir)) != NULL)
        {
            if (entry->d_name[1] != '.') {
            printf("%s  ", entry->d_name);
            }
        }
        printf("\n");
        /* Close the directory */
        closedir(dir);
        return (0);
        } else {
            for (int i = 1; i < argc; i++) {
                dir = opendir(argv[0]);
                if (dir == NULL) {
                    fprintf(stderr, "%s ", argv[i]);
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
            }
        }
    return 0;
}