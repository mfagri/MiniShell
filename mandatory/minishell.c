/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfagri <mfagri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 09:40:16 by aaitoual          #+#    #+#             */
/*   Updated: 2022/05/30 20:53:39 by mfagri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int	get_glo_2(int i, int j)
{
	static int	yo;

	if (i)
		yo = j;
	return (yo);
}

int	get_t(char *tmp, int t)
{
	while (tmp[++t])
	{
		if (tmp[t] == ' ')
			break ;
	}
	return (t);
}

void	edit_ret(char **str)
{
	int		i;
	int		j;
	int		k;
	char	*tmp;

	i = -1;
	j = -1;
	k = 0;
	while (str[++i])
	{
		if (!str[i][0])
			i++;
		if (!str[i])
			break ;
		tmp = cpy (tmp, str[i]);
		free (str[k]);
		str[k] = cpy (str[k], tmp);
		free (tmp);
		k++;
	}
	if (str[i - 1] && !str[i - 1][0])
		free (str[i - 1]);
	str[k] = NULL;
}

void	free_2(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free (str);
}

char **cpy_2(char **str)
{
	int		i;
	int		j;
	char	**ret;
	
	i = -1;
	while (str[++i])
		i = i;
	ret = malloc (sizeof (char *) * (i + 1));
	i = -1;
	while (str[++i])
		ret[i] = cpy(ret[i], str[i]);
	ret[i] = NULL;
	return (ret);
}

t_spl	get_command(char **env, int fd)
{
	char	*command;
	char	*tmp;
	char	*tmp3;
	char	*tmp2;
	char	***splited;
	char	**ret;
	char	**ret2;
	t_spl	comm;
	int		i;
	int		k;
	char	r;
	int		t;
	t_arg	ll;

	k = 0;
	i = 0;
	t = -1;
	r = '\0';
	
	tmp = readline("minishell=>");
	if (!tmp)
	{
		write (1, "\033[1A\033[11Cexit\n", 14);
		free (tmp);
		exit (0);
	}
	if (!ft_strncmp("(null)", tmp, ft_strlen(tmp)))
	{
		free (tmp);
		return (get_command(env, fd));
	}
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
	while (tmp[++i])
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
	}
	if (i - t - 1 > 0 && tmp[t + 1])
		ret[k++] = get_arg(tmp, i, t);
	free (tmp);
	ret[k] = NULL;
	if (!check_pr(ret))
	{
		printf ("%s\n", "syntax error");
		get_glo_2(1, 258);
		free_2(ret);
		return (get_command(env, fd));
	}
	ret2 = cpy_2(ret);
	edit_var(ret, env);
	edit_ret(ret);
	if (!ret[0])
	{
		free_2 (ret);
		free_2 (ret2);
		return (get_command(env, fd));
	}
	splited = split_pr(ret, 0, 0, '\0');
	free_2 (ret);
	edit_qu(splited, -1, 0, ll);
	comm.a_var = splited;
	edit_ret(ret2);
	comm.b_var = split_pr(ret2, 0, 0, '\0');
	free_2 (ret2);
	edit_qu(comm.b_var, -1, 0, ll);
	return (comm);
}

void	child_exec(char ***splited, char *path, int t, char **env)
{
	if (path && access(path, F_OK | X_OK))
		exit (126);
	if (execve(path, splited[t], env) == -1)
	{
		printf ("minishell: %s: command not found\n", splited[t][0]);
		exit (127);
	}
	exit (0);
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
	i = 0;
	u = 0;
	q = '\0';
	if (str[0][0] == ' ')
		i = 1;
	if ((str[i][0] == '|' || str[i][0] == '>' || str[i][0] == '<'))
		return (0);
	i = -1;
	while (str[++i])
	{
		j = -1;
		while (str[i][++j])
			q = get_q(str, i, j, q);
		if (!(ft_strncmp(str[i], "|", 1)) && !q)
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
			if ((str[i][j] == '<' && str[i][j + 1] == '<'  && str[i][j + 2] != '<') || (str[i][j] == '>' && str[i][j + 1] == '>'  && str[i][j + 2] != '>'))
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
	if (u)
		return (0);
	return (1);
}

// int	check_doll(char *str)
// {
// 	int	i;

// 	i = -1;
// 	while (str[++i])
// 		if (str[i] == '$')
// 			return (0);
// 	return (1);
// }

int	check_next(t_spl *comm, int t, int i)
{
	int	k;
	char ***splited = comm->a_var;
	char ***before = comm->b_var;

	k = 0;
	while (before[t][i] && ft_strcmp(before[t][i], "|"))
	{
		// printf ("before = %s\n", before[t][i]);
		// printf ("after = %s\n", splited[t][i]);
		if (!splited[t][i])
			return (0);
		if (ft_strcmp(splited[t][i], before[t][i]))
			return (0);
		i++;
	}
	return (1);
}

int	check_redi(t_spl *comm, int t, int stdin, int *fdd)
{
	int		i;
	int		j;
	int		k;
	char	**tmp;
	char	***splited = comm->a_var;
	char	***before = comm->b_var;
	char	*str;
	int		*fd;

	fd = malloc (sizeof (int) * 2);
	fd[0] = -2;
	fd[1] = -2;
	// i = -1;
	// while (splited[t][++i])
	// {
	// 	printf ("%s\n", splited[t][i]);
	// }
	i = -1;
	k = -1;
	while (splited[t][++i])
	{
		if (!(ft_strcmp(">", splited[t][i])))
		{
			if (splited[t][i + 1])
			{
				k = open (splited[t][i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
				if (k == -1)
				{
					printf ("minishell: %s: Permission denied\n", splited[t][i + 1]);
					return (0);
				}
			}
			else
			{
				printf ("minishell: %s: ambiguous redirect\n", before[t][i + 1]);
				return (0);
			}
			dup2 (k, 1);
			close (k);
		}
		if (!(ft_strcmp(">>", splited[t][i])))
		{
			if (splited[t][i + 1])
			{
				k = open (splited[t][i + 1], O_WRONLY, 0777);
				if (k == -1)
				{
					printf ("minishell: %s: Permission denied\n", splited[t][i + 1]);
					return (0);
				}
			}
			else
			{
				printf ("minishell: %s: ambiguous redirect\n", before[t][i + 1]);
				return (0);
			}
			dup2 (k, 1);
			close (k);
		}
		if (!(ft_strcmp("<<", splited[t][i])))
		{
			if (fd[0] == -2)
				pipe (fd);
			else
			{
				close (fd[0]);
				close (fd[1]);
				pipe (fd);
			}
			str = readline("> ");
			while (ft_strcmp(str, before[t][i + 1]))
			{
				if (!splited[t + 1])
				{
					write (fd[1], str, ft_strlen(str));
					write (fd[1], "\n", 1);
				}
				else
				{
					write (fdd[1], str, ft_strlen(str));
					write (fdd[1], "\n", 1);
				}
				free (str);
				str = readline("> ");
			}
			free (str);
		}
		if (!(ft_strcmp("<", splited[t][i])))
		{
			if (splited[t][i + 1])
			{
				if (access(splited[t][i + 1], F_OK))
				{
					printf ("minishell: %s: No such file or directory\n", splited[t][i + 1]);
					return (0);
				}
				k = open (splited[t][i + 1], O_RDONLY, 0777);
				if (k == -1)
				{
					printf ("minishell: %s: Permission denied\n", splited[t][i + 1]);
					return (0);
				}
			}
			else
			{
				printf ("minishell: %s: ambiguous redirect\n", before[t][i + 1]);
				return (0);
			}
		}
	}
	if (k != -1)
	{
		dup2 (k, 0);
		close (k);
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
			|| !(ft_strcmp(">>", splited[t][i])))
			i++;
		else if (!(ft_strcmp("<<", splited[t][i])))
		{
			if (check_next(comm, t, i + 1))
				i++;
		}
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
	if (fd[0] != -2 || fd[1] != -2)
	{
		dup2 (fd[0], 0);
		close (fd[1]);
		close (fd[0]);
	}
	free (fd);
	// printf ("%s\n", splited[t][0]);
	return (1);
}

int	check_command_utils(char **splited, char **env, int fd)
{
	if (!(ft_strcmp(splited[0], "pwd")))
	{
		if (fd)
			ft_pwd(splited);
		else
			exit (0);
	}
	else if (!(ft_strcmp(splited[0], "cd")))
	{
		if (fd)
			ft_cd(splited, env);
		else
			exit (0);
	}
	else if (!(ft_strcmp(splited[0], "env")))
	{
		if (fd)
			ft_print_env(env);
		else
			exit (0);
	}
	else if (!(ft_strcmp(splited[0], "exit")))
	{
		if (fd)
			ft_exit(splited, env);
		else
			exit (0);
	}
	else
		return (1);
	return (0);
}

int check_command(char **env, char **splited, int fd)
{
	if (!(strcmp(splited[0], "export")))
	{
		if (fd)
			ft_export(env, splited);
		else
			exit (0);
	}
	else if (!(strcmp(splited[0], "unset")))
	{
		if (fd)
			ft_unset(splited,env);
		else
			exit (0);
	}
	else if (!(ft_strcmp(splited[0], "echo")))
	{
		if (fd)
			ft_echo(splited);
		else
			exit (0);
	}
	else
		return (check_command_utils(splited, env, fd));
	return (0);
}

int	exec(int fd, char **env)
{
	int		*r;
	int		k;
	int		i;
	int		j = -1;
	int		t;
	int		stdout;
	int		stdin;
	int		fdd[2];
	char	***splited;
	char	***before;
	char	*path;
	t_spl	comm;

	path = malloc (1);
	comm = get_command(env, fd);
	splited = comm.a_var;
	before = comm.b_var;
	// i = -1;
	// while (splited[++i])
	// {
	// 	j = -1;
	// 	while (splited[i][++j])
	// 		printf ("----%s\n", splited[i][j]);
	// }
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
	k = -1;
	t = 0;
	while (splited[t])
	{
		k = 1;
		if (splited[t + 1])
			pipe(fdd);
		// if (!path && ft_strcmp("export", splited[t][0]) && ft_strcmp("unset", splited[t][0]))
		// {
		// 	printf ("minishell: %s: command not found\n", splited[t][0]);
		// 	get_glo(0);
		// 	if (!splited[t + 1])
		// 	{
		// 		t = 0;
		// 		pi = 127;
		// 		break ;
		// 	}
		// }
		r[t] = fork();
		k = check_redi(&comm, t, stdin, fdd);
		if (check_command(env, splited[t], r[t]) && !r[t])
		{
			if (splited[t + 1])
			{
				dup2(fdd[1], 1);
				close(fdd[0]);
				close(fdd[1]);
			}
			path = get_path(env, splited[t][0]);
			if (k)
				child_exec(splited, path, t, env);
			exit (1);
		}
		dup2(stdin, 0);
		dup2(stdout, 1);
		k = -1;
		if (splited[t + 1])
		{
			dup2(fdd[0], 0);
			close(fdd[0]);
			close(fdd[1]);
		}
		else
			dup2(stdin, 0);
		t++;
	}
	r[t] = '\0';
	while (--t != -1)
		waitpid(r[t], &k, 0);
	if (WIFSIGNALED(k))
		get_glo_2(1, k + 128);
	else if (WEXITSTATUS(k))
		get_glo_2(1, k / 128 / 2);
	if (k >= 25600)
		get_glo_2(1, (k * 100) / 25600);
	k = -1;
	while (splited[++k])
		free_2 (splited[k]);
	free (splited);
	k = -1;
	while (before[++k])
		free_2 (before[k]);
	free (before);
	// dup2(stdout, 1);
	// dup2(stdin, 0);
	close (stdout);
	close (stdin);
	free (r);
	// k = -1;
	return (1);
}

void	get_env(char **env)
{
	int		i;
	char	*tmp;
	char	*tmp2;
	int		k;
	char	*t;

	i = -1;
	while(env[++i])
	{
		if (!ft_strncmp("SHLVL=", env[i], 6))
		{
			tmp = cpy (tmp, "SHLVL=");
			t = ft_strrchr(env[i], '=');
			t++;
			t = ft_itoa(atoi(t) + 1);
			tmp = ft_strjoin(tmp, t);
			free (t);
			env[i] = cpy (env[i], tmp);
			free (tmp);
		}
		else
			env[i] = cpy (env[i], env[i]);
	}
	env[i] = NULL;
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
	int		r;
	int k;
	char	**pr;
	char	*command;
	char	*path;
	int		fd;
	//struct termios terminal2;

	rl_catch_signals = 0;
	path = malloc (1);
	fd = get_history();
	get_env(env);
	//terminal2 = remove_ctlc();
	signal(SIGINT, ft_sig);
	signal(SIGQUIT,ft_sig);
	// k = exec(fd, env, terminal2);
	k = 0;
	while (k != -2)
	{
		//g_globle.i = 0;
		get_glo(0);
		k = exec(fd, env);
	}
	if(k == 0)
	{
		//tcsetattr(STDIN_FILENO, TCSANOW, &terminal2);
		exit(0);
	}
	r = -1;
	while (env[++r])
		free (env[r]);
	free (path);
}
