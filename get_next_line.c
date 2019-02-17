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

#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"

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
	temp = ft_lstnew("\0", 1);
	temp->content_size = fd;
	ft_lstadd(file, temp);
	temp = *file;
	return (temp);
}

static void		ft_read(int ret, int fd, char *buf, t_list *current)
{
	char *temp;

	while (ret)
	{
		ret = read(fd, buf, BUFF_SIZE);
		buf[ret] = '\0';
		temp = ft_strdup(current->content);
		current->content = ft_strjoin(current->content, buf);
		free(temp);
		if (ft_strchr(buf, '\n'))
			break ;
	}
}

int				get_next_line(const int fd, char **line)
{
	char			buf[BUFF_SIZE + 1];
	static t_list	*file;
	int ret;
	t_list			*current;

	if (!*line || fd < 0)
		return (-1);
	current = get_file(fd, &file);
	*line = ft_strnew(1);
	ret = 1;
	ft_read(ret, fd, buf, current);
	if (ret < BUFF_SIZE && !ft_strlen(current->content))
	{
		free(*line);
		return (0);
	}
	*ft_strchr(current->content, '\n') = '\0';
	*line = ft_strdup(current->content);
	current->content += (ft_strlen(current->content) + 1);
	free(*line);
	return (1);
}

int		main(void) {
	int fd;
//	int fd2;
	char *line;
	int x;
	int ret;

	fd = open("gnl1_3.txt", O_RDONLY);
//	fd2 = open("testt2.txt", O_RDONLY);
//	int i = 0;
	x = 0;
	while ((ret = get_next_line(fd, &line)) > 0) {
		ft_putendl(line);
		x++;
	}
	printf("x: %d", x);
//	while (1)
//	{
//
//	}
//	i = 0;
//	while (1) {
//		get_next_line(fd2, &line);
//		ft_putendl(line);
//		free(line);
//		i++;
//		if (i == 3)
//			break ;
//	}
}