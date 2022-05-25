/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitoual <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 09:40:16 by aaitoual          #+#    #+#             */
/*   Updated: 2022/05/20 09:40:17 by aaitoual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"


int	get_t(char *tmp, int t)
{
	while (tmp[++t])
	{
		if (tmp[t] == ' ')
			break ;
	}
	return (t);
}

char	***get_command(char **env, int fd)
{
	char	*command;
	char	*tmp;
	char	*tmp3;
	char	*tmp2;
	char	***splited;
	char	**ret;
	int		i;
	int		k;
	char	r;
	int		t;

	k = 0;
	i = 0;
	t = -1;
	r = '\0';
	
	tmp = readline("minishell=>");
	if (!tmp)
	{
		write (1, "\033[1A\033[11Cexit\n", 14);
		exit (0);
	}
	if (!ft_strncmp("(null)", tmp, ft_strlen(tmp)))
		return (get_command(env, fd));
	add_history(tmp);
	if (tmp)
	{
		write (fd, "\n", 1);
		write (fd, tmp, ft_strlen(tmp));
	}
	ret = malloc (sizeof(char*) * (get_spaces(tmp) + 1));
	tmp2 = cpy(tmp2, tmp);
	free (tmp);
	tmp = sep(tmp2, 0, 0);
	free (tmp2);
	i = -1;
	i = 0;
	while (tmp[i])
	{
		r = get_q_1(tmp, i, r);
		if ((tmp[i] == ' ' && tmp[i + 1] != ' ' && tmp[i + 1]))
		{
			if (!r)
			{
				ret[k] = get_arg(tmp, i, t);
				k++;
				t = i;
				i++;
				r = get_q_1(tmp, i, r);
			}
		}
		if (!tmp[i])
			break ;
		i++;
	}
	if (i - t - 1 > 0 && tmp[t + 1])
		ret[k] = get_arg(tmp, i, t);
	ret[++k] = NULL;
	i = -1;
	ret = edit_var(ret, env);
	if (!check_pr(ret))
	{
		printf ("%s\n", "syntax error");
		return (get_command(env, fd));
	}
	splited = split_pr(ret, 0, 0, '\0');
	edit_qu(splited);
	k = -1;
	free (tmp);
	return (splited);
}

void	child_exec(char ***splited, char *path, int t, struct termios terminal2, char **env)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &terminal2);
	execve(path, splited[t], env);
	exit(0);
}

int	remove_path_2(char *str)
{
	if (str[0] == '/' || str[0] == '.')
		return (1);
	return (0);
}

char	*remove_pwd(char **env, int i)
{
	char	*ret;
	int		k;

	k = 3;
	ret = malloc (sizeof(char) * (ft_strlen(env[i]) - 2));
	while(env[i][++k])
	{
		ret[k - 4] = env[i][k];
	}
	ret[k - 4] = '\0';
	return (ret);
}

int	check_pr(char **str)
{
	int		i;
	int		j;
	char	q;
	int		u;

	i = -1;
	u = 0;
	q = '\0';
	while (str[++i])
	{
		j = -1;
		while (str[i][++j])
			q = get_q(str, i, j, q);
		if (!(ft_strncmp(str[i], "|", ft_strlen(str[i]))) && !q)
		{
			if (str[i + 1])
			{
				if (!(ft_strncmp(str[i + 1], "|", ft_strlen(str[i + 1]))))
					return (0);
			}
			else
				return (0);
		}
	}
	i = -1;
	q = '\0';
	while (str[++i])
	{
		j = -1;
		while (str[i][++j])
			q = get_q(str, i, j, q);
	}
	if (q)
		return (0);
	i = -1;
	u = 0;
	i = - 1;
	while (str[++i])
	{
		j = -1;
		while (str[i][++j])
		{
			if ((str[i][j] == '<' && str[i][j + 1] != '<') || (str[i][j] == '>' && str[i][j + 1] != '>'))
			{
				if (u)
					return (0);
				else
					u = 1;
			}
			if (str[i][j] != '|' && str[i][j] != '<' && str[i][j] != '>' && str[i][j] != '<' && str[i][j] && str[i][j] != ' ')
				u = 0;
		}
	}
	if (u)
		return (0);
	i = -1;
	while (str[++i])
	{
		j = -1;
		while (str[i][++j])
		{
			if ((str[i][j] == '<' && str[i][j + 1] != '<'  && str[i][j + 1] != '<') || (str[i][j] == '>' && str[i][j + 1] == '>'  && str[i][j + 1] != '>'))
			{
				if (u)
					return (0);
				else if (!u)
					u = 1;
			}
			if (str[i][j] != '|' && str[i][j] != '<' && str[i][j] != '>' && str[i][j] != '<' && str[i][j] && str[i][j] != ' ')
				u = 0;
		}
	}
	return (1);
}

int	check_redi(char ***splited, int t)
{
	int		i;
	int		j;
	int		k;
	char	**tmp;
	char	*str;
	int		*fd;

	fd = malloc (sizeof (int) * 2);
	i = -1;
	while (splited[t][++i])
	{
		if (!(ft_strcmp(">", splited[t][i])))
		{
			k = open (splited[t][i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
			dup2 (k, 1);
			close (k);
		}
		if (!(ft_strcmp(">>", splited[t][i])))
		{
			k = open (splited[t][i + 1], O_WRONLY | O_CREAT | O_APPEND, 0777);
			dup2 (k, 1);
			close (k);
		}
		if (!(ft_strcmp("<<", splited[t][i])))
		{
			pipe (fd);
			str = readline(">");
			while (ft_strcmp(str, splited[t][i + 1]))
			{
				write (fd[1], str, ft_strlen(str));
				write (fd[1], "\n", 1);
				free (str);
				str = readline(">");
			}
			free (str);
			dup2 (fd[0], 0);
			close (fd[0]);
			close (fd[1]);
		}
		if (!(ft_strcmp("<", splited[t][i])))
		{
			if (access(splited[t][i + 1], F_OK))
			{
				printf ("minishell: %s: No such file or directory\n", splited[t][i + 1]);
				return (0);
			}
			k = open (splited[t][i + 1], O_RDONLY , 0777);
			dup2 (k, 0);
			close (k);
		}
	}
	i = -1;
	k = -1;
	while (splited[t][++k])
		t = t;
	tmp = malloc (sizeof (char *) * (k + 1));
	k = 0;
	while (splited[t][++i])
	{
		if (!(ft_strcmp(">", splited[t][i]))
			|| !(ft_strcmp("<", splited[t][i]))
			|| !(ft_strcmp("<<", splited[t][i]))
			|| !(ft_strcmp(">>", splited[t][i])))
			i++;
		else
		{
			tmp[k] = cpy(tmp[k], splited[t][i]);
			k++;
		}
		if (!splited[t][i])
			break ;
	}
	tmp[k] = NULL;
	i = -1;
	while (splited[t][++i])
		free (splited[t][i]);
	splited[t] = tmp;
	i = -1;
	k = -1;
	return (1);
}

int check_command(char **env, char *path, char ***splited, int t, int *fdd, int stdout, int fd)
{
	if (fd)
	{
		if(!(strcmp(splited[t][0], "export")))
			ft_export(env,splited[t]);
		else if(!(strcmp(splited[t][0],"unset")))
			ft_unset(splited[t],env);
		else if(!(ft_strcmp(splited[t][0],"echo")))
			ft_echo(splited[t]);
		else if(!(ft_strcmp(splited[t][0],"pwd")))
			ft_pwd(splited[t]);
		else if(!(ft_strcmp(splited[t][0],"cd")))
			ft_cd(splited[t],env);
		else if(!(ft_strcmp(splited[t][0],"env")))
			ft_print_env(env);
		else
			return (1);
		return (0);
	}
	return (1);
}

int	exec(int fd, char **env, struct termios terminal2)
{
	int		*r;
	int		k;
	int		i;
	int		j = -1;
	int		t;
	int		stdout;
	int		stdin;
	int		pi;
	int		st = 1;
	char	**pr;
	int		fdd[2];
	char	***splited;
	char	*command;
	char	*path;

	path = malloc (1);
	splited = get_command(env, fd);
	pi = 1;
	stdin = dup(0);
	stdout = dup(1);
	k = -1;
	t = -1;
	k = -1;
	t = -1;
	t = -1;
	k = 0;
	while (splited[++t])
		k++;
	r = malloc (sizeof(int) * (k + 1));
	t = 0;
	while (splited[t])
	{
		k = 1;
		if (splited[pi])
			pipe(fdd);
		free (path);
		path = get_path(env, splited[t][0]);
		if (!path && ft_strcmp("export", splited[t][0]) && ft_strcmp("unset", splited[t][0]))
		{
			printf ("minishell: %s: command not found\n", splited[t][0]);
			get_glo(0);
			if (!splited[pi])
				break ;
			k = 0;
		}
		r[t] = fork();
		if (check_command(env, path, splited, t, fdd, stdout, r[t]) && !r[t])
		{
			if (!k)
				exit (0);
			if (splited[pi])
			{
				dup2(fdd[1], 1);
				close(fdd[0]);
				close(fdd[1]);
			}
			else
			{
				// dup2(stdin, 0);
				dup2(stdout, 1);
			}
			if (!check_redi(splited, t))
				return (1);
			k = -1;
			child_exec(splited, path, t, terminal2, env);
		}
		else if (!splited[pi])
		{
			get_glo(1);
			remove_ctlc();
		}
		k = -1;
		if (splited[pi] && k)
		{
			dup2(fdd[0], 0);
			close(fdd[0]);
			close(fdd[1]);
			dup2(stdout, 1);
		}
		else
			dup2(stdin, 0);
		t++;
		pi++;
	}
	while (--t != -1)
		waitpid(r[t], NULL, 0);
	r[t] = '\0';
	k = 0;
	t = 0;
	while (splited[k])
	{
		t = 0;
		while(splited[k][t])
		{
			free (splited[k][t]);
			t++;
		}
		free (splited[k]);
		k++;
	}
	free (splited);
	dup2(stdout, 1);
	dup2(stdin, 0);
	close (stdout);
	close (stdin);
	k = -1;
	// sleep(3);
	return (1);
}

void	get_env(char **env)
{
	int i;
	char	*tmp;
	int k;
	char *t;

	i = -1;
	while(env[++i])
	{
		if (!ft_strncmp("SHLVL=", env[i], 6))
		{
			tmp = cpy (tmp, "SHLVL=");
			t = ft_strrchr(env[i], '=');
			t++;
			k = atoi(t);
			k++;
			tmp = ft_strjoin(tmp, ft_itoa(k));
			env[i] = cpy (env[i], tmp);
		}
		env[i] = cpy (env[i], env[i]);
	}
}

char	*ft_strrchr(char *s, int c)
{
	int	i;

	i = ft_strlen(s);
	while (i && s[i] != (char)c)
		i--;
	if (s[i] == (char)c)
		return (&((char *)s)[i]);
	return (NULL);
}

int	main(int ac, char **av, char **env)
{
	t_main	i;
	int		r;
	int k;
	char	**pr;
	char	*command;
	char	*path;
	int		fd;
	struct termios terminal2;

	path = malloc (1);
	fd = get_history();
	get_env(env);
	terminal2 = remove_ctlc();
	signal(SIGINT, ft_sig);
	signal(SIGQUIT,ft_sig);
	r = 1;
	//waitpid(l, NULL, 0);
	k = 1;
	while (k)
	{
		//g_globle.i = 0;
		get_glo(0);
		k = exec(fd, env, terminal2);
	}
	if(k == 0)
	{
		tcsetattr(STDIN_FILENO, TCSANOW, &terminal2);
		exit(0);
	}
	free (path);
}
