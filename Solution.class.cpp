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
#include "sstream"

Solution::Solution() {}

Solution::Solution( const Solution &rhs ) {
	*this = rhs;
}

Solution::Solution( std::string line ) : _degree( 0 ), _line( line ) {}

const Solution& Solution::operator=( const Solution &rhs ) {
	this->_degree = rhs._degree;
	this->_line = rhs._line;
	this->_result = rhs._result;
	this->_equation = rhs._equation;
	return ( *this );
}

double	Solution::numbers( std::vector<std::string> vec ) {
	double	num = 0;
	auto	i = std::find( vec.begin(), vec.end(), "=" );

	for ( int j = 0; j < static_cast<int>( vec.size() ); j++ ) {
		if ( ( isdigit( vec[j][0] ) || ( vec[j][0] == '-'
				&& isdigit( vec[j][1] ))) && vec[j + 1] != "*" ) {
			if (( vec[j - 1] == "+" && i - vec.begin() > j ) ||
				( vec[j - 1] == "-" && i - vec.begin() < j ) || !j )
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

	for (  auto j = std::find( vec.begin(), vec.end(), subs); j != vec.end() ;
		   j = std::find( j + 1, vec.end(), subs )) {
		if ( vec[j - vec.begin() - 1] == "*" ) {

			if (( vec[j - vec.begin() - 3] == "-" && i > j ) ||
				( vec[j - vec.begin() - 3] == "+" && i < j ) ||
				 vec[j - vec.begin() - 3] == "=")
				num -= std::stod( vec[j - vec.begin() - 2] );
			else
				num += std::stod( vec[j - vec.begin() - 2] );
		}
		else
			if (( vec[j - vec.begin() - 1] == "+" && i > j ) ||
				( vec[j - vec.begin() - 1] == "-" && i < j ))
				num += 1;
			else
				num -= 1;
	}
	return ( num );
}

void	Solution::degree_check() {
	int 			temp;
	std::string		deg;

	for ( size_t i = 0; i != std::string::npos; i = _line.find( "X^", i + 1 )) {
		if ( _line[i + 2] - '0' < 3 && _line[i + 3] == ' ' )
			continue;
		std::istringstream	iss(_line.substr( i + 2 ));
		iss >> temp;
		if ( temp > _degree )
			_degree = temp;
	}
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
	for ( size_t i = 0; i < _equation.size(); i++ )
		if ( _equation[i] ) {
			_degree = 2 - i;
			break ;
		}
}

void	Solution::solve_2degree(  ) {
	double 	x1, x2;
	double D = _equation[1]*_equation[1] - 4*_equation[0]*_equation[2];

	if ( D > 0 ) {
		x1 = ( -1 * _equation[1] - sqrt( D )) / ( 2 * _equation[0] );
		x2 = ( -1 * _equation[1] + sqrt( D )) / ( 2 * _equation[0] );
		_result = "Discriminant is more than 0!\n";
		_result += "X1 = " + std::to_string( x1 ) + "\nX2 = " +  std::to_string( x2 ) + "\n";

	}
	else if ( D == 0) {
		x1 = ( -1 * _equation[1] + sqrt( D )) / ( 2 * _equation[0] );
		_result = "Discriminant is equal to 0!\n";
		_result = "X = " + std::to_string( x1 ) + "\n";
	}
	else
		_result = "Discriminant is less than 0!\nThe equation does not have a solution!\n";

}

void	Solution::solve_1degree() {
	double x;

	x = -1 * _equation[2] / _equation[1];
	_result = "X = " + std::to_string( x ) + "\n";
}

void	Solution::solve_0degree() {
	if ( !_equation[2] )
		_result = "The solution is all the real numbers!";
	else
		_result = "The equation has no solution!";
}

void	Solution::reduced() {
	std::cout << "Reduced form:" << std::endl;
	if ( _equation[0] )
		std::cout << _equation[0] << "X^2 ";
	if ( _equation[1] ) {
		if ( _equation[1] < 0 && _equation[0]) {
			_equation[1] *= -1;
			std::cout << "- ";

		} else if ( _equation[0] )
			std::cout << "+ ";
		std::cout << _equation[1] << "X ";
	}
	if ( _equation[2] ) {
		if ( _equation[2] < 0 && _equation[0] && _equation[1] ) {
			_equation[2] *= -1;
			std::cout << "- ";

		} else if ( _equation[0] || _equation[1] )
			std::cout << "+ ";
		std::cout << _equation[2];
	}
	if ( !_equation[0] && !_equation[1] && !_equation[2] )
		std::cout << "0";
	std::cout << " = 0" << std::endl;
}

void	Solution::result() {
	if ( _degree < 3 )
		reduced();
	std::cout << "Polynomial degree: " << _degree << std::endl;
	std::cout << "Solution: " << std::endl << _result << std::endl;
}

void	Solution::solve() {
	degree_check();
	if ( _degree > 2 ) {
		_result = "The polynomial degree is greater than 2!\n";
		result();
		return;
	}
	parse_line();
	if ( _degree == 2 )
		solve_2degree();
	else if ( _degree == 1 )
		solve_1degree();
	else
		solve_0degree();
	result();

}

Solution::~Solution() {}
