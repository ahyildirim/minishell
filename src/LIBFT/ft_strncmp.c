/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahyildir <ahyildir@student.42istanbul.com  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 20:52:44 by ahyildir          #+#    #+#             */
/*   Updated: 2023/12/15 20:52:45 by ahyildir         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*xs1;
	unsigned char	*xs2;

	xs1 = (unsigned char *) s1;
	xs2 = (unsigned char *) s2;
	i = -1;
	while ((xs1[++i] || xs2[i]) && i < n)
		if (xs1[i] != xs2[i])
			return (xs1[i] - xs2[i]);
	return (0);
}
