/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacaze <llacaze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 13:36:05 by llacaze           #+#    #+#             */
/*   Updated: 2018/01/23 20:43:10 by llacaze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		color(t_info *finfo)
{
	if (finfo->type == 'd' && finfo->chm[8] != 't')
		ft_putstr("\033[1;36m");
	else if (finfo->type == 'd' && finfo->chm[8] == 't')
		ft_putstr("\033[0;30;42m");
	else if (finfo->type == 'l')
		ft_putstr("\033[0;35m");
	else if (finfo->type == '-' && (finfo->chm[8] == 'x' ||
				finfo->chm[8] == 't'))
		ft_putstr("\033[1;31m");
}
