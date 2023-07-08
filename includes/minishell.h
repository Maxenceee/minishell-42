/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 16:26:12 by mgama             #+#    #+#             */
/*   Updated: 2023/07/08 10:46:57 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/wait.h>
# include <limits.h>
# include <errno.h>
# include <signal.h>

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

# define BUFF_SIZE 4096
# define ERROR 1
# define SUCCESS 0

typedef struct s_data {
	int		in;
	int		out;
	int		pipein;
	int 	pipeout;
	int		fdin;
	int		fdout;
	int		pid;
	char	**envp;
	int		exit;
}				t_data;

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
 * builtin
 * 
 */
/* cd */
/* echo */
/* env */
/* exit */
/* export */
/* pwd */
/* unset */


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