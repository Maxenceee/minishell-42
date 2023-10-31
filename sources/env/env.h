/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 16:28:56 by mgama             #+#    #+#             */
/*   Updated: 2023/10/31 13:24:46 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

typedef struct s_env_element	t_env_element;

struct s_env_element
{
	t_env_element	*next;
	char			*key;
	char			*value;
};

int		ft_parse_env(t_data *minishell, char **envp);

int		ft_push_env_element(t_data *minishell, char *line);

/* print env */

void	print_env(t_data *minishell);

#endif /* ENV_H */