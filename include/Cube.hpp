//
// Created by Peer De bakker on 3/14/22.
//

#ifndef CLUSTERBOT_CUBE_HPP
#define CLUSTERBOT_CUBE_HPP
#include <iostream>

class OffsetCoordinates;

class Cube {
	static int offset;
public:
	int _q, _r, _s, _val;
	Cube(int q, int r, int val = -1);
	Cube();
	OffsetCoordinates to_oddq() const;

	static int	set_offset(int size);

};
std::ostream&	operator<<(std::ostream& o, const Cube& c);


#endif //CLUSTERBOT_CUBE_HPP
