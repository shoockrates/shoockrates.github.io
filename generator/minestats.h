#ifndef MINESTATS_H
#define MINESTATS_H

void initialize_minestats();
void parse_csv_file(const char *filename);
void generate_leaderboard_html(const char *filename);
void generate_matches_html(const char *filename);
void cleanup_minestats();

#endif