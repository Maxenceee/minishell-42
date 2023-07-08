/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 19:02:43 by mgama             #+#    #+#             */
/*   Updated: 2023/07/07 19:03:33 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

/* ft_bzero */
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
void	ft_putstr_fd(char *s, char *t, int fd);
char	**ft_split(const char *str, char charset);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, unsigned int n);
char	*ft_strjoin_arr(int size, char **strs, char *sep);
size_t	ft_strlen(const char *str);

#endif /* UTILS_H */