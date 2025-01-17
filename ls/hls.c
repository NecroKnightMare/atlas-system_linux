#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
int main(void)
{
    DIR *dir;
    struct dirent *entry;
    /* Open the current directory */
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
    return (0);
}