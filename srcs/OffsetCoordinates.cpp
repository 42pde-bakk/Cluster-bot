//
// Created by Peer De bakker on 3/15/22.
//

#include "OffsetCoordinates.hpp"
#include "Cube.hpp"

int OffsetCoordinates::offset = 1;
int OffsetCoordinates::offset2 = 1;

OffsetCoordinates::OffsetCoordinates(int col, int row) : col(col), row(row) {
}

OffsetCoordinates OffsetCoordinates::operator+(const OffsetCoordinates &x) const {
	return {col + x.col, row + x.row};
}

OffsetCoordinates OffsetCoordinates::operator*(int mult) const {
	return {col * mult, row * mult};
}

OffsetCoordinates &OffsetCoordinates::operator+=(const OffsetCoordinates &x) {
	col += x.col;
	row += x.row;
	return (*this);
}

bool OffsetCoordinates::isvalidpos() const {
	return (row >= 0 && row <= offset2 && col >= 0 && col <= offset2);
}

OffsetCoordinates::OffsetCoordinates(const OffsetCoordinates &x) {
	*this = x;
}

OffsetCoordinates &OffsetCoordinates::operator=(const OffsetCoordinates &x) {
	if (this != &x) {
		this->col = x.col;
		this->row = x.row;
	}
	return (*this);
}

int OffsetCoordinates::set_offset(int size) {
	OffsetCoordinates::offset = size - 1;
	OffsetCoordinates::offset2 = 2 * OffsetCoordinates::offset;
	return offset;
}

Cube OffsetCoordinates::to_cube() const {
	return {
		col - offset,
		row - offset,
	};
}

OffsetCoordinates::OffsetCoordinates() = default;

std::ostream &operator<<(std::ostream &o, const OffsetCoordinates &c) {
	o << "\t\tOffsetCoords:: col: " << c.col << ", row: " << c.row << std::endl;
	return (o);
}
