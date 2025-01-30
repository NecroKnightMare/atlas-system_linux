#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include "hls.h"

int scan_sort(const struct dirent **a, const struct dirent **b)
{
    return strcasecmp((*a)->d_name, (*b)->d_name);
}

int quick_sort(const void *a, const void *b) {
    const struct dirent *dir_a = *(const struct dirent **)a;
    const struct dirent *dir_b = *(const struct dirent **)b;

    // case insensitive
    return strcasecmp(dir_a->d_name, dir_b->d_name);
}
/* Prints the contents of a directory. */
void print_directory_contents(const char *path, int option_one, int hidden)
{
	DIR *dir;
	struct dirent *entry;
	struct dirent **sort_name;
	int n;

	if ((dir = opendir(path)) == NULL)
	{
		print_err("./hls_03", path);
		return;
	}
    n = scandir(path, &sort_name, NULL, scan_sort);
    if (n < 0) {
        perror("scandir");
        return;
    }

    for (int i = 0; i < n; i++)
    {
        entry = sort_name[i];

        if (!hidden && entry->d_name[0] == '.' && entry->d_name[1] != '\0')
        {
            free(entry);
            continue;
        }
        
        if (option_one || !hidden)
        {
            printf("%s\n", entry->d_name);
        } else
        {
            struct stat sb;
            const char *entry_path = path_join(path, entry->d_name);
            if (lstat(entry_path, &sb) == -1)
            {
                print_err("./hls_02", entry_path);
            }
            print_long_format(&sb, entry->d_name);
        }
        
        free(entry);
    }
    
    free(sort_name);
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

// Ariels code
// #include <stdio.h>
// #include <dirent.h>
// #include <string.h>
// #include "hls.h"

// // make sure to remember edge case like null values
// //  (e.g., sending null to a field that expects a string)
// // invalid values (e.g., sending "potato" to an integer field)
// //  empty strings entered when you expect a string
// // regex characters like (.*)
// //   etc when inputted into a search field that uses
// //       regex in the backend (are they escaped correctly)
// // 

// void print_directory_contents(const char *directory, int long_format) {
//     DIR *dir;

//     if (open_directory(directory, &dir) == 0){
//         read_directory_entries(dir, directory, long_format);
//         closedir(dir);
//     }
// }

// int open_directory(const char *directory, DIR **dir) {
//     *dir = opendir(directory);
//     if (*dir == NULL) {
//         perror(": cannot open directory test");
//         return -1;
//     }
//     return 0;
// }

// void read_directory_entries(DIR *dir, const char *directory, int long_format) {
//     (void)directory;
    
//     struct dirent *entry;
//     struct stat statbuf;
//     char path[PATH_MAX];

//     while ((entry = readdir(dir)) != NULL) {
//         if (entry->d_name[0] != '.') {
//             if (long_format) {
//                 snprintf(path, sizeof(path), "%s/%s", ".", entry->d_name);
//                 if (lstat(path, &statbuf) == 0) {
//                     // found in library
//                     longlistfmt_t longlist;
//                     if (longlistfmt_init(&longlist, entry->d_name, &statbuf) == 0) {
//                         longlistfmt_print(&longlist);
//                     }
//                 } else {
//                     // add error messge if needed
//                     perror("");
//                 }
//                 } else {
//                 printf("%s ", entry->d_name);
//                 }
//             }
//         }
//         if (!long_format){
//             printf("/n");
//     }
// }