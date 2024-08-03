#include "../../includes/minishell.h"

void	str_append_char(char **dst, char c)
{
	int		len;
	char	*updated_str;
	char	*tmp_str;
	char	*tmp_dst;

	len = ft_strlen(*dst) + 1;
	updated_str = malloc(len + 1);
	if(!updated_str)
		return ;
	tmp_str = updated_str;
	tmp_dst = *dst;
	while(tmp_dst && *tmp_dst)
		*(tmp_str++) = *(tmp_dst++);
	*(tmp_str++) = c;
	*(tmp_str++) = 0;
	if(*dst)
		free(*dst);
	*dst = updated_str;
}