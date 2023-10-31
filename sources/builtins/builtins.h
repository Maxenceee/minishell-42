/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 12:20:42 by mgama             #+#    #+#             */
/*   Updated: 2023/10/31 23:48:10 by mgama            ###   ########.fr       */
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

/* echo */

int		ft_builtin_echo(t_data *minishell, char *args, int has_newline);

/* env */

int		ft_builtin_in_env(t_data *minishell);

/* export */

int		ft_builtin_in_export(t_data *minishell, char *key, char *value);

/* unset */

int		ft_builtin_in_unset(t_data *minishell, char *key);

/* pwd */

/* exit */

#endif /* BUILTINS_H */