/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacaze <llacaze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 22:53:30 by Lulu              #+#    #+#             */
/*   Updated: 2018/01/24 17:30:45 by llacaze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_info		*sort_name(t_info *finfo)
{
	t_info		*head;

	finfo = go_begin(finfo);
	head = finfo;
	if (finfo != NULL && finfo->name != NULL &&
		finfo->next->name != NULL && finfo->next->next->name != NULL)
	{
		while (finfo->next->next != NULL)
		{
			if (ft_strcmp(finfo->name, finfo->next->name) > 0)
			{
				finfo = ft_swap_double(finfo, finfo->next, &head);
				finfo = go_begin(finfo);
			}
			else
				finfo = finfo->next;
		}
	}
	return (finfo);
}

t_info		*sort_size(t_info *finfo)
{
	t_info		*head;

	finfo = go_begin(finfo);
	head = finfo;
	while (finfo->next->next != NULL)
	{
		if (finfo->size < finfo->next->size)
		{
			finfo = ft_swap_double(finfo, finfo->next, &head);
			finfo = go_begin(finfo);
		}
		else
			finfo = finfo->next;
	}
	return (finfo);
}

t_info		*sort_date(t_info *finfo)
{
	t_info	*head;

	finfo = go_begin(finfo);
	head = finfo;
	if (finfo->next->name != NULL && finfo->name != NULL &&
			finfo->next->next != NULL)
	{
		while (finfo->next->next != NULL)
		{
			if (finfo->stmtime < 0)
				finfo->stmtime = -finfo->stmtime;
			if (finfo->next->stmtime - finfo->stmtime > 0)
			{
				finfo = ft_swap_double(finfo, finfo->next, &head);
				finfo = go_begin(finfo);
			}
			else
				finfo = finfo->next;
		}
	}
	return (finfo);
}

t_info		*sort_options(t_info *finfo, t_acv a)
{
	finfo = sort_name(finfo);
	if (a.t == 1)
		finfo = sort_date(finfo);
	if (a.us == 1)
		finfo = sort_size(finfo);
	finfo = go_begin(finfo);
	return (finfo);
}
