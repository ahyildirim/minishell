/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahyildir <ahyildir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 19:24:48 by ahyildir          #+#    #+#             */
/*   Updated: 2024/10/20 15:38:38 by ahyildir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	env_expander(char **dst, char *env, t_data *data)
{
	t_env	*tmp_env;

	tmp_env = data->env_table;
	while (tmp_env)
	{
		if (ft_strcmp(env, tmp_env->env_name))
		{
			ft_strjoin(dst, tmp_env->content);
			break ;
		}
		tmp_env = tmp_env->next;
	}
	data->last_output = 0;
}

static void	set_order(char **dst, char **src, t_data *data)
{
	if (**src == *DOLLAR)
		dollar_expander(dst, src, data);
	if (**src == *TILDA)
		env_expander(dst, "HOME", data);
}

static void	text_expander(t_lexlist *lex_table, int meta, t_data *data)
{
	char	*command;
	char	*expanded_text;
	int		flag;

	command = lex_table->content;
	expanded_text = NULL;
	flag = 0;
	while (*command)
	{
		if (*command == '\'' && (flag == 0 || flag == 1))
			flag ^= 1;
		else if (*command == '\"' && (flag == 0 || flag == 2))
			flag ^= 2;
		else if ((*command == *DOLLAR || *command == *TILDA) && (flag == 0
				|| flag == 2))
			set_order(&expanded_text, &command,
				data);
		else
			str_append_char(&expanded_text, *command);
		command++;
	}
	if (meta && expanded_text == NULL)
		return ;
	free(lex_table->content);
	lex_table->content = expanded_text;
}

static void	lexlist_value_expander(t_data *data)
{
	t_lexlist	*lex_table;

	lex_table = data->lex_table;
	while (lex_table)
	{
		if (lex_table->type == TEXT)
			text_expander(lex_table, 0, data);
		else if (lex_table->type != SIGN_PIPE && lex_table->next)
			if (lex_table->type != SIGN_DOUBLE_LESS)
				text_expander(lex_table, 1, data);
		lex_table = lex_table->next;
	}
}

void	expander(t_data *data)
{
	if (data->output == 2)
		return ;
	lexlist_value_expander(data);
	//clear_empty_lextables(data);
}
