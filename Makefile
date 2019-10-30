CC= gcc
CFLAGS= -c -Wvla -Wall
CODEFILES= ex2.tar README Draw2DCharArray.c Separator.c SeparationMap.c Makefile
IOFILEPATH= /cs/course/2013/slabc/public/ex2/inputOutput/


# All Target
all: DrawArrayDriver SeparationMap

# Exceutables
DrawArrayDriver: DrawArrayDriver.o Draw2DCharArray.o
	$(CC) DrawArrayDriver.o Draw2DCharArray.o -o DrawArrayDriver

SeparationMap: Draw2DCharArray.o Separator.o SeparationMap.o
	$(CC) -lmath Draw2DCharArray.o Separator.o SeparationMap.o -o SeparationMap
	
# Object Files

DrawArrayDriver.o: DrawArrayDriver.c Draw2DCharArray.h
	$(CC) $(CFLAGS) DrawArrayDriver.c -o DrawArrayDriver.o
	 
Draw2DCharArray.o: Draw2DCharArray.c Draw2DCharArray.h
	$(CC) $(CFLAGS) Draw2DCharArray.c -o Draw2DCharArray.o

Separator.o: Separator.c Separator.h
	$(CC) $(CFLAGS) Separator.c -o Separator.o

SeparationMap.o: SeparationMap.c Separator.h Draw2DCharArray.h
	$(CC) $(CFLAGS) SeparationMap.c -o SeparationMap.o

# tar
tar:
	tar -cf $(CODEFILES)

# test
test1: SeparationMap
	SeparationMap $(IOFILEPATH)data_points_2.in $(IOFILEPATH)separator_2.in 0 1 > myOutput.txt
	diff myOutput.txt $(IOFILEPATH)map_data_2_separator_2_x_0_y_1.out

# Other Targets
clean:
	-rm -f *.o DrawArrayDriver SeparationMap

# Things that aren't really build targets
.PHONY: clean

