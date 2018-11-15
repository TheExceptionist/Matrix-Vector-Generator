exe_name = generator
compiler = g++
objects = main.o 
flags = -Wall

$(exe_name) : $(objects)
	$(compiler) $(flags) -o $(exe_name) $(objects)
	make clean	

$(objects) : defs.h e_math.h

.PHONY: clean \
	reset

clean: 
	rm *.o

reset:
	rm *.o
	rm $(exe_name)
