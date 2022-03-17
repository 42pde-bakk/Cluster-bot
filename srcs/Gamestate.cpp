//
// Created by Peer De bakker on 3/14/22.
//

#include "Gamestate.hpp"
#include "OffsetCoordinates.hpp"
#include "Game.hpp"

unsigned int g_id = 0;

Gamestate::Gamestate(const int T) : size(T) {
	int n = T * 2 - 1;
	for (int i = 0; i < n; i++) {
		vec.emplace_back(n, 0);
	}
	id = g_id++;
}

Gamestate::Gamestate(const Gamestate &x) : size(x.size) {
	*this = x;
	this->id = g_id++;
}

Gamestate& Gamestate::operator=(const Gamestate &x) {
	if (this != &x) {
		vec = x.vec;
		players[0] = x.players[0];
		players[1] = x.players[1];
		gravity = x.gravity;
	}
	return (*this);
}

Gamestate::~Gamestate() {
	for (auto & i : vec) {
		i.clear();
	}
	vec.clear();
	children.clear();
}

int Gamestate::get_gravity() {
	printf("fetch gravity\n");
	scanf(" gravity %d", &gravity);
	dprintf(2, "gravity = %d\n", gravity);
	return (gravity);
}

const OffsetCoordinates directions[6] = {
		OffsetCoordinates(0, -1), // 0 aka Up
		OffsetCoordinates(1, -1), // 1 aka Up-Right
		OffsetCoordinates(1, 0), // 2 aka Down-Right
		OffsetCoordinates(0, 1), // 3 aka Down
		OffsetCoordinates(-1, 1), // 4 aka Down-Left
		OffsetCoordinates(-1, 0) // 5 aka Up-Left
};

int	direction_add(int dir, int add) {
	int ret = dir + add;
	if (ret < 0)
		return (6 + ret);
	if (ret >= 6)
		return (ret % 6);
	return (ret);
}

OffsetCoordinates get_sideways(const OffsetCoordinates& start, int distance, int grav) {
	int new_dir = direction_add(grav, (distance > 0) ? - 1 : 1);
	const OffsetCoordinates& dir = directions[new_dir];
	return start + dir * abs(distance);
}

const OffsetCoordinates& tops(int size, int idx) {
	static const int _size = size - 1;
	static const int _size2 = 2 * _size;
	static const OffsetCoordinates _tops[6] = {
		OffsetCoordinates(_size, _size2),
		OffsetCoordinates(0, _size2),
		OffsetCoordinates(0, _size),
		OffsetCoordinates(_size, 0),
		OffsetCoordinates(_size2, 0),
		OffsetCoordinates(_size2, _size)
	};
	return _tops[idx];
}

bool Gamestate::drop_tile(int column, int honkychonky, OffsetCoordinates *result) {
	assert(column >= 0 && column <= (this->size - 1) * 2);
	std::cerr << "Child thinks the situation is as follows:\n" << *this;
	int distance = (this->size - 1 - column);
	const int move_dir = direction_add(gravity, (distance > 0) ? 1 : -1);
	dprintf(2, "distance = %d, move_dir = %d, col = %d\n", distance, move_dir, column);
	distance = abs(distance);

	dprintf(2, "size=%d, grav=%d\n", size, gravity);
	std::cerr << "tops: " << tops(size, gravity);
	dprintf(2, "move_dir = %d\n", move_dir);
	std::cerr << "directions[" << move_dir << "] = " << directions[move_dir] << '\n';
	OffsetCoordinates droptile = tops(size, gravity) + directions[move_dir] * distance;
	std::cerr << "droptile: " << droptile << '\n';
//	assert(droptile.col >= 0 && droptile.row >= 0 && droptile.col < 7 && droptile.row < 7);
	dprintf(2, "indexing vec at vec[%d][%d]\n", droptile.row, droptile.col);
	dprintf(2, "at that location, we have tilevalue %d\n", this->vec[droptile.row][droptile.col]);
	if (this->vec[droptile.row][droptile.col] != -1)
		return (false);
	OffsetCoordinates new_droptile;
	while (true) {
		new_droptile = droptile + directions[gravity];
//		dprintf(2, "new_droptile: col=%d, row=%d\n", new_droptile.col, new_droptile.row);
		if (!new_droptile.isvalidpos() || vec[new_droptile.row][new_droptile.col] != -1)
			break;
		droptile = new_droptile;
	}
	*result = droptile;
	dprintf(2, "dropping %d at vec[%d][%d]\n", honkychonky, new_droptile.col, new_droptile.row);
	this->vec[droptile.row][droptile.col] = honkychonky;
	return (true);
}

