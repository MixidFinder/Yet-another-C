#include <math.h>
#include <stdio.h>

#define WIDTH 80
#define HEIGHT 25
#define PADDLE_SIZE 3
#define WINNING_SCORE 21
#define CLEAR_SCREEN "\033[H\033[J"

int play(int score_one, int score_two);
char get_char_at(int x, int y);
void draw_field(int paddle_one_x, int paddle_one_y, int paddle_two_x, int paddle_two_y, int ball_x,
                int ball_y, int score_one, int score_two);
int move_paddle(int paddle_y, char input, int is_player);
char get_valid_input(int is_player);
int check_collision_racket(int ball_x, int ball_y, int racket_1_y, int racket_2_y);
int check_collision_top_bottom(int ball_y);
int check_collision_left_right(int ball_x);
int move_ball_x(int ball_x, int ball_direction_x);
int move_ball_y(int ball_y, int ball_direction_y);
void winner_screen(int player_number);

int main() {
    int score_one = 0;
    int score_two = 0;

    while (score_one < WINNING_SCORE && score_two < WINNING_SCORE) {
        if (play(score_one, score_two) == 1) {
            score_one++;
        } else {
            score_two++;
        }
    }

    return 0;
}

/**
 * @brief Generates a pseudo-random number based on the provided score.
 *
 * This function computes a pseudo-random number using a linear
 * congruential generator algorithm. The generated number is derived
 * from the input score, which acts as the seed for the random number
 * generation. This approach ensures that the same score will always
 * produce the same output, making it deterministic.
 *
 * @param score An integer value used as the seed for generating
 *              the pseudo-random number.
 *
 * @return An integer representing the generated pseudo-random number.
 */
int rand(int score) {
    int seed = (1103515245 * score + 12345);
    return seed;
}

/**
 * @brief Manages the main gameplay loop for a two-player paddle game.
 *
 * This function initializes the positions of the paddles and the ball,
 * and then enters a continuous loop where it handles user input,
 * updates the game state, and checks for collisions. The loop continues
 * until a player reaches the winning score or a collision with the
 * left or right wall occurs, indicating a score change.
 *
 * The gameplay includes:
 * - Drawing the game field with paddles and ball positions.
 * - Accepting input from both players to move their respective paddles.
 * - Moving the ball based on its current direction.
 * - Detecting collisions with the top/bottom walls and paddles,
 *   adjusting ball direction accordingly.
 * - Checking for collisions with the left/right walls to determine
 *   scoring and ending conditions.
 *
 * @param score_one The current score of player 1.
 * @param score_two The current score of player 2.
 *
 * @return Returns 1 if player 1 wins, 2 if player 2 wins, or 0 if
 *         the game ends without a winner (though this case is not
 *         expected to occur in normal gameplay).
 */
int play(int score_one, int score_two) {
    int paddle_one_x = 1, paddle_one_y = 11;
    int paddle_two_x = WIDTH - 2, paddle_two_y = 11;
    int ball_x = WIDTH / 2, ball_y = ((HEIGHT + 2) / 2) + ((rand(score_one + score_two) % 10) - 5);
    int ball_direction_x = (rand(score_one + score_two) % 2) ? 1 : -1;
    int ball_direction_y = (rand(score_one + score_two) % 2) ? 1 : -1;
    while (1) {
        draw_field(paddle_one_x, paddle_one_y, paddle_two_x, paddle_two_y, ball_x, ball_y, score_one,
                   score_two);

        printf(
            "Игрок 1, введите 'a' для вверх, 'z' для вниз или пробел для "
            "пропуска: ");
        char input_one = get_valid_input(1);
        if (input_one != ' ') {
            paddle_one_y = move_paddle(paddle_one_y, input_one, 1);
        }
        draw_field(paddle_one_x, paddle_one_y, paddle_two_x, paddle_two_y, ball_x, ball_y, score_one,
                   score_two);

        printf(
            "Игрок 2, введите 'k' для вверх, 'm' для вниз или пробел для "
            "пропуска: ");
        char input_two = get_valid_input(0);
        if (input_two != ' ') {
            paddle_two_y = move_paddle(paddle_two_y, input_two, 0);
        }
        ball_x = move_ball_x(ball_x, ball_direction_x);
        ball_y = move_ball_y(ball_y, ball_direction_y);

        if (check_collision_top_bottom(ball_y)) {
            ball_direction_y *= -1;
        }

        if (check_collision_racket(ball_x, ball_y, paddle_one_y, paddle_two_y)) {
            ball_direction_x *= -1;
        }

        if (check_collision_left_right(ball_x)) {
            ball_direction_x *= -1;
            if (ball_x == 1) {
                return 2;
            } else if (ball_x == WIDTH - 2) {
                return 1;
            }
        }
    }

    if (score_one >= WINNING_SCORE) {
        winner_screen(1);
    } else {
        winner_screen(2);
    }

    return 0;
}

