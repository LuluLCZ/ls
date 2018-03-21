/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacaze <llacaze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 11:10:56 by llacaze           #+#    #+#             */
/*   Updated: 2018/01/24 19:35:53 by llacaze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_info		*init_info(void)
{
	t_info		*finfo;

	if (!(finfo = (t_info *)malloc(sizeof(t_info) + 5120)))
		return (NULL);
	finfo->prev = NULL;
	finfo->path = NULL;
	finfo->uid = NULL;
	finfo->gid = NULL;
	finfo->date = NULL;
	finfo->name = NULL;
	finfo->liname = NULL;
	finfo->namel = NULL;
	finfo->next = NULL;
	return (finfo);
}

t_info		*refresh_info(t_info *finfo)
{
	t_info	*tmp;

	tmp = finfo;
	finfo = finfo->next;
	if (!(finfo = (t_info *)malloc(sizeof(t_info) + 5120)))
		return (NULL);
	finfo->next = NULL;
	finfo->path = NULL;
	finfo->uid = NULL;
	finfo->gid = NULL;
	finfo->date = NULL;
	finfo->name = NULL;
	finfo->liname = NULL;
	finfo->namel = NULL;
	finfo->prev = tmp;
	return (finfo);
}

void		free_info(t_info *finfo)
{
	t_info *tmp;

	finfo = go_begin(finfo);
	while (finfo)
	{
		if (finfo->next)
			tmp = finfo->next;
		norm_free(finfo);
		if (finfo->next)
		{
			free(finfo);
			finfo = tmp;
			tmp = NULL;
		}
		else
			break ;
	}
	free(finfo);
}

void		free_info_prev(t_info *finfo)
{
	t_info *tmp;

	finfo = go_end(finfo);
	while (finfo)
	{
		if (finfo->prev)
			tmp = finfo->prev;
		norm_free_prev(finfo);
		if (finfo->prev)
		{
			free(finfo);
			finfo = tmp;
			tmp = NULL;
		}
		else
			break ;
	}
	free(finfo);
}

t_info		*go_begin(t_info *finfo)
{
	t_info		*tmp;

	while (finfo && finfo->prev != NULL)
	{
		tmp = finfo;
		finfo = finfo->prev;
		finfo->next = tmp;
		tmp = NULL;
	}
	return (finfo);
}
