// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Solution.class.cpp                                 :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: oposhiva <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/06/02 13:05:16 by oposhiva          #+#    #+#             //
//   Updated: 2018/06/02 13:05:17 by oposhiva         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Solution.class.hpp"
#include <cmath>

Solution::Solution() {}

Solution::Solution( const Solution &rhs ) {
	*this = rhs;
}

Solution::Solution( std::string line ) : _line( line ) {}

double	Solution::numbers( std::vector<std::string> vec ) {
	double	num = 0;
	auto	i = std::find( vec.begin(), vec.end(), "=" );

	for ( int j = 0; j < vec.size(); j++ ) {
		if ( isdigit( vec[j][0] ) && vec[j + 1] != "*" ) {
			if ( vec[j - 1] == "+" && i - vec.begin() > j ||
				 vec[j - 1] == "-" && i - vec.begin() < j )
				num += std::stod( vec[j] );
			else
				num -= std::stod( vec[j] );
		}
	}
	return ( num );
}

double	Solution::counter( std::vector<std::string> vec, std::string subs ) {
	auto	i = std::find( vec.begin(), vec.end(), "=" );
	double	num = 0;

	for (  auto j = std::find( vec.begin(), vec.end(), subs); j != vec.end() ; j = std::find( j + 1, vec.end(), subs )) {
		if ( vec[j - vec.begin() - 1] == "*" ) {

			if ( vec[j - vec.begin() - 3] == "-" && i > j ||
				 vec[j - vec.begin() - 3] == "+" && i < j ||
				 vec[j - vec.begin() - 3] == "=")
				num -= std::stod( vec[j - vec.begin() - 2] );
			else
				num += std::stod( vec[j - vec.begin() - 2] );
		}
		else
			if ( vec[j - vec.begin() - 1] == "+" && i > j ||
				 vec[j - vec.begin() - 1] == "-" && i < j  )
				num += 1;
			else
				num -= 1;
	}
	return ( num );
}

void	Solution::parse_line() {
	std::vector<std::string> line;

	std::istringstream	iss( _line );

	while ( iss ) {
		std::string subs;
		iss >> subs;
		line.push_back( subs );
	}
	_equation.push_back( counter( line, "X^2" ));
	_equation.push_back( counter( line, "X" ) + counter( line, "X^1" ));
	_equation.push_back( counter( line, "X^0" ) + numbers( line ));
	for ( int i = 0; i < _equation.size(); i++ )
		std::cout << _equation[i] << std::endl;
	for ( int i = 0; i < _equation.size(); i++ )
		if ( _equation[i] ) {
			_degree = 2 - i;
			break ;
		}

	solve_2degree();
}

void	Solution::solve_2degree(  ) {
	double 	x1, x2;
	double D = _equation[1]*_equation[1] - 4*_equation[0]*_equation[2];

	if ( D > 0 ) {
		x1 = ( -1 * _equation[1] + sqrt( D )) / ( 2 * _equation[0] );
		x2 = ( -1 * _equation[1] - sqrt( D )) / ( 2 * _equation[0] );
		std::cout << x1 << std::endl << x2 << std::endl;

	}
	else if ( D == 0) {
		x1 = ( -1 * _equation[1] + sqrt( D )) / ( 2 * _equation[0] );
		std::cout << x1 << std::endl;
	}
	else
		std::cout << "The equation does not have a solution!" << std::endl;

}

const Solution& Solution::operator=( const Solution &rhs ) {
	//!!!
	return ( *this );
}

Solution::~Solution() {}