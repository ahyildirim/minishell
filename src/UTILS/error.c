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

int	print_lex_error(t_lexlist *lex_table)
{
	print_error("-bash: syntax error near unexpected token '", lex_table->content, "'\n");
	//TODO
	return (0);
}