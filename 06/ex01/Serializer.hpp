/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serializer.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leoaguia <leoaguia@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/27 19:59:14 by leoaguia          #+#    #+#             */
/*   Updated: 2026/08/27 21:13:59 by leoaguia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Serializer.hpp

#ifndef	SERIALIZER_HPP
# define SERIALIZER_HPP

# include "Data.hpp"
# include <stdint.h>	// We need it to use uintptr_t on C++98

class	Serializer
{
	private:
		// Ortodoxal Canonical Form
		Serializer();
		Serializer(const Serializer&);
		Serializer&	operator=(const Serializer&);
		~Serializer();

	public:
		//	It takes a pointer and converts it to uintptr_t.
		static uintptr_t serialize(Data* ptr);

		//	It takes an uintptr_t parameter and converts it to a pointer to Data.
		static Data* deserialize(uintptr_t raw);
};

#endif