#include <dirent.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

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
    if (argc == 1) {
        char *path = '.';
        // DIR *dir;
        /* Open the current directory */
        dir = opendir(".");
        if (dir == NULL) {
            perror("opendir");
            exit(1);
        }
        /* Read directory entries  added cond for hidden files to not show*/
        struct dirent *entry;
        while ((entry = readdir(dir)) != NULL)
        {
            if (entry->d_name[0] != '.') {
            printf("%s  ", entry->d_name);
            }
        }
        printf("\n");
        /* Close the directory */
        closedir(dir);
        return (0);
        } else {
        fprintf(stderr, "%s: %s\n", argv[0], stderror(errno));
        return 1;
        } else {
            for (int i = 1; i < argc; i++) {
                dir = opendir(path);
                if (dir == NULL) {
                    perror("opendir");
                    exit(1);
                }
                /* Read directory entries  added cond for hidden files to not show*/
                struct dirent *entry;
                while ((entry = readdir(dir)) != NULL)
                {
                    if (entry->d_name[0] != '.') {
                        printf("%s  ", entry->d_name);
                    }
                }
                printf("\n");
                /* Close the directory */
                closedir(dir);
                return (0);
                } else {
                    fprintf(stderr, "%s: %s\n", argv[0], stderror(errno));
                    return 1;
                }
            }
    }