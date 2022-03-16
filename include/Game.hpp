//
// Created by Peer De bakker on 3/14/22.
//

#ifndef CLUSTERBOT_GAME_HPP
#define CLUSTERBOT_GAME_HPP

#include "Gamestate.hpp"
#include <cstdio>
#include <iostream>
#include <unistd.h>

struct Inventory {
	int a;
	int b;
};

class Game {
public:
	int colour_count{};
	int	chip_count{};
	int	grid_size{};
	int	win_length{};
	int	id{};
	float		timeout_value{};
	Gamestate	*root;
	Inventory	my_inventory;

	Game();
	void	read_action();

	void	check_inventory();

	friend class Gamestate;
};

extern Game *g_game;

#endif //CLUSTERBOT_GAME_HPP
