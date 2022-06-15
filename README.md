# MiniShell

```
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
```
# CTL_C && CTL_D && CTL_\


Ctl_c:
       
       rl_on_new_lin();          Tell the update functions that we have moved onto a new (empty) line.
       
       rl_replace_line("",0);      Clears the current prompt.
       
       rl_redisplay();            Redisplays the prompt.
      

Ctl_d:

	just write(1,”\033[1A\033[11Cexite”,14);.
        Results => (<prompt> exit) in the same line.
	    \033: control the cursor.
        \033[{N}A: Move your cursor up N lines.
        \033[{N}C: Move the cursor forward N columns

Ctl_\:

	just return ;

```
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

```
The function “get_glo” is a function to simulate a global variable :
If i == 0 j be 0 else i == 1 j be 1 else the function returns the value stored in the static variable.
Why we need this function:
If we’re in child process and click “CTL_C” the program print tow prompt (“minishell=>minushell=>”),
so we go to the child process and give the function “get_glo” a 1,
In this case he’s not going to get into the conduction of “SIGINT”,and he's write a new line,
And if we aren't in the child process we give the function 0 to get into the conduction if we click “CTL_C”.
^C: To solution this case you need “rl_catch_signals”.

In main program:
```
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
```
	
Rl_catch_signals: If non-zero, readline will install a signal handler for SIGWINCH
  				  that also attempts to call any calling application's SIGWINCH signal
  				  handler.  Note that the terminal is not cleaned up before the
  				  application's signal handler is called; use rl_cleanup_after_signal()
  				  to do that.
	
# Echo:

```
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
```
ft_check_n : functoin to skip the 'n' if int pr[1] n the fonction return one

```
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

```

For echo : if no argements flowed the echo just write new line if "echo -n" t
he program just print nothing whitout new line and ,
if "echo -n arguments" print argements whitout new line.

# Pwd:
```
void	ft_pwd(char **arg)
{
	char	s[1024];

	getcwd(s, sizeof(s));
	if (!s)
		return (ft_putstr_fd("pwd: not fond\n", 2));
	printf("%s\n", s);
}
```
The fonction "getcwd()" function shall place an absolute pathname of the current working directory in the array pointed to by buf, and return buf.
The pathname copied to the array shall contain no components that are symbolic links. The size argument is the size in bytes of the character array pointed to by the buf argument.
If buf is a null pointer, the behavior of getcwd() is unspecified.

# Env:

Environment variables hold information about our login session. 
They’re stored for the system shell used when we execute commands.
Usually, when we execute a command, we don’t manipulate the environment variables directly.
 However, sometimes, we want to change the system’s predefined environment variables for one or more commands.
if we go from bash to auther bash variable SHLVL must change bash 00 : shlvl=1 bash01 :shlvl=2 ,
if no shlvl in the environment and you run minishell in minishell you should update your shlvl to shlvl=1 ,
if you export a negative value to shlvl like shlvl=-99 your shlvl must be shlvl=0.


# Export:

export- command is one of the bash shell BUILTINS commands,
which means it is part of your shell. The export command is fairly simple
to use as it has straightforward syntax with only three available command options.
In general, the export command marks an environment variable to be exported with any newly forked 
child processes and thus it allows a child process to inherit all marked variables.

Some tests you should try in your export:

# TESTS:
```
minishell=>export
declare -x ANDROID_SDK_ROOT="/Users/mfagri/goinfre/devtools/Android/sdk"
declare -x APPS="/Users/mfagri/goinfre/apps"
declare -x DEV_TOOLS="/Users/mfagri/goinfre/devtools"
declare -x GRADLE_USER_HOME="/Users/mfagri/goinfre/devtools/gradle"
declare -x HOME="/Users/mfagri"
declare -x HOMEBREW_NO_AUTO_UPDATE="1"
declare -x JAVA_17_HOME="/Users/mfagri/goinfre/devtools/jdk/Contents/Home"
declare -x JAVA_HOME="/Users/mfagri/goinfre/devtools/jdk/Contents/Home"
declare -x LANG="en_US.UTF-8"
declare -x LESS="-R"
declare -x LOGNAME="mfagri"
declare -x LSCOLORS="Gxfxcxdxbxegedabagacad"
declare -x OLDPWD
declare -x PAGER="less"
declare -x PWD="/Users/mfagri"
declare -x SHELL="/bin/zsh"
declare -x SHLVL="2"
declare -x SSH_AUTH_SOCK="/private/tmp/com.apple.launchd.HaWj0mmtOE/Listeners"
declare -x TERM="xterm-256color"
declare -x TERM_PROGRAM="Apple_Terminal"
declare -x TERM_PROGRAM_VERSION="433"
declare -x TMPDIR="/var/folders/zz/zyxvpxvq6csfxvn_n000ccsr00336f/T/"
declare -x USER="mfagri"
declare -x XPC_FLAGS="0x0"
declare -x XPC_SERVICE_NAME="0"
declare -x ZSH="/Users/mfagri/.oh-my-zsh"
declare -x _="/bin/bash"
```
```
minishell=>export a
minishell=>export | grep a
declare -x a
minishell=>env | grep a 
(nothing)
minishell=>export a=b
minishell=>export | grep a
declare -x a="b"
minishell=>env | grep a
a="b"
minishell=>export a+=b
result : declare -x a="bb"
minishell=>export a 
result : a="bb"
minishell=>export +=a || <!@#$%^&*()>
minishell : export: `+=a': not a valid identifier
minishell=>export b==============n;
result : b="=========n"
```
	
# Unset:

unset command to delete the variables during program execution.
It can remove both functions and shell variables.

try export a && export aa && export aaa && export aaaa.
try to unset aa:
result :
```
declare -x a
declare -x aaa
declare -x aaaa
```
	
# cd:

The chdir command is a system function (system call) which is used to change the current working directory.
On some systems, this command is used as an alias for the shell command cd.
chdir changes the current working directory of the calling process to the directory specified in the path.

For cd you should use the 'chdir()' function .
 
int chdir(const char *path);

# Exemple:

```
#include<stdio.h>

// chdir function is declared
// inside this header
#include<unistd.h>
int main()
{
	char s[100];

	// printing current working directory/wp-content/uploads/chdir.png
	printf("%s\n", getcwd(s, 100));

	// using the command
	chdir("..");

	// printing current working directory
	printf("%s\n", getcwd(s, 100));

	// after chdir is executed
	return 0;
}

```

When you change the directory you should update your pwd and oldpwd in the environment.


# Exit:

https://linuxize.com/post/bash-exit
	
https://codefather.tech/blog/exit-bash-script/

And try to compare your exit function  with the bash :).

