#ifndef HLS_H
#define HLS_H

#include <dirent.h>
#include <sys/stat.h>
#include <limits.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

typedef struct longlistfmt
{
    char mode[16];
    nlink_t nlinks;
    const char *user;
    const char *group;
    off_t size;
    const char *modified;
    const char *entry_name;
} longlistfmt_t;

void print_directory_contents(const char *directory);
int open_directory(const char *directory, DIR **dir);
void read_directory_entries(DIR *dir, int option_one);
void print_err(const char *program, const char *path);
void if_path(const char *path, const char *program);
void print_long_format(struct stat *sb, const char *name);
const char *dirent_type_name(unsigned char d_type);
const char *path_join(const char *dirpath, const char *entry_name);
int mode_to_str(char *buf, mode_t mode);
int longlistfmt_init(longlistfmt_t *longlist, const char *entry_name, struct stat *statbuf);
void longlistfmt_print(longlistfmt_t *longlist);

#endif /* HLS_H */

// Ariels code
// #ifndef HLS_H
// #define HLS_H

// #include <dirent.h>
// #include <sys/stat.h>

// typedef struct {
//     char mode[11];       // File type and permissions
//     unsigned long nlinks; // Number of hard links
//     const char *user;    // User name of owner
//     const char *group;   // Group name of owner
//     unsigned long size;   // Size in bytes
//     const char *modified; // Last modification time
//     const char *entry_name; // Entry name (file or directory name)
// } longlistfmt_t;

// void print_directory_contents(const char *directory, int long_format);
// int open_directory(const char *directory, DIR **dir);
// void read_directory_entries(DIR *dir, const char *directory, int long_format);
// void print_err(const char *program, const char *path);
// void if_path(const char *path, const char *program);
// void longlistfmt_print(longlistfmt_t *longlist);
// int longlistfmt_init(longlistfmt_t *longlist,
// 		     const char *entry_name,
// 		     struct stat *statbuf);
// int mode_to_str(char *buf, mode_t mode);
// const char *path_join(const char *dirpath, const char *entry_name);
// const char *dirent_type_name(unsigned char d_type);


// #endif // HLS_H