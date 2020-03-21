#
# FILE : makefile
# PROJECT :  A-03: Hoochamacallit DataCreator
# PROGRAMMER : Michael Gordon & Gabriel Gurgel
# FIRST VERSION : 2020-03-12
# DESCRIPTION : This makefile is from the MyApp Example provided in the SET Program
#
# FINAL BINARY Target
./bin/DataCreator :	./obj/DataCreator.o  ../Common/obj/logger.o	./obj/DCOutput.o
	cc ./obj/DataCreator.o ../Common/obj/logger.o	./obj/DCOutput.o -o	./bin/DataCreator
#
# =======================================================
#                     Dependencies
# =======================================================
./obj/DataCreator.o :	./src/DataCreator.c  ./inc/DataCreator.h
	cc -c ./src/DataCreator.c -o ./obj/DataCreator.o

./obj/DCOutput.o : ./src/DCOutput.c ./inc/DataCreator.h
	cc -c ./src/DCOutput.c -o ./obj/DCOutput.o

#
# =======================================================
# Other targets
# =======================================================
all : ./bin/DataCreator

clean:
	rm -f ./bin/*
	rm -f ./obj/*.o
	rm -f ./inc/*.h~
	rm -f ./src/*.c~