/**
 * @brief Retrieves the character to display at a given coordinate.
 *
 * This function determines what character should be displayed at
 * the specified (x, y) coordinates on the game field. It checks
 * if the coordinates correspond to the boundaries of the field
 * or if they are within the playable area.
 *
 * The function returns:
 * - '-' for the top and bottom edges of the field,
 * - '|' for the left and right edges of the field,
 * - ' ' (space) for all other positions inside the field.
 *
 * @param x The x-coordinate of the position to check.
 * @param y The y-coordinate of the position to check.
 *
 * @return A character representing what should be displayed at
 *         the given coordinates: '-' for horizontal boundaries,
 *         '|' for vertical boundaries, or ' ' for empty spaces.
 */
char get_char_at(int x, int y) {
    if (y == 0 || y == HEIGHT - 1) {
        return '-';
    } else if (x == 0 || x == WIDTH - 1) {
        return '|';
    } else {
        return ' ';
    }
}

/**
 * @brief Draws the game field including paddles, ball, and scores.
 *
 * This function renders the current state of the game field by displaying
 * the positions of both paddles and the ball. It also clears the screen
 * before drawing the field and updates the score for both players.
 *
 * The paddles are represented by '#' characters, while the ball is represented
 * by an 'O'. The function iterates over the dimensions of the game field
 * and determines what to display at each position based on the provided
 * coordinates.
 *
 * @param paddle_one_x The x-coordinate of player 1's paddle.
 * @param paddle_one_y The y-coordinate of player 1's paddle.
 * @param paddle_two_x The x-coordinate of player 2's paddle.
 * @param paddle_two_y The y-coordinate of player 2's paddle.
 * @param ball_x The x-coordinate of the ball.
 * @param ball_y The y-coordinate of the ball.
 * @param score_one The current score of player 1.
 * @param score_two The current score of player 2.
 */
void draw_field(int paddle_one_x, int paddle_one_y, int paddle_two_x, int paddle_two_y, int ball_x,
                int ball_y, int score_one, int score_two) {
    printf(CLEAR_SCREEN);
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (x == paddle_one_x && y >= paddle_one_y && y < paddle_one_y + PADDLE_SIZE) {
                putchar('#');

            } else if (x == paddle_two_x && y >= paddle_two_y && y < paddle_two_y + PADDLE_SIZE) {
                putchar('#');

            } else if (x == ball_x && y == ball_y) {
                putchar('O');

            } else {
                putchar(get_char_at(x, y));
            }
        }
        putchar('\n');
    }

    printf("Игрок 1: %d  Игрок 2: %d\n", score_one, score_two);
}

/**
 * @brief Moves the paddle up or down based on user input.
 *
 * This function updates the vertical position of a paddle in a game,
 * depending on the player's input and whether the paddle belongs to
 * player 1 or player 2. The paddle's movement is constrained within
 * the game boundaries to prevent it from moving out of bounds.
 *
 * @param paddle_y The current vertical position of the paddle.
 *                 Should be within the range [1, HEIGHT - PADDLE_SIZE - 1].
 * @param input A character representing the user's input:
 *              - 'a' to move player 1's paddle up,
 *              - 'z' to move player 1's paddle down,
 *              - 'k' to move player 2's paddle up,
 *              - 'm' to move player 2's paddle down.
 * @param is_player An integer flag indicating which player's paddle is being
 * moved:
 *                  - Non-zero value (true) for player 1,
 *                  - Zero value (false) for player 2.
 *
 * @return The updated vertical position of the paddle after processing
 *         the input. The returned value will still be within the valid
 *         range for paddle movement.
 */
int move_paddle(int paddle_y, char input, int is_player) {
    if (is_player) {
        if (input == 'a' && paddle_y > 1) {
            paddle_y--;
        } else if (input == 'z' && paddle_y < HEIGHT - PADDLE_SIZE - 1) {
            paddle_y++;
        }
    } else {
        if (input == 'k' && paddle_y > 1) {
            paddle_y--;
        } else if (input == 'm' && paddle_y < HEIGHT - PADDLE_SIZE - 1) {
            paddle_y++;
        }
    }
    return paddle_y;
}

/**
 * @brief Retrieves valid input from the user based on the player type.
 *
 * This function prompts the user for input and checks its validity
 * according to whether it is for player 1 or player 2. Valid inputs
 * for player 1 are 'a', 'z', or space (' '), while valid inputs for
 * player 2 are 'k', 'm', or space (' '). The function ignores any
 * invalid inputs and prompts the user to try again until a valid input
 * is received.
 *
 * @param is_player An integer flag indicating which player's input is being
 * requested:
 *                  - Non-zero value (true) for player 1,
 *                  - Zero value (false) for player 2.
 *
 * @return A character representing the valid input from the user.
 *         The returned value will be one of the valid commands
 *         corresponding to the specified player.
 */
