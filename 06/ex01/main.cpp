/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leoaguia <leoaguia@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/27 19:58:32 by leoaguia          #+#    #+#             */
/*   Updated: 2026/08/27 21:28:29 by leoaguia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// main.cpp

#include "Serializer.hpp"
#include <iostream>

int main()
{
	// 1. Create our data structure
	Data original;
	original.id = 94;
	original.name = "Gengar";

	std::cout << "---        BEFORE        ---" << std::endl;
	std::cout << "Memory Address: " << &original << std::endl;
	std::cout << "Data ID       : " << original.id << std::endl;
	std::cout << "Data Name     : " << original.name << std::endl;
	std::cout << "----------------------------\n" << std::endl;

	// 2. Serialize (structure pointer -> integer value)
	uintptr_t rawData = Serializer::serialize(&original);

	std::cout << "---  SERIALIZATION  ---" << std::endl;
	std::cout << "Raw uintptr_t value: " << rawData << std::endl;
	std::cout << "-----------------------\n" << std::endl;

	// 3. Deserialize (integer value -> structure pointer)
	Data* reconstructedData = Serializer::deserialize(rawData);

	std::cout << "--- AFTER DESERIALIZATION ---" << std::endl;
	std::cout << "Memory Address: " << reconstructedData << std::endl;

	// The ultimate test: if serialization worked, accessing members from
	// the NEW pointer must print the exact same values.
	std::cout << "Data ID       : " << reconstructedData->id << std::endl;
	std::cout << "Data Name     : " << reconstructedData->name << std::endl;
	std::cout << "-----------------------------\n" << std::endl;

	// Logical conclusion for the evaluator:
	if (reconstructedData == &original)
		std::cout << "SUCCESS: Pointers match perfectly!" << std::endl;
	else
		std::cout << "ERROR: Memory addresses differ." << std::endl;

	return (0);
}