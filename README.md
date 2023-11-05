# snake 🐍 

## intro
I tried to recreate the classic snake game in C language in order to practice the language. It's built on macOS so it should work on any unix-based system. If that's your case feel free to try it and suggest any modification. If not You could adjust the source code and play it on Windows.

## Things used
I used dynamic allocation for the snake body, bash-specific, random, and time functions.

## Bugs
-the snake length is limited to 200, I could use realloc() but it was a one-day project ...

-the fruits may overlap with the snake body but it rarely happens since the snake size is limited to 50, so it wasn't worth fixing.
