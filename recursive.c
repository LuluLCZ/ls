/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacaze <llacaze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 11:14:36 by llacaze           #+#    #+#             */
/*   Updated: 2018/01/25 17:41:45 by llacaze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char		*pather(struct dirent *sd, char *av)
{
	char	*path;
	char	*tmp;

	path = ft_strnew(ft_strlen(av) + ft_strlen(sd->d_name) + 2000);
	tmp = path;
	path = ft_strjoin(path, av);
	free(tmp);
	if (ft_strcmp(av, "/") != 0)
	{
		tmp = path;
		path = ft_strjoin(path, "/");
		free(tmp);
	}
	tmp = path;
	path = ft_strjoin(path, sd->d_name);
	free(tmp);
	return (path);
}

t_info		*read_dir(DIR *dir, char *path, t_acv a)
{
	struct dirent	*sd;
	char			*tmp;
	t_info			*recursive;
	struct stat		fstat;

	recursive = init_info();
	while ((sd = readdir(dir)) != NULL)
	{
		tmp = recursive->path;
		recursive->path = pather(sd, path);
		free(tmp);
		if (lstat(recursive->path, &fstat) == -1)
			perror(recursive->path);
		tmp = recursive->name;
		recursive->name = ft_strdup(sd->d_name);
		free(tmp);
		recursive = ft_stat(fstat, recursive, a);
		recursive = refresh_info(recursive);
	}
	return (recursive);
}

void		the_recursive(t_info *recursive, t_acv a, t_info *args)
{
	while (a.ur == 1 && recursive != NULL && recursive->name != NULL)
	{
		if (recursive->type == 'd' && ft_strcmp(recursive->name, ".") != 0 &&
				ft_strcmp(recursive->name, "..") != 0)
			if ((a.a != 1 && recursive->name[0] != '.') ||
				(a.a == 1 && ft_strcmp(recursive->name, ".") != 0 &&
				ft_strcmp(recursive->name, "..") != 0))
			{
				write(1, "\n", 1);
				ft_putstr(recursive->path);
				ft_putstr(":\n");
				oodir(a, recursive->path, args);
			}
		recursive = ((a.r == 1) ? recursive->prev : recursive->next);
	}
}

void		oodir(t_acv a, char *path, t_info *args)
{
	t_info			*recursive;
	DIR				*dir;

	dir = opendir(path);
	if (dir != NULL)
	{
		recursive = read_dir(dir, path, a);
		recursive = go_begin(recursive);
		recursive = sort_options(recursive, a);
		the_test(recursive, a, 1);
		if (a.r == 1)
		{
			recursive = go_end(recursive);
			recursive = recursive->prev;
		}
		closedir(dir);
		(a.ur == 1) ? the_recursive(recursive, a, args) : 0;
		(a.r == 1) ? free_info_prev(recursive) : free_info(recursive);
	}
	else if (args->type == 'd')
	{
		write(2, "ls: ", 4);
		perror(path);
	}
}

void		ft_recup(t_acv a)
{
	t_info			*args;
	t_sizem			s;

	args = sort_args(a);
	s = (a.l == 1) ? sizemax(args, a, 0) : init_size();
	display(args, a, 1);
	if (a.ac != a.stfile)
	{
		args = ((a.r == 1) ? go_end(args) : go_begin(args));
		args = ((a.r == 1) ? args->prev : args);
	}
	while (args)
	{
		norm_one_rec(args, a);
		if (a.stfile == a.ac)
			break ;
		if ((a.r == 1) ? args->prev : args->next)
			args = norm_recup(a, args);
		else
			break ;
	}
	free_info(args);
}
