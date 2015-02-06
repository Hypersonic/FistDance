#include "parser.h"

// parse skel file fn and creates skel
void skel_parse(char *fn, Skeleton &skel) {
	FILE *fp = fopen(fn, "r");
	char **token_buffer = new char *[8];
	for (int i = 0; i < 8; i++) token_buffer[i] = new char [16];
	char *command;

	int cur_node = -1;

	// scan each line
	while (parse_split(fp, token_buffer)) {
		if (strcmp(token_buffer[0], "node") == 0) {
			if (cur_node < 0) {
				SkeletonNode &node = skel.nodes[skel.n_nodes++];
				node.parent = -1; // indicate no parent
				cur_node = 0;
			} else {
				SkeletonNode &node = skel.nodes[cur_node];
				int new_node = skel.n_nodes++;

				node.push(new_node);
				skel.nodes[new_node].parent = cur_node;
				cur_node = new_node;
			}
		} else if (strcmp(token_buffer[0], "trans") == 0) {
			if (cur_node < 0) {
				printf("error: tried to translate before making a node\n");
				continue;
			}

			// set node translate
			SkeletonNode &node = skel.nodes[cur_node];
			node.transform.trans.x = strtod(token_buffer[1], NULL);
			node.transform.trans.y = strtod(token_buffer[2], NULL);
		} else if (strcmp(token_buffer[0], "rot") == 0) {
			if (cur_node < 0) {
				printf("error: tried to rotate before making a node\n");
				continue;
			}

			// set node translate
			SkeletonNode &node = skel.nodes[cur_node];
			sscanf(token_buffer[1], "%d", &node.transform.rot);
		} else if (strcmp(token_buffer[0], "name") == 0) {
			if (cur_node < 0) {
				printf("error: tried to name before making a node\n");
				continue;
			}

			// TODO add node naming
		} else if (strcmp(token_buffer[0], "ascend") == 0) {
			if (cur_node < 0) {
				printf("error: tried to ascend before making a node\n");
				continue;
			} else if (cur_node == 0) {
				printf("error: tried to ascend while at top node\n");
				continue;
			}

			cur_node = skel.nodes[cur_node].parent;
		} else if (strcmp(token_buffer[0], "rad") == 0) {
			if (cur_node < 0) {
				printf("error: tried to set rad before making a node\n");
				continue;
			}

			SkeletonNode &node = skel.nodes[cur_node];
			node.info.hittable = HTBX_HTBX | HTBX_HTPT;
			node.info.rad = strtod(token_buffer[1], NULL);
		}
	}
}
