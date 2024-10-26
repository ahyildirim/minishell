/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trimleft.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: euc <euc@student.42istanbul.com.tr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 19:25:51 by ahyildir          #+#    #+#             */
/*   Updated: 2024/10/24 14:44:23 by euc              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

size_t	trim_left_spaces(char **command)
{
	size_t	len;

	len = 0;
	if (!*command)
		return (len);
	while (**command == 32 || **command == '\t')
	{
		len++;
		(*command)++;
	}
	return (len);
}
