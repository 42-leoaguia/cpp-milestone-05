/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leoaguia <leoaguia@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/28 00:34:46 by leoaguia          #+#    #+#             */
/*   Updated: 2026/08/28 02:02:00 by leoaguia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// main.cpp

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <exception>

#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

// Randomly instantiates A, B, or C
Base*	generate(void)
{
	int	random = std::rand() % 3;

	if (random == 0)
	{
		std::cout << "Generated: A" << std::endl;
		return (new A());
	}
	else if (random == 1)
	{
		std::cout << "Generated: B" << std::endl;
		return (new B());
	}
	else if (random == 2)
	{
		std::cout << "Generated: C" << std::endl;
		return (new C());
	}
	else
	{
		std::cout << "Impossible" << std::endl;
		return (NULL);
	}
}

// Identify using pointers (relies on NULL returns)
void	identify(Base* p)
{
	if (dynamic_cast<A*>(p) != NULL)
	{
		std::cout << "A" << std::endl;
	}
	else if (dynamic_cast<B*>(p) != NULL)
	{
		std::cout << "B" << std::endl;
	}
	else if (dynamic_cast<C*>(p) != NULL)
	{
		std::cout << "C" << std::endl;
	}
	else
	{
		std::cout << "Unknown Type" << std::endl;
	}
}

// Identify using references (relies on bad_cast exceptions)
void	identify(Base& p)
{
	try
	{
		(void)dynamic_cast<A&>(p);
		std::cout << "A" << std::endl;
		return;
	}
	catch (std::exception& e)
	{
		// C++ throws std::bad_cast on reference failure
	}

	try
	{
		(void)dynamic_cast<B&>(p);
		std::cout << "B" << std::endl;
		return;
	}
	catch (std::exception& e) {}

	try
	{
		(void)dynamic_cast<C&>(p);
		std::cout << "C" << std::endl;
		return;
	}
	catch (std::exception& e) {}

	std::cout << "Unknown Type" << std::endl;
}

int	main(void)
{
	// 1. Random seed planted
	std::srand(static_cast<unsigned int>(std::time(NULL)));

	// 2. Pointer
	std::cout << "--- Pointer Test ---\n" << std::endl;
	for (int i = 0; i < 3; i++)
	{
		Base* instance = generate();
		std::cout << "I'm: ";
		identify(instance);
		delete instance;
		std::cout << std::endl;
	}

	// 3. Reference
	std::cout << "--- Reference Test ---\n" << std::endl;
	for (int i = 0; i < 3; i++)
	{
		Base* instance = generate();
		std::cout << "I'm: ";
		// Dereference the pointer, so it is passed by reference
		identify(*instance);
		delete (instance);
		std::cout << std::endl;
	}

	return (0);
}