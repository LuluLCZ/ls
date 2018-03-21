/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacaze <llacaze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 11:47:44 by llacaze           #+#    #+#             */
/*   Updated: 2018/01/25 18:12:34 by llacaze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	display(t_info *finfo, t_acv a, int i)
{
	t_sizem		s;
	int			j;
	int			k;

	a = opts(a);
	k = 0;
	j = a.stfile;
	if ((a.ac != a.stfile))
	{
		finfo = ((a.r == 1) ? go_end(finfo) : go_begin(finfo));
		finfo = ((a.r == 1) ? finfo->prev : finfo);
	}
	s = sizemax(finfo, a, 0);
	while (((a.r == 1) ? finfo != NULL : finfo->next != NULL))
	{
		if (finfo->type != 'd')
			norm_one_aff(finfo, s, a, i);
		finfo = ((a.r == 1) ? finfo->prev : finfo->next);
	}
}

void	disp_name(t_info *finfo, t_acv a)
{
	if (finfo->type == 'l' && a.l == 0)
		norm_three_aff(finfo, a);
	else if (finfo->type == 'd')
	{
		if ((a.r == 1 && finfo->next != NULL) ||
				(a.r == 0 && finfo->prev != NULL))
			write(1, "\n", 1);
		ft_putstr(finfo->name);
		ft_putstr(":\n");
	}
}

void	the_test(t_info *finfo, t_acv a, int i)
{
	t_sizem		s;

	a = opts(a);
	s = sizemax(finfo, a, 1);
	if (a.l == 1 && s.slinks != 0)
	{
		ft_putstr("total ");
		ft_putnbr(s.tot);
		write(1, "\n", 1);
	}
	finfo = ((a.r == 1) ? go_end(finfo) : go_begin(finfo));
	finfo = ((a.r == 1) ? finfo->prev : finfo);
	while (finfo != NULL && finfo->name != NULL)
	{
		if ((a.a == 0 && finfo->name[0] != '.') || (a.a == 1))
		{
			ft_disp(finfo, a.l, a, s);
			if (i == 1 && a.l == 0)
				write(1, "\n", 1);
		}
		finfo = ((a.r == 1) ? finfo->prev : finfo->next);
		if (finfo == NULL)
			break ;
	}
}
