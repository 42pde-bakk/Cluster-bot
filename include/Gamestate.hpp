//
// Created by Peer De bakker on 3/14/22.
//

#ifndef CLUSTERBOT_GAMESTATE_HPP
#define CLUSTERBOT_GAMESTATE_HPP
#include <vector>
#include <iostream>
#include <array>
#include "Player.hpp"
#include "Cube.hpp"
#include "Action.hpp"
#include "OffsetCoordinates.hpp"

class Gamestate {
	std::array<Player, 2>	players;
public:
	unsigned int id{};
	int depth = 0;
	float scoreSum = 0.0f;
	float h{};
	std::vector<std::vector<int>>	vec;
	Gamestate	*parent;
	std::vector<Gamestate*>	children;
	int		gravity{};
	const int		size;
	Action			action{};

	Gamestate();
	void spawn_new_children_drops(int chip_idx, int p_id);
	void spawn_new_children_rotations(int player_id);

public:
	explicit Gamestate(int T);
	Gamestate(const Gamestate& x);
	Gamestate& operator=(const Gamestate& x);
	~Gamestate();

	void	fetch_chips();
	void	fetch_cells();
	int		get_gravity();
	void	save_chip(Cube& c);

	bool drop_tile(int column, int honkychonky, OffsetCoordinates *result);
	void spawn_children(int player_id);
	void spawn_children_first(int player_id);

	bool	operator==(const Gamestate& rhs) const { return (vec == rhs.vec); }
	bool	operator!=(const Gamestate& rhs) const { return (!(*this == rhs)); }
	bool	operator<(const Gamestate& rhs) const { return (h < rhs.h); }

	void	set_h();
	void	update_h(const OffsetCoordinates &o, int tile_value);

	Player&	get_player(int idx) {
		assert(idx >= 0 && idx < 2);
		return (this->players[idx]);
	}
	void	player_set_me(int idx) {
		assert(idx >= 0 && idx < 2);
		this->players[idx]._isme = true;
	}
};

class Game;
extern Game	*g_game;
extern std::vector<Gamestate*> all_gamestates;

std::ostream&	operator<<(std::ostream& o, const Gamestate& x);



#endif //CLUSTERBOT_GAMESTATE_HPP
