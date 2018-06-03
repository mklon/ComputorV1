#include "Solution.class.hpp"

void	usage() {
	std::cout << "usage: ./computor \" equation \"" << std::endl;
	exit( 1 );
}

int		main( int argc, char *argv[] ) {
	if ( argc != 2 )
		usage();


	Solution	obj( argv[1] );

	obj.solve();

	return ( 0 );
}
