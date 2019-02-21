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
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

static t_list	*get_file(int fd, t_list **file)
{
	t_list	*temp;

	temp = *file;
	while (temp)
	{
		if (temp->content_size == (size_t)fd)
			return (temp);
		temp = temp->next;
	}
	temp = ft_lstnew("", 1);
	temp->content_size = fd;
	ft_lstadd(file, temp);
	temp = *file;
	return (temp);
}

static int		ft_read(int fd, char *buf, t_list *current)
{
	char	*temp;
	int		ret;

	ret = 1;
	while (ret > 0)
	{
		ret = read(fd, buf, BUFF_SIZE);
		buf[ret] = '\0';
		temp = current->content;
		current->content = ft_strjoin(current->content, buf);
		free(temp);
		if (ft_strchr(current->content, '\n'))
			break ;
	}
	return (ret);
}

int				get_next_line(const int fd, char **line)
{
	int				ret;
	char			buf[BUFF_SIZE + 1];
	static t_list	*file;
	t_list			*current;
	char			*temp;

	if (line == NULL || fd < 0 || read(fd, buf, 0) < 0)
		return (-1);
	current = get_file(fd, &file);
	ret = ft_read(fd, buf, current);
	if (ret < BUFF_SIZE && !ft_strlen(current->content))
		return (0);
	*line = ft_strdup(current->content);
	if (ft_strchr(*line, '\n') != NULL)
		*ft_strchr(*line, '\n') = '\0';
	if (ft_strlen(*line) < ft_strlen(current->content))
	{
		temp = current->content;
		current->content = ft_strdup(current->content + ft_strlen(*line) + 1);
		free(temp);
	}
	else
		ft_strclr(current->content);
	return (1);
}

int		main(void)
{
	int fd;
	int fd2;
	fd = open("gnl3_3.txt", O_RDONLY);
	fd2 = open("testt2.txt", O_RDONLY);
	char *line;
	int i = 0;
	while (get_next_line(fd, &line))
	{
		ft_putendl(line);
		free(line);
		i++;
		if (i == 2)
			break ;
	}
	i = 0;
	while (get_next_line(fd2, &line))
	{
		ft_putendl(line);
		free(line);
		i++;
		if (i == 2)
			break;
	}
	i = 0;
	while (get_next_line(fd, &line))
	{
		ft_putendl(line);
		free(line);
		i++;
		if (i == 2)
			break ;
	}
}
