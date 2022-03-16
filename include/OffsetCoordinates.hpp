//
// Created by Peer De bakker on 3/15/22.
//

#pragma once
#ifndef CLUSTERBOT_OFFSETCOORDINATES_HPP
#define CLUSTERBOT_OFFSETCOORDINATES_HPP

#include <iostream>

class Cube;

class OffsetCoordinates {
private:
	static int	offset;
	static int	offset2;
public:
	int col{};
	int row{};

	OffsetCoordinates();
	OffsetCoordinates(int col, int row);
	OffsetCoordinates(const OffsetCoordinates& x);
	OffsetCoordinates& operator=(const OffsetCoordinates& x);
	OffsetCoordinates operator+(const OffsetCoordinates& x) const;
	OffsetCoordinates operator*(int mult) const;
	OffsetCoordinates& operator+=(const OffsetCoordinates& x);

	bool isvalidpos() const;

	Cube	to_cube() const;
	static int	set_offset(int size);
};
std::ostream&	operator<<(std::ostream& o, const OffsetCoordinates& c);


#endif //CLUSTERBOT_OFFSETCOORDINATES_HPP
