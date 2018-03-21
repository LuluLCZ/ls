/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recup_names.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacaze <llacaze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 11:23:05 by llacaze           #+#    #+#             */
/*   Updated: 2018/01/24 17:24:33 by llacaze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_info		*norm_recup_one(t_acv a, int i, t_info *finfo)
{
	char	*tmp;

	while (i < a.ac)
	{
		tmp = finfo->name;
		finfo->name = ft_strdup(a.av[i]);
		free(tmp);
		finfo = refresh_info(finfo);
		i++;
	}
	finfo = go_begin(finfo);
	finfo = sort_options(finfo, a);
	return (finfo);
}

int			recup_norm_two(t_info *finfo, t_acv a)
{
	struct stat		fstat;
	int				j;

	j = a.stfile;
	while (finfo->next != NULL)
	{
		if (lstat(finfo->name, &fstat) == -1)
		{
			if (ft_strlen(finfo->name) == 0)
			{
				write(2, "ls: fts_open: No such file or directory\n", 40);
				exit(EXIT_FAILURE);
			}
			write(2, "ls: ", 4);
			perror(finfo->name);
			j++;
		}
		finfo = finfo->next;
	}
	free_info(finfo);
	finfo = NULL;
	return (j);
}

t_info		*norm_four_recup(t_info *finfo, t_acv a, int j)
{
	int			i;
	char		*tmp;
	struct stat	fstat;

	i = a.stfile;
	finfo = init_info();
	while (i < a.ac)
	{
		tmp = finfo->name;
		finfo->name = ft_strdup(a.av[i]);
		free(tmp);
		if (lstat(finfo->name, &fstat) != -1)
		{
			finfo = ft_stat(fstat, finfo, a);
			finfo = refresh_info(finfo);
		}
		i++;
	}
	if (i == j)
	{
		free_info(finfo);
		exit(EXIT_FAILURE);
	}
	return (finfo);
}

t_info		*recup_names(t_acv a)
{
	t_info		*finfo;
	struct stat	fstat;
	int			i;
	int			j;

	finfo = init_info();
	i = a.stfile;
	j = i;
	if (a.stfile == a.ac)
	{
		finfo->name = ft_strdup(".");
		if (lstat(finfo->name, &fstat) != -1)
		{
			finfo = ft_stat(fstat, finfo, a);
			finfo = refresh_info(finfo);
		}
		return (finfo);
	}
	else
	{
		finfo = norm_recup_one(a, i, finfo);
		j = recup_norm_two(finfo, a);
		finfo = norm_four_recup(finfo, a, j);
	}
	return (finfo);
}
