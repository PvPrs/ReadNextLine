/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strmapi.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dvan-boc <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/18 15:13:50 by dvan-boc      #+#    #+#                 */
/*   Updated: 2019/01/18 15:13:51 by dvan-boc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char		*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*str;
	int		index;

	index = 0;
	if (!s)
		return (NULL);
	str = (char *)malloc(ft_strlen(s) * sizeof(char) + 1);
	if (!str)
		return (NULL);
	while (s[index])
	{
		str[index] = f((unsigned int)index, s[index]);
		index++;
	}
	str[index] = '\0';
	return (str);
}
