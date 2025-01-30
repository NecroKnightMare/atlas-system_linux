#include <stdio.h>
#include <stdlib.h>
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
    int hidden = 0;
    int almost_all = 0;
    int long_format = 0;
    int dir_count = 0;
    int file_count = 0;
    char **files = malloc(argc * sizeof(char *));
    char **dirs = malloc(argc * sizeof(char *));

    for (int i = 1; i < argc; i++)
    {
        if (custom_strcmp(argv[i], "-a") == 0)
        {
            hidden = 1;
        }
        else if (custom_strcmp(argv[i], "-A") == 0)
        {
            almost_all = 1;
        }
        else if (custom_strcmp(argv[i], "-l") == 0)
        {
            long_format = 1;
        }
        else
        {
            if (lstat(argv[i], &sb) == 0)
            {
                if (S_ISDIR(sb.st_mode))
                {
                    dirs[dir_count++] = (char *)argv[i];
                }
                else
                {
                    files[file_count++] = (char *)argv[i];
                }
            }
            else
            {
                perror(argv[i]);
            }
        }
    }

    // Handling single directory case
    if (dir_count == 1 && file_count == 0)
    {
        print_directory_contents(dirs[0], hidden, almost_all, 0, 1, long_format);
    }
    else
    {
        // Handling multiple directories or files
        for (int i = 0; i < file_count; i++)
        {
            print_file_info(files[i]);
        }

        for (int i = 0; i < dir_count; i++)
        {
            if (argc > 2)
            {
                printf("%s:\n", dirs[i]);
            }
            print_directory_contents(dirs[i], hidden, almost_all, dir_count > 1, 0, long_format);
            if (dir_count > 1 && i < dir_count - 1)
            {
                printf("\n");
            }
        }
    }

    free(files);
    free(dirs);
    return 0;
}
