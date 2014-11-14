COMPILER=gcc
FLAGS=-Wall -std=gnu99 -g
LIBS=
SOURCES=src/alidator.c src/model_calc_functions.c src/math_functions.c src/state_creation.c src/state_container.c src/tests.c
EXEC=validator

all:
	$(COMPILER) $(FLAGS) $(LIBS) $(SOURCES) -o $(EXEC)

clean:
	@if [ -f $(EXEC) ] ; then rm $(EXEC) && echo "removed $(EXEC)" ; fi
	
tests:
	make all
	./validator -t 10
	./validator -t 11
	./validator -t 12

