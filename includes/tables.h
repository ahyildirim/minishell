/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tables.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: euc <euc@student.42istanbul.com.tr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 19:24:35 by ahyildir          #+#    #+#             */
/*   Updated: 2024/10/24 17:20:43 by euc              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TABLES_H
# define TABLES_H

typedef struct s_env
{
	char				*env_name;
	char				*content;
	struct s_env		*next;

}						t_env;

typedef struct s_filelist
{
	char				*file_name;
	char				*meta_char;
	int					fd;
	struct s_filelist	*next;
}						t_filelist;

typedef struct s_lexlist
{
	char				type;
	char				*content;
	struct s_lexlist	*next;
}						t_lexlist;

typedef struct s_cmdlist
{
	int					input_file;
	int					output_file;
	int					pid;
	char				*heradoc_values;
	char				*command;
	char				**path;
	t_filelist			*files;
	struct s_cmdlist	*next;
}						t_cmdlist;

typedef struct s_data
{
	char				*input;
	char				**metachars;
	int					is_reading;
	int					last_output;
	int					output;
	int					main_pid;
	int					heradoc_fd;
	t_lexlist			*lex_table;
	t_env				*env_table;
	t_cmdlist			*cmd_table;
}						t_data;

#endif
