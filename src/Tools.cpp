#include "../includes/QDrun.hpp"

float	Tools::LinearInterpolation(float a, float b, float mu)
{
	return (a * (1 - mu) + b * mu);
}

/*
**	Does obj1 collide with obj2 ?
*/

// bool	Tools::IsColliding(GameObject *obj1, GameObject *obj2)
// {

// }