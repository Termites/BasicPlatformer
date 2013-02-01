#pragma once

#include <iostream>
#include<ostream>
#include<cstdlib>

inline void Debug_Error(const std::ostream&Error)
{
	std::cout<<Error<<std::endl;
	exit(EXIT_FAILURE);
}
inline void Debug_Warn(const std::ostream&Error)
{
	std::cout<<Error<<std::endl;
}
