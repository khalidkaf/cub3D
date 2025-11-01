/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkafmagh <kkafmagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 10:42:17 by sachanai          #+#    #+#             */
/*   Updated: 2025/11/01 14:06:55 by kkafmagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// char	*ft_strchr(const char *str, int c)
// {
// 	unsigned char	uc;

// 	if (!str)
// 		return (NULL);
// 	uc = (unsigned char)c;
// 	while (*str && *str != uc)
// 		str++;
// 	if (*str == uc)
// 		return ((char *)str);
// 	else
// 		return (0);
// }

// int	ft_strncmp(const char *s1, const char *s2, size_t n)
// {
// 	size_t	i;

// 	i = 0;
// 	if (n == 0)
// 		return (0);
// 	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i] && i < n - 1)
// 		i++;
// 	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
// }

// void	*ft_calloc(size_t elementCount, size_t elementSize)
// {
// 	char	*str;
// 	size_t	i;

// 	i = 0;
// 	if (elementCount && elementSize > __SIZE_MAX__ / elementCount)
// 		return (NULL);
// 	str = malloc(elementCount * elementSize);
// 	if (!str)
// 		return (NULL);
// 	while (i < elementCount * elementSize)
// 	{
// 		str[i] = 0;
// 		i++;
// 	}
// 	return (str);
// }

char	*ft_strjoin1(char *s1, char *s2)
{
	char	*result;
	char	*str;
	char	*str2;
	size_t	total_len;

	total_len = ft_strlen((char *)s1) + ft_strlen((char *)s2);
	str = (char *)s1;
	str2 = (char *)s2;
	if (!str2)
		return (NULL);
	result = (char *)malloc(total_len + 1);
	if (!result)
		return (NULL);
	ft_memcpy(result, str, ft_strlen(str));
	ft_memcpy(result + ft_strlen(str), str2, ft_strlen(str2));
	free(s1);
	result[total_len] = '\0';
	return (result);
}

// int	ft_strlen(const char *str)
// {
// 	int	count;

// 	if (!str)
// 		return (0);
// 	count = 0;
// 	while (str[count] != '\0')
// 		count++;
// 	return (count);
// }

// void	*ft_memcpy(void *dest, const void *src, size_t numBytes)
// {
// 	unsigned char		*temp_dest;
// 	const unsigned char	*temp_src;
// 	size_t				i;

// 	i = 0;
// 	temp_dest = (unsigned char *)dest;
// 	temp_src = (const unsigned char *)src;
// 	if (!dest && !src)
// 		return (NULL);
// 	while (i < numBytes)
// 	{
// 		temp_dest[i] = temp_src[i];
// 		i++;
// 	}
// 	return (dest);
// }

char	*extract_line(char *stock)
{
	int		i;
	char	*line;

	if (!stock)
		return (NULL);
	i = 0;
	while (stock[i] && stock[i] != '\n')
		i++;
	line = (char *)ft_calloc(i + 2, sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (stock[i] && stock[i] != '\n')
	{
		line[i] = stock[i];
		i++;
	}
	if (stock[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*update_stock(char *stock)
{
	char	*new_stock;
	int		i;
	int		n_s;

	i = 0;
	while (stock[i] && stock[i] != '\n')
		i++;
	if (stock[i] == '\n')
		i++;
	if (!stock[i])
	{
		free(stock);
		return (NULL);
	}
	new_stock = (char *)ft_calloc(ft_strlen(stock) - i + 1, sizeof(char));
	if (!new_stock)
		return (NULL);
	n_s = 0;
	while (stock[i])
		new_stock[n_s++] = stock[i++];
	new_stock[n_s] = '\0';
	free(stock);
	return (new_stock);
}

static int	handle_invalid_fd(char **stock)
{
	if (*stock)
	{
		free(*stock);
		*stock = NULL;
	}
	return (0);
}

char	*get_next_line(int fd)
{
	static char	*stock;
	char		*buffer;
	char		*line;
	int			bytes_read;

	if (fd < 0)
		return (handle_invalid_fd(&stock), NULL);
	if (BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		stock = ft_strjoin1(stock, buffer);
		if (!stock || ft_strchr(stock, '\n'))
			break ;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	free(buffer);
	if (bytes_read < 0 || (!stock && bytes_read == 0))
		return (free(stock), stock = NULL, NULL);
	return (line = extract_line(stock), stock = update_stock(stock), line);
}
// char	*get_next_line(int fd)
// {
// 	static char	*stock;
// 	char		*buffer;
// 	char		*line;
// 	int			bytes_read;

// 	if (fd < 0)
// 		return (handle_invalid_fd(&stock), NULL);
// 	if (BUFFER_SIZE <= 0)
// 		return (NULL);
// 	buffer = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char));
// 	if (!buffer)
// 		return (NULL);
// 	bytes_read = read(fd, buffer, BUFFER_SIZE);
// 	while (bytes_read > 0)
// 	{
// 		buffer[bytes_read] = '\0';
// 		stock = ft_strjoin1(stock, buffer);
// 		if (!stock || ft_strchr(stock, '\n'))
// 			break ;
// 		bytes_read = read(fd, buffer, BUFFER_SIZE);
// 	}
// 	free(buffer);
// 	if (bytes_read < 0 || (!stock && bytes_read == 0))
// 		return (free(stock), stock = NULL, NULL);
// 	line = extract_line(stock);
// 	stock = update_stock(stock);
// 	return (line);
// }

// int main()
// {
// 	char	*line;
// 	int	fd;
// 	int	index;

// 	index = 0;
// 	fd = open("test_file.txt", O_RDWR);
// 		while (index < 2)
// 		{
// 		line = get_next_line(fd);
// 		printf("%d : %s", index, line);
// 		index++;
// 		free(line);
// 		}
// 	return (0);
// }