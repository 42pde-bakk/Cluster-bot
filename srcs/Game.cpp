//
// Created by Peer De bakker on 3/14/22.
//

#include "Game.hpp"

Game	*g_game = nullptr;

static unsigned long mix(unsigned long a, unsigned long b, unsigned long c) {
	a = (a - b - c) ^ (c >> 13);
	b = (b - c - a) ^ (a << 8);
	c = (c - a - b) ^ (b >> 13);
	a = (a - b - c) ^ (c >> 12);
	b = (b - c - a) ^ (a << 16);
	c = (c - a - b) ^ (b >> 5);
	a = (a - b - c) ^ (c >> 3);
	b = (b - c - a) ^ (a << 10);
	c = (c - a - b) ^ (b >> 15);
	return c;
}

int next(int max) {
	int res = (rand() / 256) % max;
	dprintf(2, "max=%d, res=%d\n", max, res);
	return (res);
}

Game::Game() : root(nullptr) {
	setbuf(stdout, nullptr);
	setbuf(stdin, nullptr);
	setbuf(stderr, nullptr);

	scanf(" init %d %d %d %d %f %d", &colour_count, &chip_count, &grid_size, &win_length, &timeout_value, &id);
	root = new Gamestate(grid_size);
	Cube::set_offset(grid_size);
	OffsetCoordinates::set_offset(grid_size);
	root->player_set_me(id);
//	players[id].is_me = true;
	dprintf(2, "color_count=%d, chip_count=%d, grid_size=%d, win_length=%d, timeout=%f, id=%d\n", colour_count, chip_count, grid_size, win_length, timeout_value, id);
	for (int i = 0; i < 2; i++) {
		root->get_player(i).set_chips(i * 2, i * 2 + 1, chip_count * 2);
	}

	srand(mix(clock(), time(nullptr), getpid()));
	int c = next(5);
	printf("color %d\n", c >= 2 ? c + 1 : c);
	dprintf(2, "c=%d, I apparently chose colour %d\n", c, c >= 2 ? c + 1 : c);
}

void Game::read_action(char *action, int *pos, int *value) {
	scanf("%255s", action);
	dprintf(2, "action = '%s'\n ", action);
	if (strcmp(action, "rotate") == 0) {
		scanf("%d", value);
		dprintf(2, "value = %d\n", *value);
		this->root->get_player(!id).remove_chip();
		this->root->get_player(!id).remove_chip();
	} else if (strcmp(action, "drop") == 0) {
		scanf("%d %d", pos, value);
		dprintf(2, "pos=%d, value=%d\n", *pos, *value);
		this->root->get_player(!id).remove_chip();
//		this->root->players[!id].chips[col_id].amount--;
	} else {
//		dprintf(2, "NO NOTHING\n");
	}
}

void Game::check_inventory() {
	scanf(" chips %d %d", &my_inventory.a, &my_inventory.b);
	dprintf(2, "FUCK ME chips: a=%d, b=%d\n", my_inventory.a, my_inventory.b);
}
