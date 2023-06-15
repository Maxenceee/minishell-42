/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 16:26:12 by mgama             #+#    #+#             */
/*   Updated: 2023/06/15 14:57:57 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/errno.h>
# include <signal.h>
# include <fcntl.h>

# define PIPE_ERROR "Pipe error"
# define EXEVE_ERROR "Could not execute execve"
# define OPEN_IN_ERROR "Infile"
# define OPEN_OUT_ERROR "Outfile"
# define FORK_ERROR "Fork"
# define COMMAND_NOT_FOUND "Command not found"
# define PERM_DENIED "permission denied"

typedef struct s_commands {
	char	***command_list;
	char	*input;
	char	*output;
	int		process_count;
	int		*pipes;
	int		pipe_nb;
	char	**envp;
	char	*pwd;
}				t_commands;

/* exec */
void	fork_processes(t_commands *commands);
void	process_child(t_commands *commands, int idx);
int		open_fdinout(int idx, t_commands *c);
int		execcmd(char **command, char *envp[]);

/* parse_env */
char	*parse_env(char *envp[], char *cmd);

/* pipes */
void	create_pipes(t_commands *commands);
void	close_pipes(t_commands *commands);
int		dup2_fdinout(int fdin, int fdout);

/* utils */
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
void	ft_putstr_fd(char *s, char *t, int fd);
char	**ft_split(const char *str, char charset);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, unsigned int n);
char	*ft_strjoin_arr(int size, char **strs, char *sep);
size_t	ft_strlen(const char *str);

/* exit */
void	exit_with_code(t_commands *commands, int code);
void	exit_error_with_msg(t_commands *commands, char *msg);

#endif /* MINISHELL_H */