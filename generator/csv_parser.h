#ifndef CSV_PARSER_H
#define CSV_PARSER_H

#include "csv.h"
#include "types.h"
#include "leaderboard.h"
#include "matches.h"

typedef enum
{
    FIELD_IP_ADDRESS,
    FIELD_PLAYER_NAME,
    FIELD_ELAPSED_SECONDS,
    FIELD_TIMESTAMP,
    FIELD_GAME_WON,
    FIELD_BOARD_SIZE,
    FIELD_MINE_PERCENTAGE,
    FIELD_BOARD_FLAT_START,
    FIELD_REVEALED_FLAT_START = BOARD_SIZE + FIELD_BOARD_FLAT_START,
    FIELD_FLAGS_FLAT_START = BOARD_SIZE + FIELD_REVEALED_FLAT_START,
} FieldIndex;

extern PlayerStats *tempPlayer;
extern MatchStats *tempMatch;

void cb_field(void *field, size_t field_len, void *data);
void cb_row(int c, void *data);

#endif