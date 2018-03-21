/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacaze <llacaze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 11:49:19 by llacaze           #+#    #+#             */
/*   Updated: 2018/01/25 17:41:40 by llacaze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_acv		norm_checkopts(t_acv a, int i, char *tmp)
{
	char	*str;

	str = ft_strnew(1);
	while (++i <= a.ac - 1 && a.av[i][0] == '-')
	{
		norm_check_opt(i, a);
		if (a.av[i][0] == '-')
		{
			if (ft_strcmp(a.av[i], "--") == 0)
			{
				i++;
				break ;
			}
			if (ft_strlen(a.av[i]) == 1)
				break ;
			ft_check_char(a.av[i], '-') > 1 ? illopt(a.av[i]) : 0;
			tmp = str;
			str = ft_strjoin(str, a.av[i]);
			free(tmp);
		}
	}
	a.opts = free_norm_opts(a.opts, str);
	a.stfile = i;
	return (a);
}

t_acv		check_options(t_acv a)
{
	int			i;
	char		*tmp;

	tmp = NULL;
	i = 0;
	a = norm_checkopts(a, i, tmp);
	return (a);
}

t_acv		norm_opts_nd(t_acv a, size_t x)
{
	(OPL(a.opts[x])) ? a.l = 1 : a.ich++;
	(OPT(a.opts[x])) ? a.t = 1 : a.ich++;
	(OPR(a.opts[x])) ? a.r = 1 : a.ich++;
	(OGR(a.opts[x])) ? a.ur = 1 : a.ich++;
	(OPA(a.opts[x])) ? a.a = 1 : a.ich++;
	(OGS(a.opts[x])) ? a.us = 1 : a.ich++;
	(OGG(a.opts[x])) ? a.ug = 1 : a.ich++;
	(ONE(a.opts[x])) ? a.on = 1 : a.ich++;
	return (a);
}

void		norm_opts_rd(char *new_str, t_acv a, size_t x)
{
	char	*tmp;

	new_str[0] = a.opts[x];
	tmp = new_str;
	new_str = ft_strjoin("ls: illegal option -- ", new_str);
	free(tmp);
	write(2, new_str, ft_strlen(new_str));
	write(2, "\nusage: ls [-GSalrt] [file ...]\n", 32);
	free(new_str);
	exit(EXIT_FAILURE);
}

t_acv		opts(t_acv a)
{
	size_t		x;
	char		*new_str;

	if (!(new_str = (char *)malloc(sizeof(char) * 2)))
		exit(EXIT_FAILURE);
	x = 1;
	a = check_options(a);
	if (a.opts == NULL)
		a.opts = ft_strdup("\0");
	while (x < ft_strlen(a.opts))
	{
		a.ich = 0;
		a = norm_opts_nd(a, x);
		if (a.ich != 7)
			norm_opts_rd(new_str, a, x);
		x++;
	}
	free(a.opts);
	a.opts = NULL;
	free(new_str);
	return (a);
}
