# include "minishell.h"


		// if (tmp)
		// {
		// 	while (tmp[i])
		// 	{
		// 		printf ("%c\n", tmp[i]);
		// 		if (!k && ((tmp[i] < '0' && tmp[i] != '-' && tmp[i] != '$' && tmp[i] != ' ') || ((tmp[i] > '9' && tmp[i] < 'A') && tmp[i] != '>'
		// 			&& tmp[i] != '<') || (tmp[i] > 'Z' && tmp[i] < 'a') || (tmp[i] > 'z')))
		// 		{
		// 			if (tmp[i] == 39 || tmp[i] == 34)
		// 			{
		// 				r = tmp[i];
		// 				k = 1;
		// 			}
		// 			else
		// 			{
		// 				printf ("syntax error\n");
		// 				break ;
		// 			}
		// 		}
		// 		else if (k)
		// 		{
		// 			if (tmp[i] == r)
		// 				k = 0;
		// 		}
		// 		i++;
		// 	}
		// 	if (!tmp[i] && k)
		// 		printf ("syntax error\n");
		// 	else if (!tmp[i] && !k)
		// 	{
		// 		ft_s
		// 	}
		// }

char	*get_first(char	*str)
{
	int		i;
	char	*ret;

	i = 0;
	while (str && str[i] && str[i] != ' ')
		i++;
	ret = malloc (sizeof (char) * (i + 1));
	i = 0;
	while (str && str[i] && str[i] != ' ')
	{
		ret[i] = str[i];
		i++;
	}
	return (ret);
}

int	get_spaces(char *str)
{
	int		i;
	int		k;
	int		j;
	char	qu;

	j = 0;
	i = 0;
	k = 1;
	qu = 0;
	while (str[i])
	{
		if (str[i] == ' ' && i != 0 && str[i + 1] && k && str[i + 1] != 39 && str[i + 1] != 34)
			j++;
		if ((str[i] == 39 || str[i] == 34) && k)
		{
			k = 0;
			qu = str[i];
		}
		i++;
		if (!k && str[i] == qu)
		{
			j++;
			i++;
			k = 1;
		}
	}
	return (j + 1);
}

char	*get_arg(char *str, int i, int t)
{
	int		j;
	int		r;
	char	*ret;
	
	j = t;
	r = 0;
	ret = malloc (sizeof(char) * (i - t + 1));
	while (++j < i)
	{
		ret[r] = str[j];
		r++;
	}
	ret[r] = '\0';
	return (ret);
}

int	check_next_qu(char *str, char c, int i)
{
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*remove_qu(char *str)
{
	int		i;
	int		k;
	int		j;
	char	u;
	char	*tmp;

	k = 0;
	j = 0;
	i = 0;
	u = 0;
	tmp = malloc (ft_strlen(str) - 1);
	while (str[i])
	{
		if ((str[i] == 39 || str[i] == 34))
		{
			if (u && str[i] == u)
			{
				k++;
			}
			else if (!u && check_next_qu(str, str[i], i + 1))
			{
				u = str[i];
				k++;
			}
		}
		if (k < 2)
		{
			if (!u)
			{
				tmp[j] = str[i];
				j++;
			}
			else if (u && str[i] != u)
			{
				tmp[j] = str[i];
				j++;
			} 
		}
		if (k >= 2)
		{
			k = 0;
			u = 0;
		}
		i++;
	}
	tmp[j] = '\0';
	return (tmp);
}

char	**edit_qu(char **str)
{
	int		i;
	int		j;
	char	r;
	char	*tmp;

	i = 0;
	while (str[i])
	{
		j = 0;
		r = 0;
		while (str[i][j])
		{
			if ((str[i][j] == 34 || str[i][j] == 39) && !r)
				r = str[i][j];
			else if (r && str[i][j] == r)
			{
				tmp = cpy(tmp, str[i]);
				free (str[i]);
				str[i] = remove_qu(tmp);
				free (tmp);
				r = 0;
			}
			j++;
		}
		i++;
	}
	return (str);
}

char	*get_var_2(char *str, char **env)
{
	int		i;
	int		j;
	int		k;
	char	*ret;
	
	i = 0;
	j = 0;
	k = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], str, ft_strlen(str)))
			break ;
	}
	if (!env[i])
		return (NULL);
	while (env[i][j] != '=')
		j++;
	ret = malloc (sizeof (char) * (j + 1));
	while (env[i][j])
		ret[k++] = env[i][j++];
	ret[k] = '\0';
	return (ret);
}

