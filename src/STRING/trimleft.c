/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trimleft.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahyildir <ahyildir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 19:25:51 by ahyildir          #+#    #+#             */
/*   Updated: 2024/10/05 19:25:52 by ahyildir         ###   ########.fr       */
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
	if (!*command || is_all_space(*command))
		return (-1);
	while (**command == 32 || **command == '\t') 
	{
		len++;
		(*command)++;
	}
	return (len);
}
