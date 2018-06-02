// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Solution.class.hpp                                 :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: oposhiva <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/06/02 13:05:51 by oposhiva          #+#    #+#             //
//   Updated: 2018/06/02 13:05:58 by oposhiva         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef SOLUTION_CLASS_HPP
# define SOLUTION_CLASS_HPP

#include <iostream>
#include <sstream>
#include <vector>

class Solution {
private:
	int 				_degree;
	std::string			_line;
	std::vector<double>	_equation;
public:
	Solution();
	Solution( std::string line );
	Solution( const Solution &rhs );

	void	parse_line();
	double	counter( std::vector<std::string> vec, std::string subs );
	double	numbers( std::vector<std::string> vec );
	void	solve_2degree();

	const Solution	&operator=( const Solution &rhs );


	~Solution();
};

#endif