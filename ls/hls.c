#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
/**
* Description: program to show contents of hls without hidden files
*/

/** 
* main: lists contents in hls dir
* 
* ls program to list contents of curr
* dir without listing hidden files
*
* Return: 0 if opened, 1 if not
**/

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