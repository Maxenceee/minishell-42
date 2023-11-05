/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffreze <ffreze@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 15:12:04 by ffreze            #+#    #+#             */
/*   Updated: 2023/11/03 18:08:36 by ffreze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

typedef struct s_data				t_data;
typedef struct s_parsing_commands	t_parsing_cmd;
typedef struct s_parsing_file		t_parsing_file;

/**
 * 
 * Ne plus utiliser,
 * utiliser O_TRUNC (pour REDIR_OUT)
 * et O_APPEND (pour CONCAT_OUT)
 * 
 */
typedef enum e_parsing_token
{
	PIPE, // |
	REDIR_IN, // <
	REDIR_OUT, // >
	CONCAT_IN, // <<
	CONCAT_OUT, // >>
}			t_parsing_token;

struct s_parsing_file
{
	char			*file_name;
	int				fd;
	t_parsing_token	type;
	t_parsing_file	*next;
};

struct s_parsing_commands
{
	t_parsing_cmd	*next;
	t_parsing_cmd	*prev;
	pid_t			pid;
	char			**cmd;
	int				pipe[2];
	int				fin;
	int				fout;
	t_parsing_file	*files;
};


int		ft_mainloop(t_data *minishell);

/**/

int		ft_push_new_command(t_data *minishell, char *line);
void	print_linked_list(t_parsing_cmd *cmd);

/* expands */

char	**ft_split_cmd(t_data *minishell, char *line);
char	*ft_parse_expands(t_data *minishell, char *arg);

/* free parsing linked list */

void	ft_destroy_parsing_cmd(t_data *minishell);

#endif /* PARSING_H */	