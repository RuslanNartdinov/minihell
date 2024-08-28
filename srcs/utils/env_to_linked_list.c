/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_linked_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbabayan <mbabayan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 11:48:03 by mbabayan          #+#    #+#             */
/*   Updated: 2024/08/28 12:00:07 by mbabayan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_env *create_env_node(char *env_str)
{
    t_env *new_node = (t_env *)malloc(sizeof(t_env));
    char *delimiter = strchr(env_str, '=');

    if (!new_node || !delimiter)
        return (NULL);
    new_node->name = strndup(env_str, delimiter - env_str);
    new_node->value = strdup(delimiter + 1);
    new_node->next = NULL;
    return (new_node);
}

t_env *init_env_list(char **env)
{
    t_env *head;
    t_env *current;
    t_env *new_node;
    
	head = NULL;
	current = NULL;
	new_node = NULL;
    while (*env)
    {
        new_node = create_env_node(*env);
        if (!new_node)
            return (NULL);
        
        if (!head)
            head = new_node;
        else
            current->next = new_node;
        
        current = new_node;
        env++;
    }
    return (head);
}
