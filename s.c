
int	get_glo(int i)
{
	static int	j;

	if (i == 0)
		j = 0;
	else if (i == 1)
		j = 1;
	else
		return (j);
	return (j);
}

void	ft_sig(int signum)
{
	if (signum == SIGINT && !get_glo(2))
	{
		write (1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (signum == SIGQUIT && !get_glo(2))
		return ;
	else
		write(1, "\n", 1);
}

"
"Ctl_c":	rl_on_new_lin();          	//Tell the update functions that we have moved onto a new (empty) line
   		rl_replace_line("",0);      // Clears the current prompt
   		rl_redisplay();             // Redisplays the prompt"
"
"Ctl_d":   just write(1,”\033[1A\033[11Cexite”,14);
		 Results => (<prompt> exit) in the same line.
	  	 \033: control the cursor.
		 \033[{N}A: Move your cursor up N lines.
		 \033[{N}C: Move the cursor forward N columns"
"
"Ctl_\":	just return ;"


"The function “get_glo” is a function to simulate a global variable :
If i == 0 j be 0 else i == 1 j be 1 else the function returns the value stored in the static variable.
Why we need this function:
If we’re in child process and click “CTL_C” the program print tow prompt (“minishell=>minushell=>”),so we go to the child process and give the function “get_glo” a 1,
In this case he’s not going to get into the conduction of “SIGINT”,and he's write a new line,
And if we aren't in the child process we give the function 0 to get into the conduction if we click “CTL_C”.

^C: To solution this case you need “rl_catch_signals”:
In main program:"

int	main(int ac, char **av, char **env)
{
	int		fd;

	rl_catch_signals = 0;
	fd = get_history();
	get_env(env);
	signal(SIGINT, ft_sig);
	signal(SIGQUIT,ft_sig);
	while (1)
	{
		get_glo(0);
		exec(fd, env);
	}
}


"Rl_catch_signals: If non-zero, readline will install a signal handler for SIGWINCH
  				  that also attempts to call any calling application's SIGWINCH signal
  				  handler.  Note that the terminal is not cleaned up before the
  				  application's signal handler is called; use rl_cleanup_after_signal()
  				  to do that."

""Echo""

int	ft_check_n(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	if ((!s1 || !s2))
		return (1);
	if (s1[i] == '-')
	{
		i++;
		while (s1[i])
		{
			if (s1[i] != 'n')
				return (1);
			i++;
		}
		return (0);
	}
	return (1);
}

"ft_check_n fomctoin to skip the 'n' if int pr[1] n the fonction return one"

void	ft_echo(char **pr)
{
	int		i;
	int		n_option;

	i = 1;
	n_option = 0;
	while (pr[i] && ft_check_n(pr[i], "-n") == 0)
	{
		if (pr[i][1] == 'n')
			n_option = 1;
		if (pr[i][1] != 'n')
			break ;
		i++;
	}
	while (pr[i])
	{
		ft_putstr_fd(pr[i], 1);
		if (pr[i + 1] && pr[i][0] != '\0')
			write(1, " ", 1);
		i++;
	}
	if (n_option == 0)
		write(1, "\n", 1);
}



"for Echo : if no argements flowed the echo just write new line if "echo -n" t
he program just print nothing whitout new line and ,
if "echo -n arguments" print argements whitout new line"


""PWD"":

void	ft_pwd(char **arg)
{
	char	s[1024];

	getcwd(s, sizeof(s));
	if (!s[0])
		return (ft_putstr_fd("pwd: not fond\n", 2));
	printf("%s\n", s);
}

"The fonction "getcwd()" function shall place an absolute pathname of the current working directory in the array pointed to by buf, and return buf.
The pathname copied to the array shall contain no components that are symbolic links. The size argument is the size in bytes of the character array pointed to by the buf argument.
If buf is a null pointer, the behavior of getcwd() is unspecified. "

""ENV"":


"Env(Environment) is used to either print environment variables.
 It is also used to run a utility or command in a custom environment.
 In practice, env has another common use.
 It is often used by shell scripts to launch the correct interpreter.
 In this usage, the environment is typically not changed
 Env is a shell command for Unix and Unix-like operating systems.
 It is used to either print a list of environment variables or run another 
 utility in an altered environment without having to modify 
 the currently existing environment."

int	check_shlvl(char **env)
{
	int	i;

	i = 0;
	while(env[i])
	{
		if (!ft_strncmp("SHLVL=", env[i], ft_strlen("SHLVL=")))
			return (1);
		i++;
	}
	return (0);
	
}
void	shlvl_increment(char **env, int i)
{
	char	*tmp;
	int		k;
	char	*t;
	char	*s;

	tmp = cpy (tmp, "SHLVL=");
	t = ft_strrchr(env[i], '=');
	k = ft_atoi(++t) + 1;
	s = ft_itoa(k);
	tmp = ft_strjoin(tmp, s);
	free(s);
	env[i] = cpy (env[i], tmp);
	free(tmp);
}
void	get_env(char **env)
{
	int	i;

	i = -1;
	if(check_shlvl(env))
		while(env[++i])
		{
			if (!ft_strncmp("SHLVL=", env[i], 6))
			{
				shlvl_increment(env,i);
				i++;
			}
			env[i] = cpy (env[i], env[i]);
		}
	else
	{
		while(env[++i])
			env[i] = cpy (env[i], env[i]);
		env[i] = cpy (env[i], "SHLVL=1");
		env[i+1] = NULL;
	}
}


"If you run minishell inside minishell the variabele "SHLVL" must increment "{SHLVL+1}",
and if you unset SHLVL from env and ween you run env command the "SHLVL" be SHLVL=1."

""exit""

"arg[1] and arg [2] and arg[1] num" = bash: exit: too many arguments
"arg[1] and arg [2] and arg[1] alpha" = bash: exit: y: numeric argument required