#include "../../includes/minishell.h"

static void	init_metachars(void)
{
	char	**meta_chars;

	meta_chars = malloc(METACHAR_NUM + 1);
	g_data.metachars = meta_chars;
	*(meta_chars++) = ft_strdup(DOUBLE_GREAT);
	*(meta_chars++) = ft_strdup(DOUBLE_LESS);
	*(meta_chars++) = ft_strdup(SINGLE_LESS);
	*(meta_chars++) = ft_strdup(SINGLE_GREAT);
	*(meta_chars++) = ft_strdup(PIPE);
	*(meta_chars++) = NULL;
}