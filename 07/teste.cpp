#include <iostream>
#include <stdlib.h>

template <class T>
T add(T a, T b) noexcept
{
	return (a + b);
}

int	main()
{
	std::cout << add<int>(1, 2);

	std::cout << '\n';

	std::cout << add<double>(1.55, 2.5);

	std::cout << std::endl;

	return (0);
}