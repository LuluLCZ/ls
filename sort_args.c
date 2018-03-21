/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacaze <llacaze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 11:54:17 by llacaze           #+#    #+#             */
/*   Updated: 2018/01/24 17:25:30 by llacaze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_info		*sort_nargs(t_info *finfo, t_acv a)
{
	t_info		*head;

	finfo = go_begin(finfo);
	head = finfo;
	if (a.ac - a.stfile == 1)
		return (finfo);
	if (a.ac != a.stfile && finfo->next->name != NULL &&
			finfo->name != NULL && finfo->next->next != NULL)
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

t_info		*sort_sargs(t_info *finfo)
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

t_info		*sort_dargs(t_info *finfo)
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

t_info		*sort_fod(t_info *finfo, t_acv a, t_info *new_list)
{
	t_info		*tmp;

	finfo = go_begin(finfo);
	while (finfo->next != NULL)
	{
		if (finfo->type == 'l' && a.l == 0)
			new_list = norm_fod(finfo, a, new_list);
		else if (finfo->type != 'd')
		{
			tmp = new_list;
			copy_info(finfo, new_list);
			new_list = refresh_info(new_list);
		}
		finfo = finfo->next;
	}
	return (new_list);
}

t_info		*sort_dof(t_info *finfo, t_acv a)
{
	t_info	*new_list;
	t_info	*tmp;

	tmp = init_info();
	new_list = sort_fod(finfo, a, tmp);
	finfo = go_begin(finfo);
	while (finfo->next != NULL)
	{
		if (finfo->type == 'd')
		{
			copy_info(finfo, new_list);
			new_list = refresh_info(new_list);
		}
		else if (finfo->type == 'l' && a.l == 0)
			new_list = norm_dof(finfo, a, new_list);
		finfo = finfo->next;
		if (finfo == NULL)
			break ;
	}
	return (new_list);
}
