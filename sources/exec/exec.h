/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 20:24:32 by mgama             #+#    #+#             */
/*   Updated: 2023/11/04 19:05:20 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

/* heredoc */

int		open_heredoc(t_data *ms, t_parsing_cmd *cmd);
int		check_fd_heredoc(t_parsing_cmd *cmd, int pip[2]);

/* pipes */

int		open_fdinout(t_parsing_cmd *cmd);
int		dup_cmd(t_data *minishell, t_parsing_cmd *cmd, int pip[2]);

/* commands */

int		handle_cmd(t_data *minishell, t_parsing_cmd *cmd);
int		execcmd(char **command, t_data *ms);

/* builtins */

void	*get_builtin(char *cmd);
// int		exec_builtin(t_data *minishell, t_parsing_cmd *cmd);
int		is_builtin_no_out(t_parsing_cmd *cmd);

#endif /* EXEC_H */