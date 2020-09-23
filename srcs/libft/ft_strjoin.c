/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flavon <flavon@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 12:27:34 by flavon            #+#    #+#             */
/*   Updated: 2020/05/27 10:09:00 by flavon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dst;
	int		count;

	if (s1 == 0 || s2 == 0)
		return (0);
	if (!(dst = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1))))
		return (0);
	count = 0;
	while (*s1 != 0)
		dst[count++] = *s1++;
	while (*s2 != 0)
		dst[count++] = *s2++;
	dst[count] = 0;
	return (dst);
}
