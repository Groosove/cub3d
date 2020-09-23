/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flavon <flavon@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 22:18:34 by flavon            #+#    #+#             */
/*   Updated: 2020/09/23 11:47:51 by flavon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_param(t_param *param)
{
	param->c_col = 0;
	param->f_col = 0;
	param->dir = '\0';
	param->ea_img = NULL;
	param->we_img = NULL;
	param->so_img = NULL;
	param->s_img = NULL;
	param->no_img = NULL;
	param->f = 0;
	param->c = 0;
}

void	init_keys(t_key *key)
{
	key->down = 0;
	key->up = 0;
	key->left = 0;
	key->right = 0;
	key->r_right = 0;
	key->r_left = 0;
}
