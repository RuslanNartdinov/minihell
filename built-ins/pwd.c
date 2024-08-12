/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbabayan <mbabayan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 13:32:58 by mbabayan          #+#    #+#             */
/*   Updated: 2024/08/08 11:21:46 by mbabayan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/// Remove all the other header includes and keep
/// minishell header when implemented. 
int	pwd(void)
{
	char	str[1024];

	if (getcwd(str, sizeof(str)) != NULL)
	{
		printf("%s\n", str);
		return (0);
	}
	else
		return (1);
}
