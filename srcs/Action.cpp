//
// Created by Peer De bakker on 3/16/22.
//

#include "Action.hpp"

Action::Action() {// : command(ERROR), col(-1), honkychonky_colour(-1) {}
	command = ERROR;
	col = -1;
	honkychonky_colour = -1;
}

Action::Action(e_cmd cmd, int column, int honkychonky_colour) : col(column), honkychonky_colour(honkychonky_colour), command(cmd) {}
