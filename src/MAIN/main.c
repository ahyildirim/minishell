#include "../../includes/minishell.h"

int	g_sig = 0;

void	minishell_func(t_data *data)
{
	add_history(data->input);
	lexer(data);
	expander(data);
	parser(data);
	//print_lexer(data);
	//print_parser(data);
	main_executor(data);
	//heredoc
	//free
	//execute
	
}

void shell_loop(t_data *data)
{
	while (1)
	{
		data->input = readline("minishell> ");
		
		if (data->input == NULL)
			break;
		if (data->input && *data->input)
		{
			minishell_func(data);
		}
	}
	
}

int main(int ac, char **av, char **env)
{
	t_data	*data;

	(void)ac;
	(void)av;
	(void)env;
	handle_signal();
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (ft_putstr_fd("Error: Memory allocation error\n", 2), EXIT_FAILURE);
	init_metachars(data);
	fill_envs(data, env);
	shell_loop(data);
	return (0);
}
