#include "../../includes/minishell.h"

t_env *add_new_envnode(t_env **env_table, char *env)
{
	t_env	*last_node;
	char	*content;

	if(!(*env_table)) //İlk düğümse
	{
		*env_table = (t_env *)malloc(sizeof(t_env)); //Yer aç
		last_node = *env_table; //Son düğüme eşitle
	}
	else //İlk düğüm değil ise
	{
		last_node = *env_table; 
		while(last_node->next) //Sonuna kadar ilerlet
			last_node = last_node->next;
		last_node->next = (t_env *)malloc(sizeof(t_env)); //Next'i için yer aç, yani son eklenecek düğüm için yer aç.
		last_node = last_node->next; //En son eklediğin düğüme geç.
	}
	last_node->env_name = get_env_name(env); //env name'i doldur.
	content = env + ft_strlen(last_node->env_name); //contenti env + üstte doldurduğumuz env kadar ilerlet.
	if(*content == '=' && *(content + 1)) //Eğer ='e geldiysek ve bir sonraki karakteri var ise contenti o karakterler ile doldur.
		last_node->content = ft_strdup(content + 1); //Örneğin env VAR1=Hello World yaparsan env_name->VAR1, content->Hello World olur.
	else
		last_node->content = NULL;
	last_node->next = NULL;
	return (last_node);
}

void	fill_envs(t_data *data, char **env)
{
	while(*env && env) //Mesela bak burda gelen env hep boş olmayacak mı o yüzden bu döngüye hiç girmemesi gerekmez mi nasıl çalışıyor anlamadım
		add_new_envnode(&data->env_table, *(env++));
}
