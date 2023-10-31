/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 16:26:12 by mgama             #+#    #+#             */
/*   Updated: 2023/10/31 15:19:54 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <dirent.h>
# include <sys/wait.h>
# include <limits.h>
# include <errno.h>
# include <signal.h>
# include <readline/readline.h>

# include "pcolors.h"

# include "../sources/builtins/builtins.h"
# include "../sources/env/env.h"
# include "../sources/utils/utils.h"

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define PIPE_ERROR "Pipe error"
# define EXEVE_ERROR "Could not execute execve"
# define OPEN_IN_ERROR "Infile"
# define OPEN_OUT_ERROR "Outfile"
# define FORK_ERROR "Fork"
# define COMMAND_NOT_FOUND "Command not found"
# define PERM_DENIED "permission denied"
# define MS_ERROR_MSG "Error: Could not allocate memory.\n"

# define MS_SUCCES 0
# define MS_ERROR 1
# define MS_NO_ERROR 2

# define BUFF_SIZE 4096
# define ERROR 1
# define SUCCESS 0

struct s_data
{
	int				in;
	int				out;
	int				pipein;
	int				pipeout;
	int				fdin;
	int				fdout;
	int				pid;
	int				exit;
	t_env_element	*env;
};

typedef struct s_signal
{
	int				sigint;
	int				sigquit;
	int				exit_status;
	pid_t			pid;
}				t_signal;

/**
 * main
 * 
 */

/* signal */

/**
 * exec
 * 
 */

/* pipes */

void	create_pipes(t_data *commands);
void	close_pipes(t_data *commands);
int		dup2_fdinout(int fdin, int fdout);

/* process */

void	fork_processes(t_data *commands);
void	process_child(t_data *commands, int idx);
int		open_fdinout(int idx, t_data *c);
int		execcmd(char **command, char *envp[]);

/**
 * parsing
 * 
 */

/* parsing */

char	*parse_env(char *envp[], char *cmd);

/**
 * tools
 * 
 */

/* fds */

void	close_fds(t_data *minishell);
void	reset_fds(t_data *minishell);

/**
 * exits
 * 
 */

/* exit */

void	free_minishell(t_data *minishell);

/* freeing */

#endif /* MINISHELL_H */