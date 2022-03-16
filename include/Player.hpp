//
// Created by Peer De bakker on 3/14/22.
//

#ifndef CLUSTERBOT_PLAYER_HPP
#define CLUSTERBOT_PLAYER_HPP

#include <array>

struct Chip {
	int colour;
	int amount;
};

class Player {
	int _id;
	std::array<Chip, 2> chips;

public:
	bool	_isme;
	int	remove_chip(int idx) {
		assert(idx >= 0 && idx < 2);
		if (chips[idx].amount <= 0)
			return (1);
		chips[idx].amount--;
		return (0);
	}
	Chip&	get_chip(int idx) {
		assert(idx >= 0 && idx < 2);
		return (this->chips[idx]);
	}
	void	set_chip(int idx, int amount, int colour) {
		assert(idx >= 0 && idx < 2);
		this->chips[idx].amount = amount;
		this->chips[idx].colour = colour;
	}
	int		get_id() { return (this->_id); }

};

#endif //CLUSTERBOT_PLAYER_HPP
