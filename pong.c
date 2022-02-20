#include <stdio.h>

typedef struct s_vect
{
	int		x;
	int		y;
}				t_vect;

typedef struct s_pong
{
	char		map[25][81];
	t_vect		player_1;
	t_vect		player_2;
	t_vect		ball;
	t_vect		direction;
}				t_pong;


typedef struct s_game
{
	t_pong		pong;
	int			score_1;
	int			score_2;
	char		border;
	char		racket_char;
	char		ball_char;
}				t_game;

void	ft_init(t_game *game)
{
	game->score_1 = 0;
	game->score_2 = 0;
	game->border = '*';
	game->racket_char = '|';
	game->ball_char = 'O';
	game->pong.player_1.x = 12;
	game->pong.player_1.y = 1;
	game->pong.player_2.x = 12;
	game->pong.player_2.y = 78;
	game->pong.ball.x = 12;
	game->pong.ball.y = 2;
	game->pong.direction.x = 12;
	game->pong.direction.y = 79;

}

void	ft_print_map(t_game *game)
{
	int i, j;

//	printf("\e[1;1H\e[2J");
	printf("\n	player 1 :  %d      			  player 2 : %d \n", game->score_1, game->score_2);
	i = 0;
	while (i < 25)
	{
		j = 0;
		while (j < 80)
		{
			if (i == 0 || i == 24)
				game->pong.map[i][j] = game->border;
			else if (j == 0 || j == 79)
				game->pong.map[i][j] = game->border;
			else
				game->pong.map[i][j] = ' ';
			j++;
		}
		game->pong.map[i][j] = 0;
		i++;
	}
	
	i = game->pong.player_1.x;
	j = game->pong.player_2.x;

	game->pong.map[i - 1][1] = game->racket_char;
	game->pong.map[i][1] = game->racket_char;
	game->pong.map[i + 1][1] = game->racket_char;
	game->pong.map[j - 1][78] = game->racket_char;
	game->pong.map[j][78] = game->racket_char;
	game->pong.map[j + 1][78] = game->racket_char;
	game->pong.map[game->pong.ball.x][game->pong.ball.y] = game->ball_char;

	i = 0;
	while (i < 25)
	{
		printf("%s\n", game->pong.map[i++]);
	}
}

char	*ft_strchr(char *str, int c)
{
	if (str == NULL)
		return (NULL);
	while (*str)
	{
		if (*str == c)
			return (str);
		str++;
	}
	return (NULL);
}

void	ft_move_ball(t_game *game)
{
	(void) game;
}

int		ft_game_end(t_game *game)
{
	if (game->score_2 >= 25 || game->score_1 >= 25)
		return (1);
	return (0);
}

void	ft_print_end_msg(t_game *game)
{
	if (game->score_1 > 24)
		printf("Congratulations Player 1\n");
	else
		printf("Congratulations Player 2\n");
}

void	ft_next(t_game *game)
{
	int c;

	while (1)
	{
		c = getc(stdin);
		if (ft_strchr("azkm ", c))
		{
			if (c == 'z')
			{
				if (game->pong.player_1.x > 2)
					game->pong.player_1.x--;	
			}	
			else if (c == 'a')
			{
				if (game->pong.player_1.x < 22)
					game->pong.player_1.x++;
			}
			else if (c == 'k')
			{
				if (game->pong.player_2.x > 2)
					game->pong.player_2.x--;
			}
			else if (c == 'm')
			{
				if (game->pong.player_2.x < 22)
					game->pong.player_2.x++;
			}
			ft_move_ball(game);
			ft_print_map(game);
			if (ft_game_end(game))
				break;
		}
	}
	ft_print_end_msg(game);
}


int main()
{
	t_game	game;

	ft_init(&game);
	ft_print_map(&game);
	ft_next(&game);
	return 0;
}
