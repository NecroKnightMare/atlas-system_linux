#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include "hls.h"

int custom_strcmp(const char *str1, const char *str2)
{
    while (*str1 && (*str1 == *str2))
    {
        str1++;
        str2++;
    }
    return (*(unsigned char *)str1 - *(unsigned char *)str2);
}

int scan_sort(const struct dirent **a, const struct dirent **b)
{
    return custom_strcmp((*a)->d_name, (*b)->d_name);
}

// int quick_sort(const void *a, const void *b) {
//     const struct dirent *dir_a = *(const struct dirent **)a;
//     const struct dirent *dir_b = *(const struct dirent **)b;

//     // case insensitive
//     return custom_strcmp(dir_a->d_name, dir_b->d_name);
// }
/* Prints the contents of a directory. */
void print_directory_contents(const char *path, int hidden, int almost_all, int print_dir_name)
{
    DIR *dir;
    struct dirent *entry;
    struct dirent **sort_name;
    int n;

    if ((dir = opendir(path)) == NULL)
    {
        print_err("./hls_04", path);
        return;
    }

    n = scandir(path, &sort_name, NULL, scan_sort);
    if (n < 0)
    {
        perror("scandir");
        return;
    }
    if (print_dir_name)
    {
        printf("%s:\n", path);
    }

    for (int i = 0; i < n; i++)
    {
        entry = sort_name[i];
        // file 3 code
        // Skip hidden files if hidden flag is not set
        if ((!hidden && entry->d_name[0] == '.') || 
            (almost_all && (custom_strcmp(entry->d_name, ".") == 0 || custom_strcmp(entry->d_name, "..") == 0)))
        {
            free(entry);
            continue;
        }
            printf("%s\n", entry->d_name);
            free(entry);
        }
    free(sort_name);
    closedir(dir);
}

// file 3 code    // Skip '.' and '..' if almost_all flag is set
//         if (almost_all && (custom_strcmp(entry->d_name, ".") == 0 || custom_strcmp(entry->d_name, "..") == 0)) {
//             free(entry);
//             continue;
//         }

//         // Print the entry
//         printf("%s\n", entry->d_name);

//         free(entry);
//     }

//     free(sort_name);
//     closedir(dir);
// }

/* Opens a directory. */
int open_directory(const char *directory, DIR **dir)
{
	*dir = opendir(directory);
	if (*dir == NULL)
	{
		perror("./hls_03: cannot open directory");
		return -1;
	}
	return 0;
}

/* Reads and prints directory entries. */
void read_directory_entries(DIR *dir, int option_one)
{
	struct dirent *entry;

	while ((entry = readdir(dir)) != NULL)
	{
		/* Skip "." and ".." entries */
		if ((entry->d_name[0] == '.' && entry->d_name[1] == '\0') ||
			(entry->d_name[0] == '.' && entry->d_name[1] == '.' && entry->d_name[2] == '\0'))
		{
			continue;
		}

		/* Skip hidden files when -1 is used */
		if (option_one && entry->d_name[0] == '.' && entry->d_name[1] != '\0')
		{
			continue;
		}

		printf("%s ", entry->d_name); /* Print space-separated */
	}
	if (!option_one)
	{
		printf("\n"); /* Add newline if not -1 option */
	}
}