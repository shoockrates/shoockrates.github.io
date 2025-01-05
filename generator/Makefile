CC = gcc
CFLAGS = -O2
LDFLAGS = -lcsv
SRC = main.c minestats.c leaderboard.c matches.c html_generator.c csv_parser.c enigma_html.c
OBJ = $(SRC:.c=.o)
TARGET = gen

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)