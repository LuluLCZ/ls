/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm_four.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacaze <llacaze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 19:58:43 by llacaze           #+#    #+#             */
/*   Updated: 2018/01/25 15:59:42 by llacaze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_info		*norm_fod(t_info *finfo, t_acv a, t_info *new_list)
{
	struct stat		fstat;
	t_info			*testu;
	t_info			*tmp;

	if (finfo->type == 'l' && a.l == 0)
	{
		if (lstat(finfo->liname, &fstat) != -1)
		{
			testu = init_info();
			testu = ft_stat(fstat, testu, a);
			if (testu->type != 'd')
			{
				tmp = new_list;
				copy_info(finfo, new_list);
				new_list = refresh_info(new_list);
			}
			free_info(testu);
		}
		else
		{
			new_list = finfo;
			new_list = refresh_info(new_list);
		}
	}
	return (new_list);
}

t_info		*norm_dof(t_info *finfo, t_acv a, t_info *new_list)
{
	t_info		*testu;
	struct stat	fstat;

	if (lstat(finfo->liname, &fstat) != -1)
	{
		testu = init_info();
		testu = ft_stat(fstat, testu, a);
		if (testu->type == 'd')
		{
			copy_info(finfo, new_list);
			new_list = refresh_info(new_list);
		}
		free_info(testu);
	}
	return (new_list);
}

void		norm_check_opt(int i, t_acv a)
{
	if (ft_strlen(a.av[i]) == 0)
	{
		write(2, "ls: fts_open: No such file or directory", 39);
		exit(EXIT_FAILURE);
	}
}

t_info		*norm_recup(t_acv a, t_info *args)
{
	t_info		*tmp;

	tmp = args;
	args = ((a.r == 1) ? args->prev : args->next);
	if (a.r == 1)
		args->next = tmp;
	else
		args->prev = tmp;
	tmp = NULL;
	return (args);
}

char		*slinks(t_info *finfo, t_sizem s)
{
	char	*size;
	char	*tmpd;
	char	*tmpp;
	char	*tmp;
	int		i;

	tmpd = ft_itoa(s.slinks);
	size = ft_strnew(ft_strlen(tmpd) * 20);
	size = ft_memset(size, ' ', ft_strlen(tmpd));
	free(tmpd);
	tmpp = ft_itoa(finfo->nb_links);
	size = ft_strcat(size, tmpp);
	i = ft_strlen(tmpp);
	free(tmpp);
	tmp = size + i;
	free(size);
	return (tmp);
}
