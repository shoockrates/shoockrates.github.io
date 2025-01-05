#ifndef HTML_GENERATOR_H
#define HTML_GENERATOR_H

#include <stdio.h>
#include "types.h"

void write_leaderboard_html_header(FILE *html_file);
void write_leaderboard_html_body(FILE *html_file);
void write_player_data(FILE *html_file, int rank, PlayerStats *player);
void write_leaderboard_html_footer(FILE *html_file);
void write_matches_html_header(FILE *html_file);
void write_matches_html_body(FILE *html_file);
void write_matches_data(FILE *html_file, int rank, MatchStats *match);
void write_match_board_page(FILE *html_file, MatchStats *match, int rank);
void write_matches_html_footer(FILE *html_file);

#endif