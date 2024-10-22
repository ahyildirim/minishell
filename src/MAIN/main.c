/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahyildir <ahyildir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 19:27:48 by euc               #+#    #+#             */
/*   Updated: 2024/10/20 13:33:45 by ahyildir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		g_sig = 0;

void	minishell_func(t_data *data)
{
	add_history(data->input);
	lexer(data);
	expander(data);
	parser(data);
	//print_lexer(data);
	//print_parser(data);
	main_executor(data);
	free_loop(data);
}

void	shell_loop(t_data *data)
{
	while (1)
	{
		data->input = readline("minishell> ");
		if (data->input == NULL)
		{
			ft_putstr_fd("exit\n", 0);
			free_core(data);
			exit(0);
		}
		if (data->input && *data->input)
		{
			minishell_func(data);
		}
	}
}

int	main(int ac, char **av, char **env)
{
	t_data	*data;

	(void)ac;
	(void)av;
	handle_signal();
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (ft_putstr_fd("Error: Memory allocation error\n", 2),
			EXIT_FAILURE);
	init_data(data);
	fill_envs(data, env);
	shell_loop(data);
	free_core(data);
	return (0);
}
