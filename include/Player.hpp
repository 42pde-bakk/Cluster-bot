//
// Created by Peer De bakker on 3/14/22.
//

#ifndef CLUSTERBOT_PLAYER_HPP
#define CLUSTERBOT_PLAYER_HPP

#include <array>

class Player {
	int _id{};
	std::array<int, 2>	colours{};
	int _amount{};

public:

	Player& operator=(const Player& x) {
//		dprintf(2, "in player operator=, %p %p\n", (void *)this, (void*)&x);
		if (this != &x) {
			_id = x._id;
			colours = x.colours;
			_amount = x._amount;
			_isme = x._isme;
		}
		return (*this);
	}
	bool	_isme{};
	int remove_chip() {
		--_amount;
		return (0);
	}
	int get_chip(int idx) {
		assert(idx >= 0 && idx < 2);
		return (colours[idx]);
	}
	void set_chips(int col1, int col2, int amount) {
		colours[0] = col1;
		colours[1] = col2;
		this->_amount = amount;
	}

	int	get_amount_left() const {
		return (this->_amount);
	}

	int		get_id() { return (this->_id); }

};

#endif //CLUSTERBOT_PLAYER_HPP
