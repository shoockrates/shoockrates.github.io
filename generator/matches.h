#ifndef MATCHES_H
#define MATCHES_H

#include "types.h"
#include <stdbool.h>

extern MatchData matchData;

void add_match(bool game_won, int board_size, float mine_percentage, const char* timestamp, bool* board_flat, bool* revealed_flat, bool* flags_flat);
int compare_matches(const void *a, const void *b);
void cleanup_matches();

#endif
