/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm_three.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacaze <llacaze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 19:29:47 by llacaze           #+#    #+#             */
/*   Updated: 2018/01/24 19:37:43 by llacaze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char		norm_perm_two(struct stat fstat, t_info *finfo)
{
	if (fstat.st_mode & S_ISUID)
	{
		if (fstat.st_mode & S_IXUSR)
			finfo->chm[2] = 's';
		else
			finfo->chm[2] = 'S';
	}
	else if (fstat.st_mode & S_IXUSR)
		finfo->chm[2] = 'x';
	else
		finfo->chm[2] = '-';
	return (finfo->chm[2]);
}

char		norm_perm_five(struct stat fstat, t_info *finfo)
{
	if (fstat.st_mode & S_ISGID)
	{
		if (fstat.st_mode & S_IXGRP)
			finfo->chm[5] = 's';
		else
			finfo->chm[5] = 'S';
	}
	else if (fstat.st_mode & S_IXGRP)
		finfo->chm[5] = 'x';
	else
		finfo->chm[5] = '-';
	return (finfo->chm[5]);
}

t_info		*norm_stat(struct stat fstat, t_info *finfo, t_acv a)
{
	finfo = check_type(fstat, finfo);
	finfo = check_protection_links(fstat, finfo, a);
	finfo = check_owner_size(fstat, finfo);
	finfo = check_date_name(fstat, finfo);
	return (finfo);
}

t_info		*norm_sort_a(t_info *new_list, t_acv a)
{
	new_list = sort_nargs(new_list, a);
	if (a.t == 1)
		new_list = sort_dargs(new_list);
	if (a.us == 1)
		new_list = sort_sargs(new_list);
	return (new_list);
}

t_info		*sort_args(t_acv a)
{
	t_info		*tmp;
	t_info		*args;
	t_info		*new_list;

	new_list = recup_names(a);
	new_list = norm_sort_a(new_list, a);
	if (a.stfile - a.ac < -1)
	{
		tmp = new_list;
		args = sort_dof(tmp, a);
		new_list = go_begin(new_list);
		while (new_list)
		{
			tmp = new_list->next;
			free(new_list);
			new_list = tmp;
			tmp = NULL;
		}
		free_info(new_list);
		free(tmp);
		args = go_begin(args);
		return (args);
	}
	return (new_list);
}
