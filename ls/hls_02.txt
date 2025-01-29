#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <limits.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include "hls.h"

static char PATH_BUF[PATH_MAX];
static char PERMS_ALPHAMAP[3] = {'r', 'w', 'x'};
static char FTYPE_ALPHAMAP[16] = {
	'?', 'p', 'c', '?', 'd', '?', 'b', '?', '-', '?', 'l', '?', 's', '?', '?',
	'?'};

const char *dirent_type_name(unsigned char d_type)
{
	switch (d_type)
	{
	case DT_BLK:
		return "block_device";
	case DT_CHR:
		return "character_device";
	case DT_DIR:
		return "directory";
	case DT_FIFO:
		return "named_pipe";
	case DT_LNK:
		return "symbolic_link";
	case DT_REG:
		return "file";
	case DT_SOCK:
		return "socket";
	default: /* DT_UNKNOWN */
		return "unknown";
	}
}

const char *path_join(const char *dirpath, const char *entry_name)
{
	char *dest = PATH_BUF;

	while (*dirpath)
	{
		*dest++ = *dirpath++;
	}

	*dest++ = '/';

	while (*entry_name)
	{
		*dest++ = *entry_name++;
	}

	*dest = '\0';

	return PATH_BUF;
}

int mode_to_str(char *buf, mode_t mode)
{
	mode_t pmask, i;

	*buf++ = FTYPE_ALPHAMAP[(mode & S_IFMT) >> 12];

	pmask = S_IRUSR;

	for (i = 0; i < 9; ++i, pmask >>= 1)
		*buf++ = (mode & pmask) ? PERMS_ALPHAMAP[i % 3] : '-';

	*buf = '\0';

	return (0);
}

int longlistfmt_init(longlistfmt_t *longlist, const char *entry_name,
					 struct stat *statbuf)
{
	struct passwd *pwd = NULL;
	struct group *group = NULL;

	mode_to_str(longlist->mode, statbuf->st_mode);
	longlist->nlinks = statbuf->st_nlink;

	pwd = getpwuid(statbuf->st_uid);
	group = getgrgid(statbuf->st_gid);

	if (!pwd || !group)
		return (-1);

	longlist->user = pwd->pw_name;
	longlist->group = group->gr_name;
	longlist->size = statbuf->st_size;
	longlist->modified = ctime(&(statbuf->st_mtime));
	longlist->entry_name = entry_name;
	return (0);
}

void longlistfmt_print(longlistfmt_t *longlist)
{
	printf("%s %lu %s %s %-4ld %.12s %s\n", longlist->mode, longlist->nlinks,
		   longlist->user, longlist->group, longlist->size,
		   longlist->modified + 4, longlist->entry_name);
}

void print_long_format(struct stat *sb, const char *name)
{
	longlistfmt_t longlist;

	if (longlistfmt_init(&longlist, name, sb) == 0)
	{
		/* Only print the entry name for now */
		printf("%s\n", longlist.entry_name);
	}
	else
	{
		perror("longlistfmt_init");
	}
}

void print_file_info(const char *path)
{
	struct stat sb;
	if (lstat(path, &sb) == -1)
	{
		print_err("./hls_02", path);
		return;
	}

	print_long_format(&sb, path);
}
void print_err(const char *program, const char *path)
{
	fprintf(stderr, "%s: cannot access %s: ", program, path);
	perror(NULL);
}

int main(int argc, const char *argv[])
{
	struct stat sb;
	int option_one = 0;
	int dir_count = 0;
	

	for (int i = 1; i < argc; i++)
	{
		if (argv[i][0] == '-' && argv[i][1] == '1' && argv[i][2] == '\0')
		{
			option_one = 1;
		}
		else
		{
			/* Skip invalid options (like -11111) */
			if (argv[i][0] == '-' && (argv[i][1] != '1' || argv[i][2] != '\0'))
			{
				print_err(argv[0], argv[i]);
				dir_count--;
			}

			/* Count ALL non-option arguments as directories */
			if (argv[i][0] != '-')
			{
				dir_count++;
			}
		}
	}

	if (argc == 1 || (argc == 2 && option_one))
    {
		print_directory_contents(".", option_one);
	}
    else
    {
		for (int i = 1; i < argc; i++)
        {
		    /* Skip -1 option */
            if (argv[i][0] == '-' && argv[i][1] == '1' && argv[i][2] == '\0')
            {
                continue;
            }

			if (lstat(argv[i], &sb) == 0)
			{
				if (S_ISDIR(sb.st_mode))
				{
					/* Print directory name if multiple directories */
					if (dir_count > 1)
					{
						printf("%s:\n", argv[i]);
					}
					print_directory_contents(argv[i], option_one);
					/* Print newline between directories */
					if (dir_count > 1 && i < argc - 1)
					{
						printf("\n");
					}
				}
				else
				{
						if (argv[i][0] != '.')
					{
						print_file_info(argv[i]);
					}
				}
			}
			else
			{
				print_err(argv[0], argv[i]);
			}
		}
	}
	return (0);
}

// task 2 script that keeps cakking fputs
// #include <stdio.h>
// #include <limits.h>
// #include <unistd.h>
// #include <dirent.h>
// #include <pwd.h>
// #include <grp.h>
// #include <sys/stat.h>
// #include <errno.h>
// #include <string.h>
// #include "hls.h"

// void print_err(const char *program, const char *path) {
//     fprintf(stderr, "%s: cannot access %s: \n", program, path);
//     switch (errno) {
//         case EACCES:
//             fprintf(stderr, "\n");
//             break;
//         case ENOENT:
//             fprintf(stderr, "\n");
//             break;
//         case ENOTDIR:
//             fprintf(stderr, "\n");
//             break;
//         default:
//             fprintf(stderr, "\n");
//             break;
//     }
// }

// int main(int argc, char *argv[]) {
//     struct stat sb;
//     int start = 1;
//     int long_format;

//     for (int i = 1; i < argc; i++) {
//         if (argv[i][0] == '-' && argv[i][1] == 'l' && argv[i][2] == '\0') {
//             long_format = 1;
//             start++;
//         } else {
//             break;
//         }
//     }

//     if (start == argc) {
//         if (lstat(".", &sb) == 0 && S_ISDIR(sb.st_mode)) {
//             print_directory_contents(".", long_format);
//         } else {
//             print_err(argv[0], ".");
//         }
//     } else {
//         for (int i = start; i < argc; i++) {
//             if (lstat(argv[i], &sb) == 0) {
//                 if (argc == optind + 1) {
//                     print_directory_contents(argv[i], long_format);
//                 } else {
//                     if (S_ISDIR(sb.st_mode)) {
//                         printf("%s:\n", argv[i]);
//                     }
//                     print_directory_contents(argv[i], long_format);
//                     if (i < argc - 1) {
//                         printf("\n");
//                     }
//                 }
//             } else {
//                 print_err(argv[0], argv[i]);
//             }
//         }
//     }
//     return 0;
// }

//  task 1 script
//     if (argc == 1) {
//          
//     } else {
//         for (int i = 1; i < argc; i++) {
//             if (lstat(argv[i], &sb) == 0) {
//                 // Print the directory name only if there are multiple arguments
//                 // or if it is a directory
//                 if (argc > 2 ) {
//                     printf("%s:\n", argv[i]);
//                 }
//                 if_path(argv[i], argv[0]);
//                 if (argc > 2 && i < argc - 1) {
//                     printf("\n");
//                 }
//             } else {
//                 print_err(argv[0], argv[i]);
//             }
//         }
//     }
//     return 0;
// }