char	*get_var(char *str, char **env, int j)
{
	char	*tmp;
	char	*ret;
	char	*tmp2;
	int		i;
	int		k;

	i = 0;
	tmp = malloc (sizeof (char) * (j + 1));
	while (str[i] && str[i] != '$')
	{
		tmp[i] = str[i];
		i++;
	}
	tmp[i] = '\0';
	k = i;
	while (str[++i])
		j++;
	ret = cpy(ret, tmp);
	tmp2 = malloc (sizeof (char) * (j + 1));
	i = 0;
	while (str[k])
		tmp2[i++] = str[k++];
	tmp2[k] = '\0';
	k = i;
	ret = ft_strjoin(ret, get_var_2(tmp2, env));
	return (ret);
}

char	**edit_var(char **ret, char **env)
{
	char	*tmp;
	char	*var;
	int		i;
	int		j;
	int		k;

	i = 0;
	k = 0;
	while (ret[i])
	{
		j = 0;
		while (ret[i][j])
		{
			if (k && ret[i][j] == 34)
				k = 0;
			if (ret[i][j] == 34 && check_next_qu(ret[i], 34, j) && !k)
				k = 1;
			if (k && ret[i][j] == '$')
			{
				tmp = cpy(tmp, ret[i]);
				free (ret[i]);
				ret[i] = get_var(ret[i], env, j);
			}
			j++;
		}
		i++;
	}
	return (ret);
}

char	**get_command(char **env)
{
	char	*command;
	char	*tmp;
	char	**ret;
	int		i;
	int		k;
	char	r;
	int		t;

	k = 0;
	i = 0;
	t = -1;
	r = 0;
	tmp = readline("minishell=>");
	if (!tmp)
		return (NULL);
	ret = malloc (sizeof(char*) * (get_spaces(tmp) + 2));
	while (tmp[i])
	{
		if (tmp[i] == 34 || tmp[i] == 39)
		{
			if (r && tmp[i] == r)
				r = 0;
			else
				r = tmp[i];
		}
		if (tmp[i] == ' ')
		{
			if (!r)
			{
				ret[k++] = get_arg(tmp, i, t);
			}
				t = i;
		}
		i++;
	}
	if (i - t - 1 > 0)
		ret[k++] = get_arg(tmp, i, t);
	ret[k] = NULL;
	ret = edit_var(ret, env);
	ret = edit_qu(ret);
	free (tmp);
	return (ret);
}

 int	main(int ac, char **av, char **env)
{
	t_main	i;
	int		r;
	int		k;
	char	**pr;
	char	*command;
	// char	**paths;
	char	*path;
	int		fd;

	fd = get_history();
	path = malloc (1);
	k = 2;
	while (k)
	{
		pr = get_command(env);
		add_history(pr[0]);
		write (fd, pr[0], ft_strlen(pr[0]));
		write (fd, "\n", 1);
		free (path);
		path = get_path(env, pr[0]);
		if (!path)
			printf ("minishell=> %s: command not found\n", pr[0]);
		r = fork();
		if (!r)
			execve(path, pr, NULL);
		else
			waitpid(r, NULL, 0);
		r = -1;
		while (pr[++r])
			free (pr[r]);
		free (pr);
		k--;
	}
	// if (!pr[0])
	// 	return (0);
	// r = 0;
	// while (pr[r])
	// {
	// 	printf ("%s\n", pr[r]);
	// 	r++;
	// }
	// add_history(command);
	// path = get_path(env, pr[0]);
	// printf ("%s\n", path);
	// pr = malloc (sizeof (char*) * 4);
	// pr[2] = """-l";
	// pr[3] = NULL;
	// pr[0] = "ls";
	// pr[1] = "-a";
	// pr[0] = "ls";
	// pr[1] = NULL;
	// write (fd, command, ft_strlen(command));
	// write (fd, "\n", 1);
	// pr = get_path(env, command);
	// r = -1;
	// while (pr[++r])
	// 	printf ("%s\n", pr[r]);
	r = -1;
	free (path);
	while (pr[++r])
		free (pr[r]);
	free (pr);
	// free (command);
}