char get_valid_input(int is_player) {
    while (1) {
        char input;
        input = getchar();

        if ((is_player && (input == 'a' || input == 'z' || input == ' ')) ||
            (!is_player && (input == 'k' || input == 'm' || input == ' '))) {
            while (getchar() != '\n')
                ;
            return input;

        } else {
            printf("Неверная команда. Попробуйте еще раз.\n");
            while (getchar() != '\n')
                ;
        }
    }
}

/**
 * @brief Checks for collisions between the ball and the paddles.
 *
 * This function determines whether the ball has collided with either
 * of the two paddles in the game. It checks the ball's position against
 * the coordinates of each paddle to see if they intersect.
 *
 * A collision is detected if:
 * - The ball is at the x-coordinate corresponding to paddle 1 (left paddle)
 *   and its y-coordinate is within one unit of paddle 1's y-coordinate.
 * - The ball is at the x-coordinate corresponding to paddle 2 (right paddle)
 *   and its y-coordinate is within one unit of paddle 2's y-coordinate.
 *
 * @param ball_x The x-coordinate of the ball.
 * @param ball_y The y-coordinate of the ball.
 * @param racket_1_y The y-coordinate of player 1's paddle.
 * @param racket_2_y The y-coordinate of player 2's paddle.
 *
 * @return 1 if a collision occurs with either paddle;
 *         0 if there is no collision.
 */
int check_collision_racket(int ball_x, int ball_y, int racket_1_y, int racket_2_y) {
    if (floor(ball_x) == 3) {
        if (ball_y >= racket_1_y - 1 && ball_y <= racket_1_y + 1) {
            return 1;
        }
    }

    if (floor(ball_x) == WIDTH - 4) {
        if (ball_y >= racket_2_y - 1 && ball_y <= racket_2_y + 1) {
            return 1;
        }
    }

    return 0;
}

/**
 * @brief Checks for collisions between the ball and the top/bottom walls.
 *
 * This function determines whether the ball has collided with the
 * upper or lower boundaries of the game field. A collision is detected
 * if the ball's y-coordinate is at or beyond the defined limits for
 * the top and bottom walls.
 *
 * Specifically, a collision occurs if:
 * - The ball's y-coordinate is less than or equal to 1 (top wall).
 * - The ball's y-coordinate is greater than or equal to HEIGHT - 2
 *   (bottom wall).
 *
 * @param ball_y The y-coordinate of the ball.
 *
 * @return 1 if a collision occurs with either the top or bottom wall;
 *         0 if there is no collision.
 */
int check_collision_top_bottom(int ball_y) {
    if (floor(ball_y) <= 1 || floor(ball_y) >= HEIGHT - 2) {
        return 1;
    }

    return 0;
}

/**
 * @brief Checks for collisions between the ball and the left/right walls.
 *
 * This function determines whether the ball has collided with the
 * left or right boundaries of the game field. A collision is detected
 * if the ball's x-coordinate is at or beyond the defined limits for
 * the left and right walls.
 *
 * Specifically, a collision occurs if:
 * - The ball's x-coordinate is less than or equal to 1 (left wall).
 * - The ball's x-coordinate is greater than or equal to WIDTH - 2
 *   (right wall).
 *
 * @param ball_x The x-coordinate of the ball.
 *
 * @return 1 if a collision occurs with either the left or right wall;
 *         0 if there is no collision.
 */
int check_collision_left_right(int ball_x) {
    if (floor(ball_x) <= 1 || floor(ball_x) >= WIDTH - 2) {
        return 1;
    }

    return 0;
}

/**
 * @brief Moves the ball along the X-axis based on its direction.
 *
 * This function updates the x-coordinate of the ball by adding the
 * specified direction value to its current position. The direction
 * value can be positive (moving right) or negative (moving left).
 *
 * @param ball_x The current x-coordinate of the ball.
 * @param ball_direction_x The amount to change the ball's x-coordinate.
 *                         Positive values move the ball to the right,
 *                         while negative values move it to the left.
 *
 * @return The updated x-coordinate of the ball after applying the
 *         movement.
 */
int move_ball_x(int ball_x, int ball_direction_x) {
    int updated_ball_x = ball_x + ball_direction_x;

    return updated_ball_x;
}

/**
 * @brief Moves the ball along the Y-axis based on its direction.
 *
 * This function updates the y-coordinate of the ball by adding the
 * specified direction value to its current position. The direction
 * value can be positive (moving down) or negative (moving up).
 *
 * @param ball_y The current y-coordinate of the ball.
 * @param ball_direction_y The amount to change the ball's y-coordinate.
 *                         Positive values move the ball downward,
 *                         while negative values move it upward.
 *
 * @return The updated y-coordinate of the ball after applying the
 *         movement.
 */
