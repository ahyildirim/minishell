/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: euc <euc@student.42istanbul.com.tr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 19:27:45 by euc               #+#    #+#             */
/*   Updated: 2024/10/05 19:27:46 by euc              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_metachars(t_data *data)
{
	char	**meta_chars;

	meta_chars = (char **)malloc(sizeof(char *) * (METACHAR_NUM + 1));
	data->metachars = meta_chars;
	*(meta_chars++) = ft_strdup(DOUBLE_GREAT);
	*(meta_chars++) = ft_strdup(DOUBLE_LESS);
	*(meta_chars++) = ft_strdup(SINGLE_LESS);
	*(meta_chars++) = ft_strdup(SINGLE_GREAT);
	*(meta_chars++) = ft_strdup(PIPE);
	*(meta_chars++) = NULL;
}

void	init_data(t_data *data)
{
	data->input = NULL;
	data->is_reading = 0;
	data->last_output = 0;
	data->output = 0;
	data->main_pid = 0;
	data->heradoc_fd = -1;
	data->cnt_pipe = 0;
	data->env_table = NULL;
	data->cmd_table = NULL;
	data->lex_table = NULL;
	init_metachars(data);
}
