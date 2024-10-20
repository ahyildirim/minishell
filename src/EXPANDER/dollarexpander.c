/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollarexpander.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahyildir <ahyildir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 19:24:44 by ahyildir          #+#    #+#             */
/*   Updated: 2024/10/17 17:04:32 by ahyildir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	handle_dollar_value(char **dst, char **src, t_data *data)
{
	int		len;
	char	*str;

	len = 0;
	str = (*src) + 1;
	while (*str != ' ' && *str && *str != *SINGLE_QUOTE && *str != *DOUBLE_QUOTE
		&& *str != '$')
	{
		len++;
		str++;
	}
	str = ft_strlcpy(NULL, (*src) + 1, len);
	env_expander(dst, str, data);
	free(str);
	*src += len;
}

static void	handle_single_dollar(char **dst)
{
	str_append_char(dst, *DOLLAR);
}

static void	handle_question_mark(char **dst, char **src, t_data *data)
{
	char	*ret;

	ret = ft_itoa(data->last_output);
	ft_strjoin(dst, ret);
	free(ret);
	(*src)++;
}

static void	handle_double_dollar(char **dst, char **src, t_data *data)
{
	char	*ret;

	ret = ft_itoa(data->main_pid);
	ft_strjoin(dst, ret);
	free(ret);
	(*src)++;
}

void	dollar_expander(char **dst, char **src, t_data *data)
{
	char	*str;

	str = (*src) + 1;
	if (*str == *DOLLAR)
		handle_double_dollar(dst, src, data);
	else if (*str == *QUSTION_MARK)
		handle_question_mark(dst, src, data);
	else if (*str == ' ' || *str == '\0' || *str == *DOUBLE_QUOTE
		|| *str == *SINGLE_QUOTE)
		handle_single_dollar(dst);
	else
		handle_dollar_value(dst, src, data);
}
