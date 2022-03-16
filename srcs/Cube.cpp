//
// Created by Peer De bakker on 3/14/22.
//

#include "Cube.hpp"
#include "OffsetCoordinates.hpp"

int Cube::offset = 1;

Cube::Cube(int q, int r, int val) : _q(q), _r(r), _s(-q - r), _val(val) {}

Cube::Cube() : _q(0), _r(0), _s(0), _val(0) {
}

int Cube::set_offset(int size) {
	Cube::offset = size - 1;
	return Cube::offset;
}

OffsetCoordinates Cube::to_oddq() const {
	return {
		_q + offset,
		_r + offset
	};
}

std::ostream &operator<<(std::ostream &o, const Cube &c) {
	o << "Cube::: Q: " << c._q << ", R: " << c._r << ", S: " << c._s << ", value: " << c._val << std::endl;
	return (o);
}
