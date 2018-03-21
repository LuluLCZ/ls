/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm_one.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacaze <llacaze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 17:25:24 by llacaze           #+#    #+#             */
/*   Updated: 2018/01/25 16:33:54 by llacaze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		norm_one_rec(t_info *args, t_acv a)
{
	struct stat		fstat;

	if (stat(args->name, &fstat) != -1)
	{
		if ((args->type == 'd' || (args->type == 'l' && a.l == 0)))
		{
			if (a.ac - a.stfile > 1)
				disp_name(args, a);
			oodir(a, args->name, args);
		}
	}
}

void		norm_two_aff(t_info *finfo, t_sizem s, t_acv a, struct stat fstat)
{
	t_info *testu;

	testu = init_info();
	testu = ft_stat(fstat, testu, a);
	if (testu->type != 'd')
	{
		ft_disp(finfo, a.l, a, s);
		write(1, "\n", 1);
	}
	free_info(testu);
}

void		norm_one_aff(t_info *finfo, t_sizem s, t_acv a, int i)
{
	struct stat		fstat;

	if (finfo->type == 'l' && a.l == 0)
	{
		if (lstat(finfo->liname, &fstat) != -1)
			norm_two_aff(finfo, s, a, fstat);
		else
		{
			ft_disp(finfo, a.l, a, s);
			write(1, "\n", 1);
		}
	}
	else if ((a.a == 0 && finfo->name[0] != '.') || (a.a == 1))
	{
		ft_disp(finfo, a.l, a, s);
		if (i == 1 && a.l == 0)
			write(1, "\n", 1);
	}
}

void		norm_three_aff(t_info *finfo, t_acv a)
{
	struct stat		fstat;
	t_info			*testu;

	if (lstat(finfo->liname, &fstat) != -1)
	{
		testu = init_info();
		testu = ft_stat(fstat, testu, a);
		if (testu->type == 'd')
		{
			if ((a.r == 1 && finfo->next != NULL) ||
					(a.r == 0 && finfo->prev != NULL))
				write(1, "\n", 1);
			ft_putstr(finfo->name);
			ft_putstr(":\n");
		}
		free_info(testu);
	}
	else
		ft_putstr(finfo->name);
}
