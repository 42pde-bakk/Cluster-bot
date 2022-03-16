//
// Created by Peer De bakker on 3/14/22.
//

#include <cstdio>
#include <string>

void read_action(char *action, int *pos, int *value)
{
	scanf("%255s", action);
	dprintf(2, "action = '%s' ", action);
	if (strcmp(action, "rotate") == 0) {
		scanf("%d", value);
		dprintf(2, "value = %d\n", *value);
	} else if (strcmp(action, "drop") == 0) {
		scanf("%d %d", pos, value);
		dprintf(2, "pos=%d, value=%d\n", *pos, *value);
	} else
		dprintf(2, "NO NOTHING\n");
}

int read_gravity()
{
	int gravity;
	printf("fetch gravity\n");
	scanf(" gravity %d", &gravity);
	dprintf(2, "gravity = %d\n", gravity);
	return gravity;
}
