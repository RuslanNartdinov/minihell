/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbabayan <mbabayan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 14:24:14 by mbabayan          #+#    #+#             */
/*   Updated: 2024/09/18 14:50:25 by mbabayan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_gnl(t_list **list)
{
	t_list	*temp;

	if (*list)
	{
		while (*list != NULL)
		{
			temp = *list;
			*list = (*list)->next;
			free(temp->content);
			free(temp);
		}
		*list = NULL;
	}
}

static void	add_to_save(t_list **list, char *new)
{
	t_list	*temp;
	t_list	*current;

	if (!ft_strlen(new))
		return ;
	temp = (t_list *)malloc(sizeof(t_list));
	if (!temp)
	{
		return ;
	}
	temp->content = ft_strdup(new);
	temp->next = NULL;
	if (*list == NULL)
		*list = temp;
	else
	{
		current = *list;
		while (current->next != NULL)
		{
			current = current->next;
		}
		current->next = temp;
	}
}

static int	check_lst_nl(t_list *list, char **cache)
{
	char	*string;
	int		iter;

	iter = 0;
	if (!list)
		return (0);
	while (list->next != NULL)
		list = list->next;
	string = ft_strdup(list->content);
	while (string[iter] != '\0')
	{
		if (string[iter] == '\n')
		{
			*cache = ft_strdup(string + iter + 1);
			string[iter + 1] = '\0';
			free(list->content);
			list->content = ft_strdup(string);
			free(string);
			return (1);
		}
		iter++;
	}
	free(string);
	return (0);
}

static void	populate_lst(t_list **list, int fd, char **cache)
{
	ssize_t	read_size;
	char	*str_buff;

	str_buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!str_buff)
		return ;
	while (check_lst_nl(*list, cache) == 0)
	{
		read_size = read(fd, str_buff, BUFFER_SIZE);
		if (read_size <= 0)
		{
			return (free(str_buff), free(*cache));
		}
		str_buff[read_size] = '\0';
		add_to_save(list, str_buff);
	}
	free(str_buff);
}

char	*get_next_line(int fd)
{
	static char	*cache = NULL;
	t_list		*line;
	char		*result;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE >= INT_MAX)
		return (NULL);
	if (cache != NULL)
	{
		if (read(fd, 0, 0) == -1)
		{
			free(cache);
			cache = NULL;
			return (cache);
		}
		add_to_save(&line, cache);
		free(cache);
		cache = NULL;
	}
	populate_lst(&line, fd, &cache);
	result = concatenate_list(&line);
	free_gnl(&line);
	return (result);
}
