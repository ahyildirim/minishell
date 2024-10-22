/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trimleft.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: euc <euc@student.42istanbul.com.tr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 19:25:51 by ahyildir          #+#    #+#             */
/*   Updated: 2024/10/22 18:19:23 by euc              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_all_space(char *command)
{
	while (*command)
	{
		if (*command != 32 && *command != '\t')
			return (0);
		command++;
	}
	return (1);
}

int	trim_left_spaces(char **command)
{
	size_t	len;

	len = 0;
	if (!*command)
		return (len);
	while (**command == 32)
	{
		len++;
		(*command)++;
	}
	return (len);
}
