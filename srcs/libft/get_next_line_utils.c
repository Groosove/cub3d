/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flavon <flavon@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 21:24:52 by flavon            #+#    #+#             */
/*   Updated: 2020/09/08 23:02:28 by flavon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup_f(char *str, int f)
{
	char	*res;
	size_t	len;
	size_t	i;

	len = 0;
	i = 0;
	while (str[len])
		len++;
	if (!(res = (char *)malloc(sizeof(char) * len + 1)))
		return (NULL);
	while (i < len)
	{
		res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	if (f)
		free(str);
	return (res);
}

char	*ft_strchr(const char *str, int c)
{
	while (*str)
	{
		if (*str == c)
			return ((char *)str);
		str++;
	}
	if ((char)c == '\0')
		return ((char *)str);
	return (NULL);
}

