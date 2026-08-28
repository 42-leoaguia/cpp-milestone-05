/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Base.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leoaguia <leoaguia@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/28 00:49:54 by leoaguia          #+#    #+#             */
/*   Updated: 2026/08/28 00:53:15 by leoaguia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Base.hpp

#ifndef BASE_HPP
# define BASE_HPP

class	Base
{
	// Virtual Destructor enables the RTTI (Run-Time Type Information)
	public:
		virtual ~Base();
};

#endif