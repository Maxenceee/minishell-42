/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 16:26:12 by mgama             #+#    #+#             */
/*   Updated: 2023/11/08 19:35:10 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <dirent.h>
# include <limits.h>
# include <errno.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "pcolors.h"

# define MS_PROMPT_NAME			HEADER"minishell$ "RESET
# define MS_HEREDOC_MSG			B_PURPLE"> "RESET
# define MS_ERROR_PREFIX		"minishell: "
# define MS_PIPE_ERROR			MS_ERROR_PREFIX"pipe error\n"
# define MS_EXEVE_ERROR			MS_ERROR_PREFIX"could not execute execve: "
# define MS_OPEN_ERROR			MS_ERROR_PREFIX"could not open file\n"
# define MS_FORK_ERROR			MS_ERROR_PREFIX"could not fork\n"
# define MS_WAIT_ERROR			MS_ERROR_PREFIX"could not wait\n"
# define MS_COMMAND_NOT_FOUND	"command not found\n"
# define MS_IS_DIR				"is a directory\n"
# define MS_NO_FILE_DIR			"No such file or directory\n"
# define MS_PERM_DENIED			"Permission denied\n"
# define MS_TOO_MANY			"too many arguments\n"
# define MS_ALLOC_ERROR_MSG		"Error: could not allocate memory.\n"

# define BUFF_SIZE		4096
# define MS_SUCCESS		0
# define MS_ERROR		1
# define MS_NO_ERROR	2

# include "../sources/utils/utils.h"
# include "../sources/parsing/parsing.h"
# include "../sources/exec/exec.h"
# include "../sources/builtins/builtins.h"
# include "../sources/env/env.h"

extern uint32_t			g_signal;
typedef struct s_data	t_data;

struct s_data {
	t_env_element	*env;
	char			**envp;
	int				exit;
	int				pipes;
	char			*pwd;
	// char			*old_pwd;
	t_parsing_cmd	*parsing_cmd;
	char			*prompt;
};

typedef	enum e_signal
{
	EXIT_CODE		= 255,
	STOP_HEREDOC	= 256,
	IN_CMD			= 512,
	IN_HERE_DOC		= 1024,
}				t_signal;

// typedef struct	s_signal
// {
// 	int			exit_code;
// 	int			stop_heredoc;
// 	int			in_cmd;
// 	int			in_here_doc;
// }				t_signal;

// t_signal	g_signal;

/**
 * main
 * 
 */

/* signal */

int		get_g_signal_val(int flag);
void	set_g_signal_val(int flag, int val);
// void	sigint_handler(int sig);
// void	sigquit_handler(int sig);
// void	setup_signals(void);
void	setup_signals(void);
void	setup_exec_signals(int child_pid);
void	setup_hd_signals(int child_pid);

/**
 * exec
 * 
 */

/* process */

int		mini_exec(t_data *minishell);

/**
 * parsing
 * 
 */

/* parsing */

char	*parse_env(t_data *ms, char *cmd);

/**
 * exits
 * 
 */

/* exit */

void 	exit_with_code(t_data *ms, int error_code, char *message);
void	exit_with_error(t_data *ms, int error_code, char *message);
void	free_minishell(t_data *minishell);

/* freeing */

#endif /* MINISHELL_H */