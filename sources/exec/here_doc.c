/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 18:34:34 by mgama             #+#    #+#             */
/*   Updated: 2023/11/03 18:46:35 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char	*new_here_doc_fname()
// {
// 	static int	i = 0;
// 	char		*num;
// 	char		*file_name;

// 	num = ft_itoa(i++);
// 	file_name = ft_strjoin(".objs/.tmp_hd_file", num);
// 	free(num);
// 	return (file_name);
// }

int	open_heredoc(t_data *ms, t_parsing_cmd *cmd)
{
	t_parsing_file	*f;

	f = cmd->files;
	while (f)
	{
		if (f->type == CONCAT_IN)
		{
			// if (cmd->here_doc_fname)
			// 	free(cmd->here_doc_fname);
			// cmd->here_doc_fname = 
		}
		f = f->next;
	}
	return (MS_SUCCESS);
}
