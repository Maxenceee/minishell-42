/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 12:20:42 by mgama             #+#    #+#             */
/*   Updated: 2023/11/04 02:13:51 by mgama            ###   ########.fr       */
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

int		ft_builtin_cd();

/* echo */

int		ft_builtin_echo(char **args);

/* env */

int		ft_builtin_env(t_data *minishell);

/* export */

int		ft_builtin_export(t_data *minishell, t_parsing_cmd *cmd);
char	**dup_env(t_data *ms);

/* unset */

int		ft_builtin_unset(t_data *minishell, t_parsing_cmd *cmd);

/* pwd */

int		ft_builtin_pwd(t_data *minishell);

/* exit */

int		ft_builtin_exit(t_data *minishell);

#endif /* BUILTINS_H */