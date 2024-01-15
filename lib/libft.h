/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcario <jcario@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:37:49 by jcario            #+#    #+#             */
/*   Updated: 2023/12/02 03:44:20 by jcario           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

typedef struct s_list
{
	int				content;
	struct s_list	*next;
}	t_list;

long long			ft_atoi(const char *str);
void				ft_bzero(void *ptr, size_t n);
void				*ft_calloc(size_t count, size_t size);
int					ft_isalnum(int ch);
int					ft_isalpha(int ch);
int					ft_isascii(int ch);
int					ft_isdigit(int ch);
int					ft_isprint(int ch);
char				*ft_itoa(int n);
void				*ft_memchr(const void *mem, int s, size_t size);
int					ft_memcmp(const void *ptr1, const void *ptr2, size_t size);
void				*ft_memcpy(void *dest, const void *src, size_t size);
void				*ft_memmove(void *dest, const void *src, size_t size);
void				*ft_memset(void *ptr, int value, size_t size);
void				ft_putchar_fd(char c, int fd);
void				ft_putendl_fd(char *str, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_putstr_fd(char *str, int fd);
char				**ft_split(char const *str, char sep);
char				*ft_strchr(const char *str, int s);
char				*ft_strdup(const char *src);
void				ft_striteri(char *str, void (*f)(unsigned int, char*));
char				*ft_strjoin(char const *s1, char const *s2);
unsigned int		ft_strlcat(char *dest, const char *src, size_t size);
unsigned int		ft_strlcpy(char *dest, const char *src, size_t size);
int					ft_strlen(const char *str);
char				*ft_strmapi(char const *str, char (*f)(unsigned int, char));
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strnstr(const char *str, const char *srch, size_t len);
char				*ft_strrchr(const char *str, int s);
char				*ft_strtrim(char *str, char const *set);
char				*ft_substr(char const *str, unsigned int start, size_t len);
int					ft_tolower(int ch);
int					ft_toupper(int ch);
t_list				*ft_lstmap(t_list *l, int (*f)(int), void (*d)(int));
void				ft_lstiter(t_list *lst, void (*f)(int));
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstadd_front(t_list **lst, t_list *new);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstclear(t_list **lst, void (*del)(int));
void				ft_lstdelone(t_list *lst, void (*del)(int));
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
t_list				*ft_lstnew(int content);

char				*get_next_line(int fd);
char				*ft_strjoin_modified(char *s1, char *s2);

int					ft_printf(const char *str, ...);

int					ft_putstr(char *str);
int					ft_putchar(char ch);

int					ft_putnbr(int nb);
void				ft_putunbr(unsigned int nb);
int					ft_putunbr_count(unsigned int nb);

int					ft_putptr_fd(void *addr, int fd);
int					ft_puthexa(unsigned int nb, char *base);
void				ft_puthexa_fd(unsigned int n, char *base, int fd);

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

#endif
