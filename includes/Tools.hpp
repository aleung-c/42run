#ifndef TOOLS_HPP
# define TOOLS_HPP

#include "QDrun.hpp"

	class Tools
	{
		public:
			static float	LinearInterpolation(float a, float b, float mu);
			static double	GetRandomDouble(double min, double max);
	};

#endif