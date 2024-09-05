#include "../../includes/minishell.h"

void	print_error(char *str1, char *str2, char *str3)
{
	if(str1)
		write(2, str1, ft_strlen(str1));
	if(str2)
		write(2, str2, ft_strlen(str2));
	if(str3)
		write(2, str3, ft_strlen(str3));
}

int	print_lex_error(t_lexlist *lex_table, t_data *data)
{
	print_error("-bash: syntax error near unexpected token '", lex_table->content, "'\n");
	data->output = 2;
	lexer_free_no_heradoc(lex_table, data);
	return (0);
}
int	quote_error(t_lexlist *lex_table, t_data *data)
{
	ft_putstr_fd("Syntax error with quotes.\n", 2);
	lexer_free_no_heradoc(lex_table, data);
	return 0;
}
