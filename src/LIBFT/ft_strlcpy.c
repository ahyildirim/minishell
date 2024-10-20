/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahyildir <ahyildir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 19:25:30 by ahyildir          #+#    #+#             */
/*   Updated: 2024/10/05 19:25:31 by ahyildir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strlcpy(char *dst, char *src, int len)
{
	char	*str;
	char	*ret_str;
	int		i;

	if (!src || !len)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (ft_strlen(dst) + (len + 1)));
	ret_str = str;
	i = -1;
	while (dst && *dst)
		*(str++) = *(dst++);
	while (++i < len && src && *src)
		*(str++) = *(src++);
	*str = 0;
	return (ret_str);
}
