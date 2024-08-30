#include "../../includes/minishell.h"

static char	*get_env_content(char **envs, char *arg_name)
{
	char	*ptr;
	char	*temp_envs;
	int		len;

	len = 0;
	temp_envs = *envs;
	while(**envs && **envs != ':') // /usr/local/sbin:/usr/local/bin: örneğinde : gelene kadar yolun boyutunu alır.
	{
		len++;
		(*envs)++;
	}
	if(!len) //Eğeer iki nokta yoksa geçerli bir yol değildir ve NULL döndürür
		return (NULL);
	ptr = malloc(len + 1); //ptr için boyut kadar yer aç.
	ft_strlcpy(ptr, temp_envs, len + 1); //ptr'nin içine yolu kopyalar.
	str_append_char(&ptr, '/'); // :'dan sonraki / karakterini ekler.
	ft_strjoin(&ptr, arg_name); //Gelen komutu en sona ekler, örneğin ls yazdığımızı ele alalım; 
	//usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin:/usr/local/go/bin yolunu alır, sonuna / koyar ve ls komutunu yapıştırıp döndürür.
	if(**envs == ':') //eğer karkater : ise bir sonraki iterasyonun hatasız olması için atlamamız gerekir.
		(*envs)++;
	return (ptr);
}

static void	expand_env_content(char **cmd, char *content)
{
	char	*path; //Yolu tutmak için değişken

	while(content && *content)
	{
		path = get_env_content(&content, *cmd); //Bu fonksiyon ile olası yolu alırız.
		if(access(path, F_OK) == 0) //access fonksiyonu ile aldığımız yolun var olup olmadığını kontrol ederiz, çıktı 0 ise erişilebilir demektir yani öyle bir komut vardır.
		{
			free(*cmd);
			*cmd = path; //cmd içine path'ı yapıştır ve execute için hazır hale getir.
			return ;
		}
		free(path);
	}
}

void	cmd_expander(char **cmd, t_data *data)
{
	t_env *tmp_env;

	tmp_env = data->env_table; //Geçici bir env_table structı aç.
	while(tmp_env && *cmd && **cmd)
	{
		if(ft_strcmp("PATH", tmp_env->env_name)) //Eğer gelen env PATH ise
		{
			expand_env_content(cmd, tmp_env->content); //PATH ortam değişkenini kullanarak komutun hangi yolda olduğunu bulur ve cmd'ye atar.
			return;
		}
		tmp_env = tmp_env->next;
	}
}
