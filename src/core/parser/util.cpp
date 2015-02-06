#include "util.h"

bool parse_split(FILE *fp, char **token_buffer) {
	// split line into tokens
	int token_index = 0;
	int token_char = 0;
	bool inWhitespace = false;

	// zero start of token_buffer
	for (int i = 0; i < 8; i++)
		token_buffer[i][0] = '\0';

	// trim starting whitespace
	char c;
	c = getc(fp);
	for (; isspace(c) && c != '\n'; c = getc(fp));
	if (c == EOF || c == '\0') {
		return false;
	}
	if (c == '\n') {
		return true;
	}

	// read and tokenize
	for (; c && c != '#' && c != '\n'; c = getc(fp)) {
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

	// ignore rest of commented line
	if (c == '#') while (c != '\n' && c != EOF) c = getc(fp);

	token_buffer[token_index][token_char] = '\0';
	token_buffer[++token_index][0] = '\0';

	return true;
}
