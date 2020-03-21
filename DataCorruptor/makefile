#
# this makefile will compile and and all source
# found in the ~/develop/DataCorruptor directory.
#
#==============================================
# FINAL BINARY Target
../dataReader/bin/DataCorruptor :	./obj/DataCorruptor.o	 ../Common/obj/logger.o ./obj/DCrrpOutput.o
	cc ./obj/DataCorruptor.o  ../Common/obj/logger.o ./obj/DCrrpOutput.o -o ./bin/DataCorruptor
#
# =======================================================
#                     Dependencies
# =======================================================
./obj/DataCorruptor.o :	./src/DataCorruptor.c ./inc/DataCorruptor.h
	cc -c ./src/DataCorruptor.c -o ./obj/DataCorruptor.o

./obj/DCrrpOutput.o : ./src/DCrrpOutput.c ./inc/DataCorruptor.h
	cc -c ./src/DCrrpOutput.c -o ./obj/DCrrpOutput.o

#
# =======================================================
# Other targets
# =======================================================
all : ../dataReader/bin/DataCorruptor

clean:
	rm -f ./bin/*
	rm -f ./obj/*.o
	rm -f ./inc/*.h~
	rm -f ./src/*.c~
