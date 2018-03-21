/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacaze <llacaze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 11:05:57 by llacaze           #+#    #+#             */
/*   Updated: 2018/01/25 16:49:19 by llacaze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <dirent.h>
# include "libft/includes/libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <pwd.h>
# include <grp.h>
# include <uuid/uuid.h>
# include <time.h>
# include <sys/xattr.h>
# include <sys/ioctl.h>
# include <errno.h>

# define O(s) (s == '-')
# define OPL(s) (s == 'l')
# define OPT(s) (s == 't')
# define OPR(s) (s == 'r')
# define OGR(s) (s == 'R')
# define OPA(s) (s == 'a')
# define OGS(s) (s == 'S')
# define OGG(s) (s == 'G')
# define ONE(s) (s == '1')

typedef struct		s_acv
{
	int				ac;
	char			**av;
	struct s_info	**first;
	int				ich;
	int				l;
	int				t;
	int				r;
	int				us;
	int				a;
	int				ur;
	int				on;
	int				ug;
	int				pos;
	char			*opts;
	int				stfile;
}					t_acv;

typedef struct		s_sizem
{
	int				slinks;
	size_t			huid;
	size_t			hgid;
	int				hsize;
	int				tot;
	int				nl;
	int				lik;
	int				di;
	size_t			name;
}					t_sizem;

typedef struct		s_info
{
	struct s_info	*prev;
	char			type;
	char			chm[10];
	nlink_t			nb_links;
	char			*uid;
	char			*gid;
	int				size;
	int				blocks;
	char			*date;
	char			atime[13];
	char			crtime[13];
	int				stmtime;
	char			*name;
	char			*namel;
	char			*liname;
	char			*args;
	char			*opts;
	int				stfile;
	int				testu;
	char			fin[250];
	char			*path;
	char			*pathn;
	struct s_info	*next;
}					t_info;

t_info				*check_type(struct stat fstat, t_info *finfo);
t_info				*check_protection_links(struct stat fstat,
							t_info *finfo, t_acv a);
t_info				*check_owner_size(struct stat fstat, t_info *finfo);
t_info				*check_date_name(struct stat fstat, t_info *finfo);
t_info				*init_info(void);
t_info				*refresh_info(t_info *finfo);
t_acv				init_opts(void);
t_info				*go_begin(t_info *finfo);
t_info				*ft_stat(struct stat fstat, t_info *finfo, t_acv a);
void				ft_recup(t_acv a);
t_info				*odir(t_info *finfo, t_acv a, char *path);
void				oodir(t_acv a, char *path, t_info *args);
char				*pather(struct dirent *sd, char *av);
t_acv				check_options(t_acv a);
t_acv				opts(t_acv a);
t_info				*afficher(t_info *finfo, t_acv a);
void				ft_disp(t_info *finfo, int i, t_acv a, t_sizem s);
t_info				*ft_swap_double(t_info *s1, t_info *s2, t_info **finfo);
void				display(t_info *finfo, t_acv a, int i);
t_info				*sort_options(t_info *head, t_acv a);
void				the_test(t_info *head, t_acv a, int i);
t_info				*sort_args(t_acv a);
t_info				*recup_names(t_acv a);
t_info				*add_end(t_info *finfo, t_info *recursive);
t_sizem				sizemax(t_info *finfo, t_acv a, int i);
t_sizem				init_size(void);
void				reverse(t_info *finfo, t_acv a, int i);
t_info				*go_end(t_info *finfo);
t_info				*sort_name_insert(t_info **finfo);
void				color(t_info *finfo);
void				illopt(char *str);
void				disp_name(t_info *finfo, t_acv a);
char				*recuperr(char *str);
void				copy_info(t_info *finfo, t_info *args);
t_info				*sort_name(t_info *finfo);
void				free_info(t_info *finfo);
void				free_a(t_acv a);
void				norm_one_rec(t_info *args, t_acv a);
void				norm_one_aff(t_info *finfo, t_sizem s, t_acv a, int i);
void				norm_three_aff(t_info *finfo, t_acv a);
void				norm_in_main(t_info *finfo, t_sizem s);
char				*huid(t_info *finfo, t_sizem s);
char				*guid(t_info *finfo, t_sizem s);
char				*size(t_info *finfo, t_sizem s);
t_sizem				norm_sizem(t_info *finfo, t_acv a, t_sizem s, int i);
char				*norm_date(char *findate, char *date, char *tmp);
char				norm_perm_two(struct stat fstat, t_info *finfo);
char				norm_perm_five(struct stat fstat, t_info *finfo);
t_info				*norm_stat(struct stat fstat, t_info *finfo, t_acv a);
t_info				*sort_dargs(t_info *finfo);
t_info				*sort_sargs(t_info *finfo);
t_info				*sort_nargs(t_info *finfo, t_acv a);
t_info				*sort_dof(t_info *finfo, t_acv a);
t_info				*norm_fod(t_info *finfo, t_acv a, t_info *new_list);
t_info				*norm_dof(t_info *finfo, t_acv a, t_info *new_list);
void				norm_check_opt(int i, t_acv a);
void				free_info_prev(t_info *finfo);
t_info				*norm_recup(t_acv a, t_info *args);
void				norm_free(t_info *finfo);
void				norm_free_prev(t_info *finfo);
char				*slinks(t_info *finfo, t_sizem s);
char				*free_norm_opts(char *opts, char *str);

#endif