int move_ball_y(int ball_y, int ball_direction_y) {
    int updated_ball_y = ball_y + ball_direction_y;

    return updated_ball_y;
}

/**
 * @brief Prints the word "PONG" in ASCII art format.
 *
 * This function outputs a stylized representation of the word
 * "PONG" to the console using a series of characters to create
 * a visually appealing design. The output is formatted to align
 * properly when displayed in a monospaced font.
 *
 * This function does not take any parameters and does not return
 * any values. It is primarily used for branding or decorative
 * purposes within the game.
 */
void print_pong_word() {
    printf("██████   ██████  ███    ██  ██████ \n");
    printf("                    ██   ██ ██    ██ ████   ██ ██      \n");
    printf("                    ██████  ██    ██ ██ ██  ██ ██   ███\n");
    printf("                    ██      ██    ██ ██  ██ ██ ██    ██\n");
    printf("                    ██       ██████  ██   ████  ██████ \n");
}

/**
 * @brief Displays a victory message for Player One.
 *
 * This function outputs an ASCII art representation of a victory
 * message specifically for Player One. The message is designed to
 * be visually appealing and celebratory, indicating that Player One
 * has won the game.
 *
 * The output is formatted to align properly when displayed in a
 * monospaced font, making it suitable for console applications.
 *
 * This function does not take any parameters and does not return
 * any values. It is typically called at the end of the game when
 * Player One achieves victory.
 */
void player_one_win() {
    printf(
        "██████  ██       █████  ██    ██ ███████ ██████     ██   ██     ██ "
        "██ ███    ██\n");
    printf(
        " ██   ██ ██      ██   ██  ██  ██  ██      ██   ██   ███   ██     ██ "
        "██ ████   ██\n");
    printf(
        " ██████  ██      ███████   ████   █████   ██████     ██   ██  █  ██ "
        "██ ██ ██  ██\n");
    printf(
        " ██      ██      ██   ██    ██    ██      ██   ██    ██   ██ ███ ██ "
        "██ ██  ██ ██\n");
    printf(
        " ██      ███████ ██   ██    ██    ███████ ██   ██    ██    ███ ███  "
        "██ ██   ████\n");
}

/**
 * @brief Displays a victory message for Player Two.
 *
 * This function outputs an ASCII art representation of a victory
 * message specifically for Player Two. The message is designed to
 * be visually appealing and celebratory, indicating that Player Two
 * has won the game.
 *
 * The output is formatted to align properly when displayed in a
 * monospaced font, making it suitable for console applications.
 *
 * This function does not take any parameters and does not return
 * any values. It is typically called at the end of the game when
 * Player Two achieves victory.
 */
void player_two_win() {
    printf(
        "██████  ██       █████  ██    ██ ███████ ██████      ██████      ██  "
        "   ██ ██ ███    ██\n");
    printf(
        " ██   ██ ██      ██   ██  ██  ██  ██      ██   ██          ██     ██ "
        "    ██ ██ ████   ██\n");
    printf(
        " ██████  ██      ███████   ████   █████   ██████       █████      ██ "
        " █  ██ ██ ██ ██  ██\n");
    printf(
        " ██      ██      ██   ██    ██    ██      ██   ██     ██          ██ "
        "███ ██ ██ ██  ██ ██\n");
    printf(
        " ██      ███████ ██   ██    ██    ███████ ██   ██     ███████      "
        "███ ███  ██ ██   ████\n");
}

/**
 * @brief Displays the winner screen after a game concludes.
 *
 * This function clears the screen and presents a celebratory
 * message indicating the winner of the game. It uses ASCII art
 * to display the word "PONG" and a victory message for the
 * specified player.
 *
 * The function takes into account the player's number to determine
 * which victory message to display:
 * - If `player_number` is 1, it shows the victory message for Player One.
 * - If `player_number` is 2, it shows the victory message for Player Two.
 *
 * The screen is formatted to center the messages, with appropriate
 * spacing to enhance visibility and aesthetics.
 *
 * @param player_number An integer representing the winning player:
 *                      - 1 for Player One,
 *                      - 2 for Player Two.
 *
 * @return This function does not return any values.
 */
void winner_screen(int player_number) {
    printf(CLEAR_SCREEN);

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (i == HEIGHT / 2 - 2 && j == (WIDTH / 2) - 20) {
                print_pong_word();

                j += 3;
            } else if (i == HEIGHT / 2 && j == 1) {
                if (player_number == 1) {
                    player_one_win();
                } else {
                    player_two_win();
                }
                j += 11;
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
}
