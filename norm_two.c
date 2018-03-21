/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm_two.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacaze <llacaze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 19:03:38 by llacaze           #+#    #+#             */
/*   Updated: 2018/01/25 16:00:23 by llacaze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char		*size(t_info *finfo, t_sizem s)
{
	char	*size;
	char	*tmpd;
	char	*tmpp;
	char	*tmp;
	int		i;

	tmpd = ft_itoa(s.hsize);
	size = ft_strnew(ft_strlen(tmpd) * 20);
	size = ft_memset(size, ' ', ft_strlen(tmpd));
	free(tmpd);
	tmpp = ft_itoa(finfo->size);
	size = ft_strcat(size, tmpp);
	i = ft_strlen(tmpp);
	free(tmpp);
	tmp = size + i;
	free(size);
	return (tmp);
}

t_sizem		norm_sizem(t_info *finfo, t_acv a, t_sizem s, int i)
{
	if (finfo->size > s.hsize)
		if (((a.a == 1) || (a.a == 0 && finfo->name[0] != '.')))
			s.hsize = finfo->size;
	if (ft_strlen(finfo->uid) > s.huid)
		if ((a.a == 1) || (a.a == 0 && finfo->name[0] != '.'))
			s.huid = ft_strlen(finfo->uid);
	if (ft_strlen(finfo->gid) > s.hgid)
		if (((a.a == 1) || (a.a == 0 && finfo->name[0] != '.')))
			s.hgid = ft_strlen(finfo->gid);
	if (finfo->nb_links > s.slinks)
		if ((a.a == 1 && ((i == 1) ? i == 1 : finfo->type != 'd')) ||
				(a.a == 0 && finfo->name[0] != '.' &&
				((i == 1) ? i = 1 : finfo->type != 'd')))
			s.slinks = finfo->nb_links;
	if ((a.a == 1) || (a.a == 0 && finfo->name[0] != '.'))
		s.tot = s.tot + finfo->blocks;
	if (ft_strlen(finfo->name) > s.name)
		if ((a.a == 1) || (a.a == 0 && finfo->name[0] != '.'))
			s.name = ft_strlen(finfo->name);
	return (s);
}

void		norm_in_main(t_info *finfo, t_sizem s)
{
	char	*str;

	ft_putchar(finfo->type);
	ft_putstr(finfo->chm);
	((listxattr(finfo->path, NULL, 500, XATTR_NOFOLLOW) > 0) ?
			ft_putstr("@ ") : ft_putstr("  "));
	str = slinks(finfo, s);
	ft_putstr(str);
	write(1, " ", 1);
	str = huid(finfo, s);
	ft_putstr(str);
	free(str);
	write(1, "  ", 2);
	str = guid(finfo, s);
	ft_putstr(str);
	free(str);
	write(1, "  ", 2);
	str = size(finfo, s);
	ft_putstr(str);
	write(1, " ", 1);
	ft_putstr(finfo->date);
	write(1, " ", 1);
}

char		*norm_date(char *findate, char *date, char *tmp)
{
	int		i;

	i = 19;
	findate[6] = ' ';
	while (date[i] == ' ')
		i++;
	if (ft_strlen(date + i) < 6)
		findate[7] = ' ';
	tmp = findate;
	tmp = ft_strjoin(findate, date + i);
	free(findate);
	findate = ft_strdup(tmp);
	free(tmp);
	findate[ft_strlen(findate) - 1] = '\0';
	return (findate);
}
