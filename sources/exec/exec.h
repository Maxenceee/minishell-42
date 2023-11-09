/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 20:24:32 by mgama             #+#    #+#             */
/*   Updated: 2023/11/09 14:30:59 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

/* parse env */

char	*parse_env(t_data *ms, char *cmd);

/* pipes */

int		open_fdinout(t_parsing_cmd *cmd);
int		dup_cmd(t_data *minishell, t_parsing_cmd *cmd, int pip[2]);

/* commands */

int		handle_cmd(t_data *minishell, t_parsing_cmd *cmd);
int		execcmd(char **command, t_data *ms);

/* builtins */

void	*get_builtin(char *cmd);
int		is_builtin_no_out(t_parsing_cmd *cmd);

/* wait */
int		wait_process(pid_t pid, int last);
void	wait_all_process(t_data *ms);

/* heredoc */

int		open_heredoc(t_data *ms, t_parsing_cmd *cmd);
int		check_fd_heredoc(t_parsing_cmd *cmd, int pip[2]);

/* utils */

int		is_empty(char *str);
int		is_dir(char *str);

#endif /* EXEC_H */