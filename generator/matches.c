#include "matches.h"
#include <stdlib.h>
#include <string.h>

MatchData match_data = {NULL, 0};

void add_match(bool game_won, int board_size, float mine_percentage, const char* timestamp, bool* board_flat, bool* revealed_flat, bool* flags_flat)
{
    match_data.matchCount++;
    match_data.matches = realloc(match_data.matches, match_data.matchCount * sizeof(MatchStats));
    
    MatchStats* new_match = &match_data.matches[match_data.matchCount - 1];
    new_match->gameWon = game_won;
    new_match->boardSize = board_size;
    new_match->minePercentage = mine_percentage;
    
    strncpy(new_match->timestamp, timestamp, sizeof(new_match->timestamp) - 1);
    new_match->timestamp[sizeof(new_match->timestamp) - 1] = '\0';
    
    memcpy(new_match->boardFlat, board_flat, BOARD_SIZE * sizeof(bool));
    memcpy(new_match->revealedFlat, revealed_flat, BOARD_SIZE * sizeof(bool));
    memcpy(new_match->flagsFlat, flags_flat, BOARD_SIZE * sizeof(bool));

    cleanup_matches();
}

int compare_matches(const void *a, const void *b)
{
    const MatchStats *matchA = (const MatchStats *)a;
    const MatchStats *matchB = (const MatchStats *)b;
    return strcmp(matchB->timestamp, matchA->timestamp);
}

void cleanup_matches()
{
    free(match_data.matches);
    match_data.matches = NULL;
    match_data.matchCount = 0;
}
