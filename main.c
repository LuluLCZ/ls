/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacaze <llacaze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 11:13:01 by llacaze           #+#    #+#             */
/*   Updated: 2018/01/25 17:38:36 by llacaze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_sizem		sizemax(t_info *finfo, t_acv a, int i)
{
	t_sizem		s;

	s = init_size();
	while (finfo && finfo->name != NULL && a.l == 1)
	{
		s = norm_sizem(finfo, a, s, i);
		finfo = finfo->next;
	}
	return (s);
}

char		*huid(t_info *finfo, t_sizem s)
{
	char	*str;
	char	*tmp;

	str = ft_strnew(s.huid + 5000);
	str = ft_memset(str, ' ', s.huid);
	tmp = str;
	str = ft_strjoin(finfo->uid, str + ft_strlen(finfo->uid));
	free(tmp);
	return (str);
}

char		*guid(t_info *finfo, t_sizem s)
{
	char	*str;
	char	*tmp;

	str = ft_strnew(s.hgid + 5000);
	str = ft_memset(str, ' ', s.hgid);
	tmp = str;
	str = ft_strjoin(finfo->gid, str + ft_strlen(finfo->gid));
	free(tmp);
	return (str);
}

void		ft_disp(t_info *finfo, int i, t_acv a, t_sizem s)
{
	i == 1 ? norm_in_main(finfo, s) : 0;
	if (a.ug == 1)
		color(finfo);
	ft_putstr(finfo->name);
	if (a.ug == 1)
		ft_putstr("\033[0m");
	ft_putstr((finfo->type == 'l' && a.l == 1) ? finfo->namel : "");
	if (i == 1)
		write(1, "\n", 1);
}

int			main(int ac, char **av)
{
	t_acv		a;

	a = init_opts();
	a.av = av;
	a.ac = ac;
	a = opts(a);
	ft_recup(a);
	return (0);
}
