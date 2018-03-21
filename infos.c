/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infos.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacaze <llacaze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 11:03:32 by llacaze           #+#    #+#             */
/*   Updated: 2018/01/23 19:51:10 by llacaze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_info		*check_type(struct stat fstat, t_info *finfo)
{
	int		i;

	i = 0;
	S_ISBLK(fstat.st_mode) ? finfo->type = 'b' : i++;
	S_ISCHR(fstat.st_mode) ? finfo->type = 'c' : i++;
	S_ISDIR(fstat.st_mode) ? finfo->type = 'd' : i++;
	S_ISLNK(fstat.st_mode) ? finfo->type = 'l' : i++;
	S_ISSOCK(fstat.st_mode) ? finfo->type = 's' : i++;
	S_ISFIFO(fstat.st_mode) ? finfo->type = 'p' : i++;
	S_ISREG(fstat.st_mode) ? finfo->type = '-' : i++;
	if (i == 7 || i < 6)
		finfo->type = '?';
	return (finfo);
}

t_info		*check_protection_links(struct stat fstat, t_info *finfo, t_acv a)
{
	(void)a;
	finfo->chm[0] = ((fstat.st_mode & S_IRUSR) ? 'r' : '-');
	finfo->chm[1] = ((fstat.st_mode & S_IWUSR) ? 'w' : '-');
	finfo->chm[2] = norm_perm_two(fstat, finfo);
	finfo->chm[3] = ((fstat.st_mode & S_IRGRP) ? 'r' : '-');
	finfo->chm[4] = ((fstat.st_mode & S_IWGRP) ? 'w' : '-');
	finfo->chm[5] = norm_perm_five(fstat, finfo);
	finfo->chm[6] = ((fstat.st_mode & S_IROTH) ? 'r' : '-');
	finfo->chm[7] = ((fstat.st_mode & S_IWOTH) ? 'w' : '-');
	finfo->chm[8] = ((fstat.st_mode & S_IXOTH) ? 'x' : '-');
	if (fstat.st_mode & S_ISVTX)
		finfo->chm[8] = ((finfo->chm[8] == 'x') ? 't' : 'T');
	finfo->chm[9] = '\0';
	finfo->nb_links = fstat.st_nlink;
	finfo->blocks = fstat.st_blocks;
	return (finfo);
}

t_info		*check_owner_size(struct stat fstat, t_info *finfo)
{
	struct passwd	*uid;
	struct group	*gid;
	int				i;

	i = fstat.st_size;
	if ((uid = getpwuid(fstat.st_uid)))
		finfo->uid = ft_strdup(uid->pw_name);
	else
		finfo->uid = ft_strdup(ft_itoa(fstat.st_uid));
	if ((gid = getgrgid(fstat.st_gid)))
		finfo->gid = ft_strdup(gid->gr_name);
	else if (ft_itoa(fstat.st_gid))
		finfo->gid = ft_strdup(ft_itoa(fstat.st_gid));
	finfo->size = i;
	return (finfo);
}

t_info		*check_date_name(struct stat fstat, t_info *finfo)
{
	char			*date;
	time_t			sec;
	char			*tmp;

	time(&sec);
	free(finfo->date);
	tmp = ctime(&fstat.st_mtime);
	finfo->date = ft_strnew(ft_strlen(tmp));
	date = ctime(&fstat.st_mtime);
	finfo->stmtime = fstat.st_mtimespec.tv_sec;
	ft_memcpy(finfo->date, date + 4, 3);
	ft_memcpy(finfo->date + 3, date + 7, 3);
	if (((sec - fstat.st_mtimespec.tv_sec) / (60 * 60 * 24)) < 182.5 &&
		((sec - fstat.st_mtimespec.tv_sec) / (60 * 60 * 24)) > -182.5)
	{
		ft_memcpy(finfo->date + 6, date + 10, 6);
		finfo->date[12] = '\0';
	}
	else
		finfo->date = norm_date(finfo->date, date, tmp);
	return (finfo);
}

t_info		*ft_stat(struct stat fstat, t_info *finfo, t_acv a)
{
	char	*test;
	char	*verif;

	test = ft_strnew(5120);
	verif = ft_strnew(5120);
	finfo = norm_stat(fstat, finfo, a);
	if (finfo->type == 'l')
	{
		readlink(finfo->name, test, 2147483645);
		((ft_strcmp(verif, test) == 0) ?
			readlink(finfo->path, test, 2147483645) : 0);
		if (test != NULL)
		{
			finfo->namel = ft_strjoin(" -> ", test);
			finfo->namel[ft_strlen(finfo->namel)] = '\0';
			finfo->liname = ft_strjoin(finfo->liname, test);
			finfo->liname[ft_strlen(finfo->liname)] = '\0';
		}
	}
	free(verif);
	free(test);
	return (finfo);
}
