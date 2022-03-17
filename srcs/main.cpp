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
		dprintf(2, "MYBOT: drop %d %d\n", gs->action.col, gs->action.honkychonky_colour);
		game.root->get_player(game.id).remove_chip();
	}
	else if (gs->action.command == ROTATE) {
		printf("rotate %d\n", gs->action.col);
		dprintf(2, "MYBOT: rotate %d\n", gs->action.col);
		game.root->get_player(game.id).remove_chip();
		game.root->get_player(game.id).remove_chip();
	} else {
		printf("WAIT\n");
		dprintf(2, "MYBOT: WAIT\n");
	}
	game.root->children.clear();
	for (auto & all_gamestate : all_gamestates) {
		delete all_gamestate;
	}
	all_gamestates.clear();
	dprintf(2, "still got %d tiles left\n", game.root->get_player(game.id).get_amount_left());
}

int main()
{
	int pos, value;
	char action[256];
	int turn = 0;
	Game game;

	g_game = &game;
	Minimax minimax(1);
	if (game.id == 1) {
//		read_action(action, &pos, &value);
		game.read_action(action, &pos, &value);
	}
	while (true) {
		game.check_inventory();
		game.root->fetch_cells();
		game.root->fetch_chips(); // resets the board and fills it in
		game.root->get_gravity();
		game.root->spawn_children_first(game.id);
//		assert(!game.root->children.empty());
		Gamestate* gs = game.root->children[0];
//		Gamestate* gs = minimax.minimax(game.root, 0, game.id);
		assert(gs);
//		assert(game.my_inventory.a != game.my_inventory.b && game.my_inventory.a != 0);
		execute_move(gs, game);
		dprintf(2, "DONE WITH EXECUTION!\n");
		usleep(500000);

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
		game.read_action(action, &pos, &value);
//		game.read_action();
		turn++;
	}
	return EXIT_SUCCESS;
}
