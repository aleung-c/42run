#include "../includes/QDrun.hpp"

float	Tools::CubicInterpolation(float a, float b, float mu)
{
	return (a * (1 - mu) + b * mu);
}
