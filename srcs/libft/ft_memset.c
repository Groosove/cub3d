/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flavon <flavon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 19:04:11 by flavon            #+#    #+#             */
/*   Updated: 2020/10/21 19:04:12 by flavon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *ptr, int value, size_t num)
{
	char	*tmp;
	char	number;

	tmp = (char *)ptr;
	number = (char)value;
	while (num-- != 0)
		*tmp++ = number;
	return (ptr);
}