/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strappendchar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahyildir <ahyildir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 19:25:48 by ahyildir          #+#    #+#             */
/*   Updated: 2024/10/05 19:25:49 by ahyildir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	str_append_char(char **dst, char c)
{
	size_t	len;
	char	*updated_str;
	char	*tmp_src;
	char	*tmp_dst;

	len = 0;
	if (*dst)
		len = strlen(*dst);
	updated_str = malloc(len + 2);
	if (!updated_str)
	{
		perror("malloc failed");
		exit(EXIT_FAILURE);
	}
	tmp_dst = updated_str;
	if (*dst)
	{
		tmp_src = *dst;
		while (*tmp_src)
			*tmp_dst++ = *tmp_src++;
		free(*dst);
	}
	*tmp_dst++ = c;
	*tmp_dst = '\0';
	*dst = updated_str;
}
