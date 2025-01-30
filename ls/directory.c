#include "hls.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <limits.h>

int is_hidden_file(const char *filename)
{
    return (filename[0] == '.');
}

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
void print_directory_contents(const char *path, int hidden, int almost_all, int print_dir_name, int single_directory, int long_format)
{
    DIR *dir;
    struct dirent **namelist;
    int n;

    if ((dir = opendir(path)) == NULL)
    {
        perror("opendir");
        return;
    }

    n = scandir(path, &namelist, NULL, scan_sort);
    if (n < 0)
    {
        perror("scandir");
        closedir(dir);
        return;
    }

    if (print_dir_name)
    {
        printf("%s:\n", path);
    }

    for (int i = 0; i < n; i++)
    {
        struct dirent *entry = namelist[i];

        // Skip "." and ".." if the almost_all flag is set
        if (almost_all && (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0))
        {
            free(entry);
            continue;
        }

        // Skip hidden files if single_directory is true and the hidden flag is not set
        if (single_directory && !hidden && is_hidden_file(entry->d_name))
        {
            free(entry);
            continue;
        }

        if (long_format)
        {
            struct stat sb;
            char full_path[PATH_MAX];
            snprintf(full_path, PATH_MAX, "%s/%s", path, entry->d_name);

            if (lstat(full_path, &sb) == -1)
            {
                perror("lstat");
                free(entry);
                continue;
            }

            print_long_format(&sb, entry->d_name);
        }
        else
        {
            printf("%s\n", entry->d_name);
        }

        free(entry);
    }

    free(namelist);
    closedir(dir);
}

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