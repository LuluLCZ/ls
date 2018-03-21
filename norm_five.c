/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm_five.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacaze <llacaze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 16:44:45 by llacaze           #+#    #+#             */
/*   Updated: 2018/01/25 17:42:31 by llacaze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char		*free_norm_opts(char *opts, char *str)
{
	char	*tmp;

	if (str[0] == '-')
	{
		tmp = opts;
		opts = retry(str);
		tmp = NULL;
	}
	else
		free(str);
	return (opts);
}
