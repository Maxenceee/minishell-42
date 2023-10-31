/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 12:20:42 by mgama             #+#    #+#             */
/*   Updated: 2023/10/31 13:24:35 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILDINS_H
# define BUILDINS_H

/**
 * builtin
 * 
 */

/* cd */

/* echo */

/* env */
int	builtin_env(t_data *minishell);

/* export */
int	builtin_export(t_data *minishell);

/* unset */

/* pwd */

/* exit */

#endif /* BUILDINS_H */