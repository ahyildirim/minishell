/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ismetachar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahyildir <ahyildir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 19:26:00 by ahyildir          #+#    #+#             */
/*   Updated: 2024/10/17 20:03:22 by ahyildir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*is_meta_char(char *command, t_data *data)
{
	char	**meta_chars;

	if (!command)
		return (NULL);
	meta_chars = data->metachars;
	while (meta_chars && *meta_chars)
	{
		if ((*command == **meta_chars && !*(*meta_chars + 1))
			|| (*command == **meta_chars && *(*meta_chars + 1) == *(command
					+ 1)))
			return (*meta_chars);
		meta_chars++;
	}
	return (NULL);
}
