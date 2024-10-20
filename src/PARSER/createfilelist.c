/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   createfilelist.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahyildir <ahyildir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 19:25:36 by ahyildir          #+#    #+#             */
/*   Updated: 2024/10/05 19:25:37 by ahyildir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_filelist	*add_filelist_node(t_filelist **file_list, char *file_name,
		char *meta_char)
{
	t_filelist	*tmp;

	if (!file_name || !meta_char)
		return (NULL);
	if (!*file_list)
	{
		*file_list = (t_filelist *)malloc(sizeof(t_filelist));
		tmp = *file_list;
	}
	else
	{
		tmp = *file_list;
		while (tmp && tmp->next)
			tmp = tmp->next;
		tmp->next = (t_filelist *)malloc(sizeof(t_filelist));
		tmp = tmp->next;
	}
	tmp->fd = 0;
	tmp->file_name = file_name;
	tmp->meta_char = meta_char;
	tmp->next = NULL;
	return (tmp);
}

int	create_filelist(t_cmdlist *cmd_table, t_lexlist **lex_table, t_data *data)
{
	char		*meta_char;
	char		*file_name;
	t_filelist	*temp_filelist;

	if (!cmd_table || !lex_table || !(*lex_table))
		return (0);
	if ((*lex_table)->type == TEXT)
		return (0);
	meta_char = is_meta_char((*lex_table)->content, data);
	file_name = NULL;
	if ((*lex_table)->next)
		file_name = (*lex_table)->next->content;
	if (*meta_char != *PIPE)
	{
		temp_filelist = add_filelist_node(&(cmd_table->files), file_name,
				meta_char);
		if (!temp_filelist)
			return (0);
		if (*lex_table)
			temp_filelist->meta_char = (*lex_table)->content;
	}
	*lex_table = (*lex_table)->next;
	if (*lex_table)
		*lex_table = (*lex_table)->next;
	return (1);
}
