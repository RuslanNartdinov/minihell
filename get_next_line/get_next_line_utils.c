/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbabayan <mbabayan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 14:24:04 by mbabayan          #+#    #+#             */
/*   Updated: 2024/09/18 14:50:25 by mbabayan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*malloc_result(t_list *list)
{
	int		total_sz;
	char	*res;

	total_sz = 0;
	while (list != NULL)
	{
		total_sz += ft_strlen(list->content);
		list = list->next;
	}
	res = (char *)malloc((total_sz + 1) * sizeof(char));
	return (res);
}

char	*concatenate_list(t_list **list)
{
	t_list	*current;
	char	*result;
	char	*temp;

	current = *list;
	if (!current)
		return (NULL);
	result = malloc_result(current);
	if (!result)
	{
		free_gnl(list);
		return (NULL);
	}
	result[0] = '\0';
	while (current != NULL)
	{
		temp = ft_strjoin(result, current->content);
		free(result);
		result = temp;
		if (!result)
			return (free_gnl(list), NULL);
		current = current->next;
	}
	free_gnl(list);
	return (result);
}
