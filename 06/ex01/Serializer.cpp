/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serializer.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leoaguia <leoaguia@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/27 19:59:52 by leoaguia          #+#    #+#             */
/*   Updated: 2026/08/27 21:17:23 by leoaguia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Serializer.cpp

#include "Serializer.hpp"

Serializer::Serializer() {}

Serializer::Serializer(const Serializer&) {}

Serializer&	Serializer::operator=(const Serializer&)
{
	return (*this);
}

Serializer::~Serializer() {}

uintptr_t	Serializer::serialize(Data* ptr)
{
	return(reinterpret_cast<uintptr_t>(ptr));
}

Data*		Serializer::deserialize(uintptr_t raw)
{
	return(reinterpret_cast<Data*>(raw));
}
