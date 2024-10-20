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

#include <unistd.h>

size_t	trim_left_spaces(char **command)
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
