/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serializer.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leoaguia <leoaguia@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/27 19:59:14 by leoaguia          #+#    #+#             */
/*   Updated: 2026/08/27 20:26:30 by leoaguia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	SERIALIZER_HPP
# define SERIALIZER_HPP

# include <stdint.h>	// We need it to use uintptr_t on C++98
# include "Data.hpp"

class	Serializer
{
	private:
		// Ortodoxal Canonical Form
		Serializer();
		Serializer(const Serializer& other);
		Serializer&	operator=(const Serializer& other);
		~Serializer();

	public:
		//	It takes a pointer and converts it to uintptr_t.
		static uintptr_t serialize(Data* ptr);

		//	It takes an uintptr_t parameter and converts it to a pointer to Data.
		static Data* deserialize(uintptr_t raw);
};

#endif