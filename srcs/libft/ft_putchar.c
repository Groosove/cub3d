/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flavon <flavon@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/19 13:21:29 by flavon            #+#    #+#             */
/*   Updated: 2020/09/20 11:55:14 by flavon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_putchar(char c)
{
	write(1, &c, 1);
}

void		ft_puterror(char *msg)
{
	if (!msg)
		return ;
	while (*msg)
	{
		ft_putchar(*msg);
		msg++;
	}
}

int			ft_isspace(char c)
{
	if (c == 9 || c == 10 || c == 32 || c == 11 || c == 12 || c == 13)
		return (1);
	return (0);
}