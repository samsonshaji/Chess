# CS247-Chess

Chess group project for CS247 

**Group Members:**
- Parsh Parikh
- Siddharth Viswanath
- Samson Shaji

## Available Modes
- `game human human`
- `game computer1 human`
- `game computer2 human`
- `game computer3 human`
- `game computer4 human`
- `game human computer1`
- `game human computer2`
- `game human computer3`
- `game human computer4`
- `game computer1 computer1`
- `game computer1 computer2`
- `game computer1 computer3`
- `game computer1 computer4`
- `game computer2 computer1`
- `game computer2 computer2`
- `game computer2 computer3`
- `game computer2 computer4`
- `game computer3 computer1`
- `game computer3 computer2`
- `game computer3 computer3`
- `game computer3 computer4`
- `game computer4 computer1`
- `game computer4 computer2`
- `game computer4 computer3`
- `game computer4 computer4`

## How to Play
1. Start the game:
    ```bash
    game human human
    ```

2. Make a move:
    ```bash
    move e2 e4
    ```

3. Resign the game:
    ```bash
    resign
    ```

4. Enter setup mode (when the game is ended or not started) to configure a custom initial board setup:
    ```bash
    setup
    ```

### Setup Mode Commands
- Place a piece on the board:
    ```bash
    + K e1
    ```
  This command places the piece `K` (white king) on the square `e1`. If a piece is already on that square, it is replaced. The board will be redisplayed.

- Remove a piece from the board:
    ```bash
    - e1
    ```
  This command removes the piece from the square `e1` and then redisplays the board. If there is no piece at that square, no action is taken.

- Set the next turn:
    ```bash
    = white
    ```
  This command makes it white's turn to go next.

- Exit setup mode:
    ```bash
    done
    ```
  This command leaves setup mode.

Enjoy playing Chess!
