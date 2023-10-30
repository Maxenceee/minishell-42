/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffreze <ffreze@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 16:26:12 by mgama             #+#    #+#             */
/*   Updated: 2023/10/30 15:37:21 by ffreze           ###   ########.fr       */
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
# include <readline/history.h>

# include "pcolors.h"

typedef struct s_data	t_data;

# define MS_STDIN 0
# define MS_STDOUT 1
# define MS_STDERR 2

# define MS_PIPE_ERROR "Pipe error"
# define MS_EXEVE_ERROR "Could not execute execve"
# define MS_OPEN_IN_ERROR "Infile"
# define MS_OPEN_OUT_ERROR "Outfile"
# define MS_FORK_ERROR "Fork"
# define MS_COMMAND_NOT_FOUND "Command not found"
# define MS_PERM_DENIED "permission denied"
# define MS_PROMPT_NAME "minishell$ "

# define BUFF_SIZE 4096
# define MS_ERROR 1
# define MS_SUCCESS 0

# include "../sources/utils/utils.h"
# include "../sources/builtins/builtins.h"
# include "../sources/parsing/parsing.h"

struct s_data {
	int				in;
	int				out;
	int				pipein;
	int 			pipeout;
	int				fdin;
	int				fdout;
	int				pid;
	char			**envp;
	int				exit;
	t_parsing_cmd	*parsing_cmd;
};

typedef struct	s_signal
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

void	exit_with_code(t_data *commands, int code);
void	exit_error_with_msg(t_data *commands, char *msg);

/* freeing */

#endif /* MINISHELL_H */