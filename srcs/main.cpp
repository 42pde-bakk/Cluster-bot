#include <cstdio>
#include <cstdlib>
#include "Game.hpp"
#include "commands.hpp"
#include "Minimax.hpp"

int next(int max);

void	execute_move(Gamestate* gs, Game& game) {
//	dprintf(2, "what I think the situation is:\n");
//	std::cerr << *game.root;
	while (gs->parent != game.root)
		gs = gs->parent;
	dprintf(2, "gravity = %d\n", game.root->gravity);
	dprintf(2, "Action: %d %d %d\n", gs->action.command, gs->action.col, gs->action.honkychonky_colour);
	if (gs->action.command == DROP) {
		printf("drop %d %d\n", gs->action.col, gs->action.honkychonky_colour);
		dprintf(2, "BOT: drop %d %d\n", gs->action.col, gs->action.honkychonky_colour);
	}
	else if (gs->action.command == ROTATE) {
		printf("rotate %d\n", gs->action.col);
		dprintf(2, "BOT: rotate %d\n", gs->action.col);
	} else {
		printf("WAIT\n");
		dprintf(2, "BOT: WAIT\n");
	}
	game.root->children.clear();
	for (auto & all_gamestate : all_gamestates) {
		delete all_gamestate;
	}
	all_gamestates.clear();
}

int main()
{
	int pos, value;
	int turn = 0;
	char action[256];
	Game game;

	g_game = &game;
	Minimax minimax(1);
	if (game.id == 1) {
		read_action(action, &pos, &value);
	}
	while (true) {
		game.check_inventory();
		game.root->fetch_chips(); // resets the board and fills it in
		game.root->get_gravity();
		game.root->fetch_cells();

		Gamestate* gs = minimax.minimax(game.root, 0, game.id);
		assert(gs);
		execute_move(gs, game);
		dprintf(2, "DONE WITH EXECUTION!\n");

//		if (turn > 0)
//			return (1); // fuck all this
//		game.root->spawn_children_first(game.id);
//		if (next(3) == 0 && b != -1 && false) {
//			value = next(5);
//			int grav = read_gravity();
//			printf("rotate %d\n", value >= grav ? value + 1 : value);
//			dprintf(2, "BOT: rotate %d, value=%d, grav=%d\n", value >= grav ? value + 1 : value, value, grav);
//		} else {
//			while (true) {
//				pos = next(game.grid_size * 2 - 1) - game.grid_size + 1;
//				compute_pos(pos, game.grid_size, read_gravity(), &q, &r, &s);
//				dprintf(2, "pos = %d, q,r,s=%d,%d,%d\n", pos, q, r, s);
//				if (read_emptiness(q, r, s)) {
//					printf("drop %d %d\n", pos, game.);
//					dprintf(2, "BOT: drop %d %d\n", pos, a);
//					break;
//				}
//			}
//		}
		game.root->children.clear();
		read_action(action, &pos, &value);
		turn++;
	}
	return EXIT_SUCCESS;
}
