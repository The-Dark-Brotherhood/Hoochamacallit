#
# this makefile will compile the objects required
#	for the Hoochamacallit system
#
#==============================================

./obj/logger.o : ./src/logger.c  ./inc/logger.h
	cc -c ./src/logger.c -o  ./obj/logger.o

#
# =======================================================
# Other targets
# =======================================================
all : ./bin/logger

clean:
	rm -f ./obj/*.o
	rm -f ./inc/*.h~
	rm -f ./src/*.c~
