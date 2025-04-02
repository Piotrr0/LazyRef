#ifndef LAZYMATH_H
#define LAZYMATH_H

class LazyMath
{
public:
	static int CeilToInt(const float num);

	template<typename T>
	static T Clamp(const T value, const T min, const T max);
};


template <typename T>
T LazyMath::Clamp(const T value, const T min, const T max)
{
    if (value > max)
        return max;
    if (value < min)
        return min;

    return value;
}

#endif // !LAZYMATH_H