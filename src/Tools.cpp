#include "../includes/QDrun.hpp"

float	Tools::LinearInterpolation(float a, float b, float mu)
{
	return (a * (1 - mu) + b * mu);
}

double	Tools::GetRandomDouble(double min, double max)
{
    double before = rand() % (int)max + (int)min;
    double after = (double)rand() / RAND_MAX;
    double result = before + after;
    if (result < min || result > max) {
        result = GetRandomDouble(min, max);
    }
    return result;
}

/*
**	Does obj1 collide with obj2 ?
*/

// bool	Tools::IsColliding(GameObject *obj1, GameObject *obj2)
// {

// }