CC = gcc
CFLAGS = -I.
BIN_FILE = main

default: main.c dijkstra_func.c aux_funcs.c graph_bib.h
	@echo "Compiling" main "..."
	$(CC) $(CFLAGS) -o ${BIN_FILE} main.c dijkstra_func.c aux_funcs.c -lpthread #-DGERA_ARQ
	@echo "done!"
clean:
	rm -f ${BIN_FILE}
