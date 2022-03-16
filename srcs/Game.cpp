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
		for (int c = 0; c < colour_count / 2; c++) {
			root->get_player(i).set_chip(c, chip_count, i * 2 + c);
//			root->players[i].chips[c].amount = chip_count;
//			root->players[i].chips[c].colour = i * 2 + c;
		}
	}

	srand(mix(clock(), time(nullptr), getpid()));
	int c = next(5);
	printf("color %d\n", c >= 2 ? c + 1 : c);
	dprintf(2, "c=%d, I apparently chose colour %d\n", c, c >= 2 ? c + 1 : c);
}

void Game::read_action() {
	char	action[256];
	int		pos, value;

	scanf("%255s", action);
	dprintf(2, "action = '%s' ", action);
	if (strcmp(action, "rotate") == 0) {
		scanf("%d", &value);
		dprintf(2, "value = %d\n", value);
		this->root->fetch_chips();
		this->root->set_h();
	} else if (strcmp(action, "drop") == 0) {
		scanf("%d %d", &pos, &value);
		dprintf(2, "pos=%d, value=%d\n", pos, value);
		int col_id = value - (!id * 2);
		this->root->get_player(!id).remove_chip(col_id);
//		this->root->players[!id].chips[col_id].amount--;
	} else
		dprintf(2, "NO NOTHING\n");
}

void Game::check_inventory() {
	scanf(" chips %d %d", &my_inventory.a, &my_inventory.b);
	dprintf(2, "chips: a=%d, b=%d\n", my_inventory.a, my_inventory.b);
}
