COMPILER=gcc
FLAGS=-Wall -std=gnu99 -g
LIBS=
SOURCES=validator.c model_calc_functions.c math_functions.c state_creation.c state_container.c tests.c
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

