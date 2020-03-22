#
# this makefile will compile and and all source
# found in the dataReader directory.
#
#==============================================

# FINAL BINARY Target
./bin/DataReader : ./obj/dataReader.o ../Common/obj/logger.o  ./obj/DClist.o  ./obj/DROutput.o
	cc ./obj/dataReader.o ../Common/obj/logger.o  ./obj/DClist.o ./obj/DROutput.o -o  ./bin/DataReader
#
# =======================================================
#                     Dependencies
# =======================================================

./obj/dataReader.o : ./src/dataReader.c  ./inc/dataReader.h
	cc -c ./src/dataReader.c -o  ./obj/dataReader.o

./obj/DROutput.o : ./src/DROutput.c  ./inc/dataReader.h
	cc -c ./src/DROutput.c -o  ./obj/DROutput.o

./obj/DClist.o : ./src/DClist.c ./inc/dataReader.h
	cc -c ./src/DClist.c -o ./obj/DClist.o

#
# =======================================================
# Other targets
# =======================================================
all : ./bin/dataReader

clean:
	rm -f ./bin/*
	rm -f ./obj/*.o
	rm -f ./inc/*.h~
	rm -f ./src/*.c~
