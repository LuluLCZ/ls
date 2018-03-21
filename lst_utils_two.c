/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils_two.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacaze <llacaze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 15:58:38 by llacaze           #+#    #+#             */
/*   Updated: 2018/01/24 16:00:15 by llacaze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_info		*go_end(t_info *finfo)
{
	t_info		*tmp;

	while (finfo->next != NULL)
	{
		tmp = finfo;
		finfo = finfo->next;
		finfo->prev = tmp;
	}
	return (finfo);
}

t_info		*add_end(t_info *finfo, t_info *recursive)
{
	recursive = go_begin(recursive);
	while (finfo->next != NULL)
		finfo = finfo->next;
	finfo->next = recursive;
	recursive = finfo->next;
	return (finfo);
}
