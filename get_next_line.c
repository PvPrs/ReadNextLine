/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dvan-boc <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/04 18:58:06 by dvan-boc      #+#    #+#                 */
/*   Updated: 2019/02/04 18:58:07 by dvan-boc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "stdio.h"
#include <fcntl.h>

/**
 *
 * @param fd File Descriptor
 * @param file File
 * @return t_list
 */
t_list	*get_file(int fd, t_list **file)
{
	t_list	*temp;

	temp = *file;
	while (temp)
	{
		if (temp->content_size == (size_t) fd)
			return (temp);
		temp = temp->next;
	}
	temp = ft_lstnew("\0", fd);
	ft_lstadd(file, temp);
	temp = *file;
	return (temp);
}


/*
** @param fd
** @param line
** @return	 1: Line has been read.
** @return	 0: Reading Completed.
** @return	-1: Error happened respectively.
*/
int		get_next_line(const int fd, char **line)
{
	char			buf[BUFF_SIZE + 1];
	int				ret;
	static t_list	*file;
	t_list			*current;

	if (!*line || fd < 0)
		return (-1);
	current = get_file(fd, &file);
	*line = ft_strnew(1);
	if (!*line)
		return (-1);
	while ((ret = read(fd, buf, BUFF_SIZE)))
	{
		buf[ret] = '\0';
		current->content = ft_strjoin(current->content, buf);
		if (!current->content)
			return (-1);
		if (ft_strchr(buf, '\n'))
			break ;
	}
	if (ret < BUFF_SIZE && !ft_strlen(current->content))
		return (0);
	printf("%s", ft_strcpy(*line, ft_strchr(current->content, '\0')));
	(ret < (int)ft_strlen(current->content)) ? current->content += (ret + 1) : ft_strclr(current->content);
	return (1);
}

int		main(void)
{
	int fd;
	char *line;

	fd = open("testt.txt", O_RDONLY);
	get_next_line(fd, &line);
	printf("%s", line);
}