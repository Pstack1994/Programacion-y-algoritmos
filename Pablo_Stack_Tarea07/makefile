# Makefile

# Compiler flags: all warnings + debugger meta-data
CFLAGS = -Wall -g

# Pre-defined macros for conditional compilation
DEFS = -DDEBUG_FLAG -DEXPERIMENTAL=0

# The final executable program file, i.e. name of our program
BIN = arbol_rojonegro

# Object files from which $BIN depends
RUTA= .
OBJS= ${RUTA}/arbol_tarea7.o

# This default rule compiles the executable program
$(BIN): $(OBJS) $(BIN).c
	$(CC) $(CFLAGS) $(DEFS) $(OBJS) $(BIN).c -o $(BIN)

# This rule compiles each module into its object file
%.o: %.c %.h
	$(CC) -c $(CFLAGS) $(DEFS) $< -o $@

clean:
	rm -f *~ *.o $(BIN)
	rm -f ../../*.o

depend:
	makedepend -Y -- $(CFLAGS) $(DEFS) -- *.c
run:
	./$(BIN)

valgrind:
	valgrind --tool=memcheck --leak-check=yes ./$(BIN)
