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
		k++;
	}
	str[k] = NULL;
	free (tmp);
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
		return (get_command(env, fd));
	}
	ret2 = cpy_2(ret);
	ret = edit_var(ret, env);
	edit_ret(ret);
	splited = split_pr(ret, 0, 0, '\0');
	i = -1;
	while (ret[++i])
		free (ret[i]);
	free (ret);
	edit_qu(splited, -1, 0, ll);
	comm.a_var = splited;
	edit_ret(ret2);
	comm.b_var = split_pr(ret2, 0, 0, '\0');
	i = -1;
	while (ret2[++i])
		free (ret2[i]);
	free (ret2);
	edit_qu(comm.b_var, -1, 0, ll);
	return (comm);
}

void	child_exec(char ***splited, char *path, int t, struct termios terminal2, char **env)
{
	if (!path)
		exit (127);
	// if (path && access(path, F_OK | X_OK))
	// 	exit (126);
	tcsetattr(STDIN_FILENO, TCSANOW, &terminal2);
	execve(path, splited[t], env);
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
	// while (str[++i])
	// 	printf ("-%s\n", str[i]);
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
	i = -1;
	while (splited[t][++i])
	{
		if (!(ft_strcmp(">", splited[t][i])))
		{
			if (splited[t][i + 1])
			{
				k = open (splited[t][i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
				if (k == -1)
					printf ("minishell: %s: No such file or directory\n", splited[t][i + 1]);
				return (0);
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
			k = open (splited[t][i + 1], O_WRONLY | O_CREAT | O_APPEND, 0777);
			dup2 (k, 1);
			close (k);
		}
		if (!(ft_strcmp("<<", splited[t][i])))
		{
			if (fd[0] == -2)
				pipe (fd);
			// printf ("--%s\n", before[t][i + 1]);
			// printf ("--%s\n", splited[t][i + 1]);
			str = readline("> ");
			while (ft_strcmp(str, before[t][i + 1]))
			{
				write (fd[1], str, ft_strlen(str));
				write (fd[1], "\n", 1);
				// write (fdd[1], str, ft_strlen(str));
				// write (fdd[1], "\n", 1);
				free (str);
				str = readline("> ");
			}
			free (str);
			dup2 (fd[0], 0);
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
			|| !(ft_strcmp(">>", splited[t][i])))
			i++;
		else if (!(ft_strcmp("<<", splited[t][i])))
		{
			if (!check_next(comm, t, i + 1))
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
		close (fd[1]);
		close (fd[0]);
	}
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
	char	***before;
	char	*command;
	char	*path;
	t_spl	comm;
	t_arg	hh;
	int		ret;

	path = malloc (1);
	comm = get_command(env, fd);
	splited = comm.a_var;
	before = comm.b_var;
	// pi = 1;
	// stdin = dup(0);
	// stdout = dup(1);
	// k = -1;
	// t = -1;
	// k = -1;
	// t = -1;
	// t = -1;
	// k = 0;
	// while (splited[++t])
	// 	k++;
	// r = malloc (sizeof(int) * (k + 1));
	// k = -1;
	// t = 0;
	// while (splited[t])
	// {
	// 	k = 1;
	// 	if (splited[pi])
	// 		pipe(fdd);
	// 	free (path);
	// 	path = get_path(env, splited[t][0]);
	// 	// if (!path && ft_strcmp("export", splited[t][0]) && ft_strcmp("unset", splited[t][0]))
	// 	// {
	// 	// 	printf ("minishell: %s: command not found\n", splited[t][0]);
	// 	// 	get_glo(0);
	// 	// 	if (!splited[t + 1])
	// 	// 	{
	// 	// 		t = 0;
	// 	// 		pi = 127;
	// 	// 		break ;
	// 	// 	}
	// 	// }
	// 	r[t] = fork();
	// 	if (check_command(env, splited[t], r[t]) && !r[t])
	// 	{
	// 		k = check_redi(&comm, t, stdin, fdd);
	// 		// if (!k)
	// 		// {
	// 		// 	dup2(stdout, 1);
	// 		// 	dup2(stdin, 0);
	// 		// 	// close (stdout);
	// 		// 	// close (stdin);
	// 		// }
	// 		if (splited[pi])
	// 		{
	// 			dup2(fdd[1], 1);
	// 			close(fdd[0]);
	// 			close(fdd[1]);
	// 		}
	// 		else
	// 		{
	// 			dup2(stdout, 1);
	// 			// close (stdout);
	// 			// close (stdin);
	// 		}
	// 		hh.stdout = stdout;
	// 		hh.k = t;
	// 		if (k)
	// 			child_exec(splited, path, t, terminal2, env);
	// 	}
	// 	else if (!splited[pi])
	// 	{
	// 		get_glo(1);
	// 		remove_ctlc();
	// 	}
	// 	k = -1;
	// 	if (splited[pi] && k)
	// 	{
	// 		dup2(fdd[0], 0);
	// 		close(fdd[0]);
	// 		close(fdd[1]);
	// 	}
	// 	else
	// 		dup2(stdin, 0);
	// 	t++;
	// 	pi++;
	// }
	// r[t] = '\0';
	// while (--t != -1)
	// 	waitpid(r[t], &pi, 0);
	// // printf ("--%d\n", pi);
	// if (WIFSIGNALED(pi))
	// 	get_glo_2(1, pi + 128);
	// else if (WEXITSTATUS(pi))
	// 	get_glo_2(1, pi / 128 / 2);
	// if (pi >= 25600)
	// 	get_glo_2(1, (pi * 100) / 25600);
	// // printf ("----%d\n", pi);
	// // 	pi = pi + 128;
	k = 0;
	// t = 0;
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
	k = 0;
	while (before[k])
	{
		t = 0;
		while(before[k][t])
		{
			free (before[k][t]);
			t++;
		}
		free (before[k]);
		k++;
	}
	free (before);
	// free (splited);
	// dup2(stdout, 1);
	// dup2(stdin, 0);
	// close (stdout);
	// close (stdin);
	if (path)
		free (path);
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
	struct termios terminal2;

	path = malloc (1);
	fd = get_history();
	get_env(env);
	terminal2 = remove_ctlc();
	signal(SIGINT, ft_sig);
	signal(SIGQUIT,ft_sig);
	k = exec(fd, env, terminal2);
	// k = 0;
	// while (k != -2)
	// {
	// 	//g_globle.i = 0;
	// 	get_glo(0);
	// 	k = exec(fd, env, terminal2);
	// }
	// if(k == 0)
	// {
	// 	tcsetattr(STDIN_FILENO, TCSANOW, &terminal2);
	// 	exit(0);
	// }
	r = -1;
	while (env[++r])
		free (env[r]);
	free (path);
}
