//
// Created by Peer De bakker on 3/14/22.
//

#ifndef CLUSTERBOT_COMMANDS_HPP
#define CLUSTERBOT_COMMANDS_HPP
#include <cstring>

typedef enum cmd {
	INIT,
	COLOR,
	CHIPS,
	ROTATE,
	DROP,
	FETCH,
	CELL_COUNT,
	CELL,
	GRAVITY,
	WALL_COUNT,
	WALL,
	ERROR
}	e_cmd;

int read_gravity();





#endif //CLUSTERBOT_COMMANDS_HPP
