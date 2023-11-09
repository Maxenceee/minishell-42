/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 16:28:56 by mgama             #+#    #+#             */
/*   Updated: 2023/11/09 01:30:52 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

typedef struct s_data			t_data;

typedef struct s_env_element	t_env_element;

struct s_env_element
{
	t_env_element	*next;
	char			*key;
	char			*value;
};

int				ft_parse_env(t_data *minishell, char **envp);

/* new env element */

t_env_element	*ft_new_env_element(char *key, char *value);
t_env_element	*ft_new_env_element_fromline(char *line);
int				ft_push_env_element(t_data *minishell, t_env_element *env_e);

/* get env variable */

char			*ft_get_env_variable(t_data *minishell, char *key);

/* freeing env element */

void			destroy_env_element(t_env_element *env_e);
void			free_env(t_data *minishell);

/* print env */

void			print_env(t_data *minishell);
void			ft_print_env_variable(t_data *minishell, char *key, int new_line);

/* exit status */

char			*exit_status(char *line);

#endif /* ENV_H */