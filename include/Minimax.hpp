//
// Created by Peer De bakker on 3/16/22.
//

#ifndef CLUSTERBOT_MINIMAX_HPP
#define CLUSTERBOT_MINIMAX_HPP

#include <bit>
//#include <bits/stdc++.h>
#include "Gamestate.hpp"

class Minimax {
public:
	int max_depth;

	Minimax();
	explicit Minimax(int maxdepth);

	Gamestate *minimax(Gamestate *gs, int depth, bool maximizing_player);
	Gamestate *alphabeta(Gamestate *gs, int depth, bool maximizing_player, float alpha, float beta);
};


int minimax(Gamestate *state, int depth, bool maximizing_player);



#endif //CLUSTERBOT_MINIMAX_HPP
