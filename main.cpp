#include <iostream>
#include "Solution.class.hpp"

int main( int argc, char *argv[] ) {

	Solution	obj("5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0");

	obj.parse_line();

	return ( 0 );
}
