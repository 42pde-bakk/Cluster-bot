//
// Created by Peer De bakker on 3/16/22.
//

#include "Minimax.hpp"
#include <cmath>
#include <climits>


Minimax::Minimax() : max_depth(5) {
}

Minimax::Minimax(int maxdepth) : max_depth(maxdepth) {
}

Gamestate *Minimax::minimax(Gamestate *gs, int depth, bool maximizing_player) {
	Gamestate	*best_state = nullptr;
	float		best_value;
	Gamestate	*res;

	gs->spawn_new_children();
	if (depth == this->max_depth || gs->children.empty())
		return (gs);

	if (maximizing_player) {
		best_value = std::numeric_limits<float>::min();
		for (auto& child : gs->children) {
			res = this->minimax(child, depth + 1, false);
			if (res->h > best_value) {
				best_value = res->h;
				best_state = res;
			}
		}
	} else {
		best_value = std::numeric_limits<float>::max();
		for (auto& child : gs->children) {
			res = this->minimax(child, depth + 1, true);
			if (res->h < best_value) {
				best_value = res->h;
				best_state = res;
			}
		}
	}
	assert(best_state);
	return (best_state);
}

Gamestate *Minimax::alphabeta(Gamestate *gs, int depth, bool maximizing_player, float alpha, float beta) {
	Gamestate	*best_state = nullptr;
	float		best_value;
	Gamestate	*res;

	gs->spawn_new_children();
	if (depth == this->max_depth || gs->children.empty())
		return (gs);

	if (maximizing_player) {
		best_value = std::numeric_limits<float>::min();
		for (auto& child : gs->children) {
			res = this->alphabeta(child, depth + 1, false, alpha, beta);
			if (res->h > best_value) {
				best_value = res->h;
				best_state = res;
			}
			if (best_value >= beta)
				break ; // Beta cutoff
			alpha = std::max(alpha, res->h);
		}
	} else {
		best_value = std::numeric_limits<float>::max();
		for (auto& child : gs->children) {
			res = this->alphabeta(child, depth + 1, true, alpha, beta);
			if (res->h < best_value) {
				best_value = res->h;
				best_state = res;
			}
			if (best_value <= alpha)
				break ; // Alpha cutoff
			beta = std::min(beta, res->h);
		}
	}
	assert(best_state);
	return (best_state);
}

