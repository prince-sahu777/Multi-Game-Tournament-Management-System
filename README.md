# Multi-Game Tournament Management System

A beginner-friendly, intermediate-level C++ console application for managing esports players, teams, tournaments, match points, rankings, and winners.

## Supported games

- BGMI
- Free Fire
- Valorant
- Counter-Strike 2 (CS2)

## Features

- Register and search players
- Create and display teams
- Create and display tournaments
- Register teams only in tournaments for the same game
- Enter match points for registered teams
- Calculate tournament-specific rankings
- Declare a winner (including ties)
- Save players, teams, tournaments, registrations, and scores to text files
- Validate basic numeric input and duplicate IDs

## Requirements

- C++ compiler supporting C++11 or newer (G++, MinGW, or Clang)
- Visual Studio Code is optional

## Project structure

```text
Multi-Game-Tournament-Management-System/
├── src/
│   └── main.cpp
├── data/
│   ├── .gitkeep
│   ├── players.txt
│   ├── teams.txt
│   ├── tournaments.txt
│   ├── registrations.txt
│   └── scores.txt
├── docs/
│   └── PROJECT_OVERVIEW.md
├── .gitignore
├── LICENSE
└── README.md
```

## Compile and run

Open a terminal in the project root folder.

### Windows (MinGW / G++)

```bash
g++ -std=c++11 -Wall -Wextra src/main.cpp -o gaming_tournament.exe
gaming_tournament.exe
```

### Linux / macOS

```bash
g++ -std=c++11 -Wall -Wextra src/main.cpp -o gaming_tournament
./gaming_tournament
```

**Important:** Run the program from the project root directory so it can find the `data/` folder when saving records.

## Suggested demo workflow

1. Register players and select their games.
2. Create teams for a supported game.
3. Create a tournament for that same game.
4. Register matching teams in the tournament.
5. Enter points for each registered team.
6. Display rankings and declare the winner.
7. Select **Save records** to write the data files.

## Data persistence note

This version saves records to text files when you choose **Save records**. It does **not** automatically reload saved records when the program starts. Data is stored separately by tournament for scoring, so a team's points in one tournament do not affect its points in another. Add file-loading functions as a future enhancement if automatic persistence is required.

## Concepts demonstrated

- Structures and classes
- Encapsulation through a manager class
- Constructors for initializing player, team, and tournament objects
- Vectors and maps from the C++ Standard Library
- Functions and references
- Searching and sorting
- Text file handling
- Input validation
- Tournament-specific scoring

## Future improvements

- Load saved records automatically at startup
- Edit and delete players and teams
- Assign players to team rosters
- Add dates, entry fees, and tournament status
- Store individual match history
- Add a GUI or database in a later version
