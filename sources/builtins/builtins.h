/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 12:20:42 by mgama             #+#    #+#             */
/*   Updated: 2023/11/09 15:10:44 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

typedef struct s_data	t_data;

/**
 * builtin
 * 
 */

/* cd */

int		update_wd(t_data *ms);
int		ft_builtin_cd(t_data *minishell, t_parsing_cmd *cmd);

/* echo */

int		ft_builtin_echo(t_data *minishell, t_parsing_cmd *cmd);

/* env */

int		ft_builtin_env(t_data *minishell, t_parsing_cmd *cmd);

/* export */

int		ft_builtin_export(t_data *minishell, t_parsing_cmd *cmd);
char	**dup_env(t_data *ms);
char	**export_split(t_data *ms, char *token);

/* unset */

int		ft_builtin_unset(t_data *minishell, t_parsing_cmd *cmd);
void	unset_env(t_data *minishell, char *key);

/* pwd */

int		ft_builtin_pwd(t_data *minishell, t_parsing_cmd *cmd);

/* exit */

int		ft_builtin_exit(t_data *minishell, t_parsing_cmd *cmd);

#endif /* BUILTINS_H */