#include "Lib.hpp"
#include <iostream>
#include <boost/math/special_functions/binomial.hpp>

void foo(){
	std::string h("hallo");
	int i = boost::math::binomial_coefficient<double>(3,2);
	std::cout << h << i << std::endl;
}
