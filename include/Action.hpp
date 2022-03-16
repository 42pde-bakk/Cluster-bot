//
// Created by Peer De bakker on 3/15/22.
//

#ifndef CLUSTERBOT_ACTION_HPP
#define CLUSTERBOT_ACTION_HPP
#include <iostream>
#include "commands.hpp"

class Action {
public:
	int		col{};
	int		honkychonky_colour{};
	e_cmd	command{};

	Action();
	Action(e_cmd cmd, int column, int honkychonky_colour = -1);

};

#endif //CLUSTERBOT_ACTION_HPP
