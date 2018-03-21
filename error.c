/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacaze <llacaze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 17:30:40 by llacaze           #+#    #+#             */
/*   Updated: 2018/01/24 15:43:20 by llacaze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		illopt(char *str)
{
	(void)str;
	write(2, "ls: illegal option -- -\nusage: ls [-GSalrt] [file ...]\n", 56);
	exit(EXIT_FAILURE);
}

char		*recuperr(char *str)
{
	int		i;
	char	*new_str;

	new_str = ft_strnew(2);
	i = 0;
	while (str[i])
		i++;
	while (str[i] != '/')
		i--;
	i++;
	new_str = ft_strjoin(new_str, str + i);
	return (new_str);
}
