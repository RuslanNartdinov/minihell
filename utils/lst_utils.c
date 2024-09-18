/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbabayan <mbabayan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 20:28:03 by mbabayan          #+#    #+#             */
/*   Updated: 2024/09/18 14:50:25 by mbabayan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_token	*ft_lstnew(char *word)
{
	t_token	*node;

	node = (t_token *) malloc(sizeof(t_token));
	if (!node)
		return (NULL);
	node->content = ft_strdup(word);
	node->next = NULL;
	node->type = 0;
	return (node);
}

t_token	*ft_lstlast(t_token *list)
{
	if (!list)
		return (NULL);
	while (list->next != NULL)
		list = list->next;
	return (list);
}

void	ft_lstadd_back(t_token **list, t_token *new)
{
	t_token	*temp;

	if (*list == NULL)
		*list = new;
	else
	{
		temp = ft_lstlast(*list);
		temp->next = new;
	}
}

void	ft_lstclear(t_shell *list)
{
	t_token	*temp;

	while (list->tokens)
	{
		temp = list->tokens;
		list->tokens = list->tokens->next;
		if (temp->content)
			free(temp->content);
		if (temp)
			free(temp);
		temp = NULL;
	}
	list->tokens = NULL;
}
