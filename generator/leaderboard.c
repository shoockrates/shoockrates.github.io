#include "leaderboard.h"
#include "csv_parser.h"
#include <string.h>

LeaderboardData leaderboard = {0};

void update_player_stats(const char *ipAddress, int elapsedSeconds, const char *timestamp, bool gameWon)
{
    // Randame esantį žaidėją
    for (int i = 0; i < leaderboard.playerCount; i++)
    {
        if (strcmp(leaderboard.players[i].ipAddress, ipAddress) == 0)
        {
            // Atnaujiname statistiką, jei laikas geresnis
            if (elapsedSeconds < leaderboard.players[i].elapsedSeconds && gameWon)
            {
                leaderboard.players[i].elapsedSeconds = elapsedSeconds;
            }
            leaderboard.players[i].gamesWon += gameWon ? 1 : 0;
            leaderboard.players[i].gamesPlayed++;
            leaderboard.players[i].winRate = ((float)leaderboard.players[i].gamesWon / leaderboard.players[i].gamesPlayed) * 100.0f;
            strcpy(leaderboard.players[i].lastPlayed, timestamp);
            return;
        }
    }

    // Pridedame naują žaidėją
    if (leaderboard.playerCount < MAX_PLAYERS)
    {
        int i = leaderboard.playerCount;
        strcpy(leaderboard.players[i].ipAddress, ipAddress);
        leaderboard.players[i].elapsedSeconds = gameWon ? elapsedSeconds : 1000000000;
        leaderboard.players[i].gamesWon = gameWon ? 1 : 0;
        leaderboard.players[i].gamesPlayed = 1;
        leaderboard.players[i].winRate = leaderboard.players[i].gamesWon * 100.0f;
        strcpy(leaderboard.players[i].lastPlayed, timestamp);
        leaderboard.playerCount++;
    }
}

int compare_players(const void *a, const void *b)
{
    const PlayerStats *playerA = (const PlayerStats *)a;
    const PlayerStats *playerB = (const PlayerStats *)b;
    return playerA->elapsedSeconds - playerB->elapsedSeconds;
}