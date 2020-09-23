/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flavon <flavon@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 20:59:23 by flavon            #+#    #+#             */
/*   Updated: 2020/09/17 00:52:50 by flavon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>

# define BUFFER_SIZE 32

typedef struct		s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

int					ft_atoi(const char *src, int *index);

int					ft_isdigit(int c);

void				ft_putchar(char c);

void				ft_putstr_fd(char *s);

void				ft_puterror(char *msg);

int					ft_strncmp(const char *s1, const char *s2, size_t n);

int					ft_isspace(char c);

char				*ft_strdup(const char *s1);

char				*ft_strdup_f(char *str, int f);

char				*ft_strchr(const char *str, int c);

void				*ft_calloc(size_t count, size_t size);

char				*ft_strjoin(char const *s1, char const *s2);

int					get_next_line(int fd, char **line);

size_t				ft_strlen(const char *str);

void				ft_bzero(void *s, size_t n);

t_list				*ft_lstnew(void *content);

void				ft_lstadd_front(t_list **lst, t_list *new_lst);

int					ft_lstsize(t_list *lst);

t_list				*ft_lstlast(t_list *lst);

void				ft_lstadd_back(t_list **lst, t_list *new_lst);

void				ft_lstdelone(t_list *lst, void (*del)(void *));

void				ft_lstclear(t_list **lst, void (*del)(void *));

void				ft_lstiter(t_list *lst, void (*f)(void *));

t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
		void (*del)(void *));

#endif