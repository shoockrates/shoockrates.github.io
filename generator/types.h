#ifndef TYPES_H
#define TYPES_H

#include <stdbool.h>

#define MAX_IP_LENGTH 16
#define BOARD_SIZE 81
#define MAX_PLAYERS 1000
#define FIELD_NUM 250

typedef struct
{
    char ipAddress[16];
    char playerName[50];
    int elapsedSeconds;
    int gamesWon;
    int gamesPlayed;
    float winRate;
    char lastPlayed[25];
} PlayerStats;

typedef struct
{
    bool gameWon;
    int boardSize;
    float minePercentage;
    char timestamp[25];
    bool boardFlat[BOARD_SIZE];
    bool revealedFlat[BOARD_SIZE];
    bool flagsFlat[BOARD_SIZE];
} MatchStats;

typedef struct
{
    PlayerStats *players;
    int playerCount;
} LeaderboardData;

typedef struct
{
    MatchStats *matches;
    int matchCount;
} MatchData;

#endif
