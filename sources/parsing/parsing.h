/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 15:12:04 by ffreze            #+#    #+#             */
/*   Updated: 2023/11/01 18:01:16 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

typedef struct s_data				t_data;
typedef struct s_parsing_commands	t_parsing_cmd;
typedef struct s_parsing_file		t_parsing_file;

typedef enum e_parsing_token
{
	// PIPE, // |
	REDIR_IN, // <
	REDIR_OUT, // >
	CONCAT_IN, // <<
	CONCAT_OUT, // >>
}			t_parsing_token;

struct s_parsing_file
{
	char			*file_name;
	t_parsing_file	*next;	
};

struct s_parsing_commands
{
	t_parsing_cmd	*next;
	char			**cmd;
	char			*line;
	t_parsing_file	*files;
};

int		ft_mainloop(t_data *minishell);

/**/

int		ft_push_new_command(t_data *minishell, char *line);
void	print_linked_list(t_parsing_cmd *cmd);

/* expands */

char	*ft_parse_expands(t_data *minishell, char *arg);

/* free parsing linked list */

void	ft_destroy_parsing_cmd(t_data *minishell);

#endif /* PARSING_H */