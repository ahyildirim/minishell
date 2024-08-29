#include "../../includes/minishell.h"

int	g_sig = 0;

void shell_loop(t_data *data)
{
	while (1)
	{
		data->input = readline("prompt #");
		lexer(data);
		if (data->input == NULL)
			break;
		if (data->input && *data->input)
		{
			add_history(data->input);
			print_lexer(data);
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
	data = malloc(sizeof(t_data));
	if (!data)
		return (ft_putstr_fd("Error: Memory allocation error\n", 2), EXIT_FAILURE);
	init_metachars(data);
	 //parse
	shell_loop(data);
	return (0);
}
