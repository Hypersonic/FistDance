#include "parser.h"

// parse skel file fn and creates skel
void skel_parser::parse(char *fn, Skeleton &skel) {
	int fd = open(fn, O_RDONLY);
	char **token_buffer = new char *[8];
	for (int i = 0; i < 8; i++) token_buffer[i] = new char [16];
	char *command;

	int cur_node = -1;

	// scan each line
	while (skel_parser::split(fd, token_buffer)) {
		if (strcmp(token_buffer[0], "node") == 0) {
			if (cur_node < 0) {
				printf("adding first node\n");
				SkeletonNode &node = skel.nodes[skel.n_nodes++];
				node.parent = -1; // indicate no parent
				cur_node = 0;
			} else {
				printf("adding another node\n");
				SkeletonNode &node = skel.nodes[cur_node];
				int new_node = skel.n_nodes++;

				node.push(new_node);
				skel.nodes[new_node].parent = cur_node;
				cur_node = new_node;
			}
		} else if (strcmp(token_buffer[0], "trans") == 0) {
			printf("translating\n");
			if (cur_node < 0) {
				printf("error: tried to translate before making a node\n");
				continue;
			}

			// set node translate
			SkeletonNode &node = skel.nodes[cur_node];
			sscanf(token_buffer[1], "%f", &node.transform.trans.x);
			sscanf(token_buffer[2], "%f", &node.transform.trans.y);
		} else if (strcmp(token_buffer[0], "rot") == 0) {
			printf("rotating\n");
			if (cur_node < 0) {
				printf("error: tried to rotate before making a node\n");
				continue;
			}

			// set node translate
			SkeletonNode &node = skel.nodes[cur_node];
			sscanf(token_buffer[1], "%d", &node.transform.rot);
		} else if (strcmp(token_buffer[0], "name") == 0) {
			printf("naming\n");
			if (cur_node < 0) {
				printf("error: tried to name before making a node\n");
				continue;
			}

			// TODO add node naming
		} else if (strcmp(token_buffer[0], "ascend") == 0) {
			printf("ascending\n");
			if (cur_node < 0) {
				printf("error: tried to ascend before making a node\n");
				continue;
			} else if (cur_node == 0) {
				printf("error: tried to ascend while at top node\n");
				continue;
			}

			cur_node = skel.nodes[cur_node].parent;
		}
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
