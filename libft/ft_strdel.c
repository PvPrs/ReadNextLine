/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strdel.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dvan-boc <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/18 16:49:21 by dvan-boc      #+#    #+#                 */
/*   Updated: 2019/01/18 16:49:22 by dvan-boc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void		ft_strdel(char **as)
{
	if (!as)
		return ;
	free(*as);
	*as = NULL;
	return ;
}
