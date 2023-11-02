/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffreze <ffreze@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 16:26:12 by mgama             #+#    #+#             */
/*   Updated: 2023/11/02 03:35:29 by mgama            ###   ########.fr       */
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

# define MS_PROMPT_NAME			HEADER"minishell$ "RESET
# define MS_ERROR_PREFIX		"minishell: "
# define MS_PIPE_ERROR			MS_ERROR_PREFIX"Pipe error"
# define MS_EXEVE_ERROR			MS_ERROR_PREFIX"could not execute execve"
# define MS_OPEN_ERROR			MS_ERROR_PREFIX"could not open file "
# define MS_FORK_ERROR			MS_ERROR_PREFIX"fork"
# define MS_COMMAND_NOT_FOUND	MS_ERROR_PREFIX"command not found: "
# define MS_PERM_DENIED			MS_ERROR_PREFIX"permission denied"
# define MS_ALLOC_ERROR_MSG		"Error: could not allocate memory.\n"

# define BUFF_SIZE		4096
# define MS_SUCCESS		0
# define MS_ERROR		1
# define MS_NO_ERROR	2

# include "../sources/utils/utils.h"
# include "../sources/parsing/parsing.h"
# include "../sources/builtins/builtins.h"
# include "../sources/env/env.h"

typedef struct s_data	t_data;

struct s_data {
	int				in;
	int				out;
	int				pid;
	t_env_element	*env;
	// char			**envp;
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

void	close_pipes(t_parsing_cmd *cmd);
int		dup2_fdinout(int fdin, int fdout);

/* process */

int	fork_processes(t_data *minishell);

/**
 * parsing
 * 
 */

/* parsing */

// char	*parse_env(char *envp[], char *cmd);
char	*parse_env(t_data *ms, char *cmd);

/**
 * tools
 * 
 */

/**
 * exits
 * 
 */

/* exit */

void	free_minishell(t_data *minishell);

/* freeing */

#endif /* MINISHELL_H */