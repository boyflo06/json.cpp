/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nullptr.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 19:23:35 by fghysbre          #+#    #+#             */
/*   Updated: 2025/02/22 19:27:43 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

struct ft_nullptr_t {
	template <typename T>
	operator T*() const { return 0; }
	
	template <typename C, typename T>
	operator T C::*() const { return 0; }
	
private:
	void operator&() const;
};

const ft_nullptr_t ft_nullptr = {};