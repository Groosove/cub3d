/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flavon <flavon@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 01:43:52 by flavon            #+#    #+#             */
/*   Updated: 2020/05/10 12:02:23 by flavon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list *list;
	t_list *tmp;

	list = 0;
	while (lst != 0)
	{
		tmp = ft_lstnew(f(lst->content));
		if (tmp == 0)
		{
			ft_lstclear(&list, del);
			return (0);
		}
		ft_lstadd_back(&list, tmp);
		lst = lst->next;
	}
	return (list);
}
