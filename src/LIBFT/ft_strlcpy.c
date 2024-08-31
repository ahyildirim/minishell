#include "../../includes/minishell.h"

char	*ft_strlcpy(char *dst, char *src, int len)
{
	char	*str;
	char	*ret_str;
	int		i;

	if(!src || !len)
		return (NULL);
	if(!dst)
		return (NULL);
	str = (char *)malloc(ft_strlen(dst) + (len + 1));
	ret_str = str;
	i = -1;
	while(dst && *dst)
		*(str)++ = *(dst)++;
	while(++i < len && src && *src)
		*(str)++ = *(src)++;
	*str = '\0';
	return (ret_str);
}