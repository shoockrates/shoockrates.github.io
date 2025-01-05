#include "csv_parser.h"
#include "leaderboard.h"
#include "html_generator.h"
#include "types.h"
#include "minestats.h"
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s <input.csv> <output.html>\n", argv[0]);
        return 1;
    }

    initialize_minestats();
    parse_csv_file(argv[1]);
    if (strcmp(argv[2], "../frontend/leaderboard.html") == 0)
    {
        generate_leaderboard_html(argv[2]);
    }
    else
    {
        generate_matches_html(argv[2]);
    }
    cleanup_minestats();

    return 0;
}