void Gamestate::save_chip(Cube& c) {
	if (c._val >= 0)
		c._val += 10;
	OffsetCoordinates o = c.to_oddq();
	vec[o.row][o.col] = c._val;
}

void Gamestate::fetch_chips() {
	int count;

	printf("fetch chips\n");
	scanf(" cell_count %d", &count);
	dprintf(2, "chip_count = %d\n", count);
	for (int i = 0; i < count; i++) {
		Cube cube;
		scanf(" cell %d %d %d %d", &cube._q, &cube._r, &cube._s, &cube._val);
//		std::cerr << cube;
		save_chip(cube);
	}
}

void Gamestate::fetch_cells() {
	int count;

	printf("fetch cells\n");
	scanf(" cell_count %d", &count);
	dprintf(2, "cell_count = %d\n", count);
	for (int i = 0; i < count; i++) {
		Cube cube;
		scanf(" cell %d %d %d %d", &cube._q, &cube._r, &cube._s, &cube._val);
//		std::cerr << cube;
		save_chip(cube);
	}
}

void Gamestate::spawn_new_children_drops(int chip_nb, int player_id) {
	if (chip_nb < 0)
		return;
	Chip	chip = this->get_player(player_id).get_chip(chip_nb);
//	Chip*	chip = &this->players[player_id].chips[chip_nb];
	OffsetCoordinates	drop_coords;

	if (chip.amount <= 0)
		return;
	int maxval = (this->size - 1) * 2 + 1;
	for (int column = 0; column < maxval; column++) {
		auto	*child = new Gamestate(*this);
		child->parent = this;
//		dprintf(2, "lets drop, col=%d, colour = %d\n", column, chip.colour + 10);
//		child->parent = std::shared_ptr<Gamestate>(this);
		if (!child->drop_tile(column, chip.colour + 10, &drop_coords)) {
			delete child;
			continue;
		}
		dprintf(2, "drop was succesful\n");
		all_gamestates.emplace_back(child);
		child->action = Action(DROP, column - this->size + 1, chip.colour);
		child->get_player(player_id).remove_chip(chip_nb);
//		child->players[player_id].chips[chip_nb].amount--;
		dprintf(2, "PLACING chip: nb=%d, idx=%d, in column %d\n", chip.colour, chip_nb, column - this->size + 1);
		child->update_h(drop_coords, chip.colour + 10);

		children.emplace_back(child);
	}
}

void Gamestate::spawn_new_children_rotations(int player_id) {
	for (int i = 1; i < 6; i++) {
		// create new object
		auto	*child = new Gamestate(*this);
		child->parent = this;
//		child->parent = std::shared_ptr<Gamestate>(this);
		// apply rotation
		child->get_player(player_id).remove_chip(0);
		child->get_player(player_id).remove_chip(1);
		// add to children
		children.emplace_back(child);
	}
}

void Gamestate::spawn_children(int player_id) {
	this->children.clear();
	spawn_new_children_drops(0, player_id);
	spawn_new_children_drops(1, player_id);
}

void Gamestate::spawn_children_first(int player_id) {
	Inventory& inv = g_game->my_inventory;
	std::cerr << "in spawn_children\n";
	this->children.clear();
	spawn_new_children_drops(inv.a, player_id);
//	if (inv.a != inv.b)
//		spawn_new_children_drops(inv.b, player_id);
	// maybe only do rotations in this turn?
//		spawn_new_children_rotations(player_id);

	std::cerr << "Spawned " << children.size() << " children!\n";
}


void Gamestate::set_h() {
	this->h = 0;
	for (size_t i = 0; i < vec.size(); i++) {
		for (size_t j = 0; j < vec[i].size(); j++) {
			this->update_h({(int)i, (int)j}, vec[i][j]);
		}
	}
}

void Gamestate::update_h(const OffsetCoordinates &o, int tile_value) {
	int delta = (tile_value <= 11) ? -1 : 1; // -1 for player 0, 1 for player 1
	for (const auto & direction : directions) {
		OffsetCoordinates check = o + direction;
		if (check.isvalidpos() && vec[check.col][check.row] == tile_value)
			this->h += static_cast<float>(delta);
	}
	std::cerr << "h now is " << h << '\n';
}

std::ostream &operator<<(std::ostream &o, const Gamestate &x) {
	for (const auto & i : x.vec) {
		for (int j : i) {
			o << j << ' ';
		}
		o << '\n';
	}
	return (o);
}
