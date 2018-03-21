/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacaze <llacaze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 15:52:52 by llacaze           #+#    #+#             */
/*   Updated: 2018/01/25 17:42:28 by llacaze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		norm_free(t_info *finfo)
{
	if (finfo->name)
		ft_strdel(&finfo->name);
	if (finfo->path)
		ft_strdel(&finfo->path);
	if (finfo->date)
		ft_strdel(&finfo->date);
	if (finfo->namel)
		ft_strdel(&finfo->namel);
	if (finfo->liname)
		ft_strdel(&finfo->liname);
	if (finfo->uid)
		ft_strdel(&finfo->uid);
	if (finfo->gid)
		ft_strdel(&finfo->gid);
}

void		norm_free_prev(t_info *finfo)
{
	if (finfo->name)
		ft_strdel(&finfo->name);
	if (finfo->path)
		ft_strdel(&finfo->path);
	if (finfo->date)
		ft_strdel(&finfo->date);
	if (finfo->namel)
		ft_strdel(&finfo->namel);
	if (finfo->liname)
		ft_strdel(&finfo->liname);
	if (finfo->uid)
		ft_strdel(&finfo->uid);
	if (finfo->gid)
		ft_strdel(&finfo->gid);
}

void		copy_info(t_info *finfo, t_info *args)
{
	int	i;

	i = -1;
	args->type = finfo->type;
	while (finfo->chm[++i])
		args->chm[i] = finfo->chm[i];
	args->nb_links = finfo->nb_links;
	args->uid = finfo->uid;
	args->gid = finfo->gid;
	args->size = finfo->size;
	args->blocks = finfo->blocks;
	args->date = finfo->date;
	args->stmtime = finfo->stmtime;
	args->name = finfo->name;
	args->namel = finfo->namel;
	args->liname = finfo->liname;
	args->args = finfo->args;
	args->opts = finfo->opts;
	args->stfile = finfo->stfile;
	args->testu = finfo->testu;
	args->path = finfo->path;
	args->pathn = finfo->pathn;
}

t_acv		init_opts(void)
{
	t_acv	opts;

	opts.l = 0;
	opts.t = 0;
	opts.r = 0;
	opts.ur = 0;
	opts.a = 0;
	opts.us = 0;
	opts.ug = 0;
	opts.ich = 0;
	return (opts);
}

t_sizem		init_size(void)
{
	t_sizem		s;

	s.tot = 0;
	s.slinks = 0;
	s.huid = 0;
	s.hgid = 0;
	s.hsize = 0;
	s.name = 0;
	s.nl = 0;
	s.di = 0;
	s.lik = 0;
	return (s);
}
