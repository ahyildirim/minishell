#include "../../includes/minishell.h"

void	ft_strjoin(char **dst, char *src)
{
	char	*str;
	char	*tmp_str;
	char	*tmp_dst;
	size_t	len;

	if(!*dst && !src)
		return ;
	len = 0;
	if(*dst)
		len += ft_strlen(*dst);
	if(src)
		len += ft_strlen(src);
	str = (char *)malloc(len + 1);
	str[len] = 0;
	tmp_str = str;
	tmp_dst = *dst;
	while(tmp_dst && *tmp_dst)
		*(tmp_str++) = *(tmp_dst++);
	while(src && *src)
		*(tmp_str++) = *(src++);
	if(*dst)
		free(*dst);
	*dst = str;
}
