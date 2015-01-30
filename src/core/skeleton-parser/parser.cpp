#include "parser.h"

// parse skel file fn and creates skel
void skel_parser::parse(char *fn, Skeleton *skel) {
	int fd = open(fn, O_RDONLY);
	char **token_buffer = new char *[8];
	for (int i = 0; i < 8; i++) token_buffer[i] = new char [16];
	char *command;

	while (skel_parser::split(fd, token_buffer)) {
		for (int i = 0; i < 8; i++) {
			if (token_buffer[i][0]) {
				printf("%s ", token_buffer[i]);
			}
		}
		printf("\n");
	}
}

bool skel_parser::split(int fd, char **token_buffer) {
	// split line into tokens
	int token_index = 0;
	int token_char = 0;
	bool inWhitespace = false;

	// zero start of token_buffer
	for (int i = 0; i < 8; i++)
		token_buffer[i][0] = '\0';

	// trim starting whitespace
	char c;
	read(fd, &c, 1);
	for (; isspace(c) && c != '\n'; read(fd, &c, 1));
	if (c == '\0') return false;
	if (c == '\n') return true;

	// read and tokenize
	for (; c; read(fd, &c, 1)) {
		// end on comments and newlines
		if (!c || c == '#' || c == '\n') {
			break;
		}

		// parse for tokens
		if (!isspace(c)) {
			if (inWhitespace) {
				// found a new token; end the last token
				inWhitespace = false;
				token_buffer[token_index][token_char] = '\0';
				token_index++;
				token_char = 0;
			}
			token_buffer[token_index][token_char++] = c;
		} else
			inWhitespace = true;
	}
	token_buffer[token_index][token_char] = '\0';
	token_buffer[++token_index][0] = '\0';

	return true;
}
