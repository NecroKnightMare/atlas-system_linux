#include "_getline.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

char *_getline(const int fd) {
	static char buffer[READ_SIZE];
	static size_t buff_length = 0;
	static size_t buff_position = 0;
	char *line = NULL;
	size_t line_lgth = 0;

	while (1) {
		if (buff_position >= buff_length) {
			buff_length = read(fd, buffer, READ_SIZE);
			buff_position = 0;
			if (buff_length == 0) {
				break;
			} else if (buff_length < 0) {
				return NULL;
			}
		}
		size_t start = buff_position;
		while (buff_position < buff_length && buffer[buff_position] != '\n') {
			buff_position++;
		}
	
		size_t piece = buff_position - start;
		char *new_line = (char *)realloc(line, line_lgth + piece + 1);
		if (!new_line) {
			free(line);
			return NULL;
		}
		line = new_line;
		memcpy(line + line_lgth, buffer + start, piece);
		line_lgth += piece;

		if (buff_position < buff_length && buffer[buff_position] == '\n') {
			buff_position++;
			break;
		}
	}
	if (line) {
		line[line_lgth] = '\0';
	}
	return line;
}
