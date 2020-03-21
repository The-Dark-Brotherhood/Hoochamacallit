#
# this makefile will call all the makefiles required
# for the Hoochamacallit system.
#
#==============================================

./bin:
	cd dataReader    && make && cp ./bin/DataReader ../Common/bin
	cd DataCorruptor && make && cp ./bin/DataCorruptor ../Common/bin
	cd DataCreator   && make && cp ./bin/DataCreatorsss ../Common/bin

#
# =======================================================
# Other targets
# =======================================================
all : ./bin/Hoochamacallit/

clean:
	rm -f ./bin/*
	rm -f ./obj/*.o
	rm -f ./inc/*.h~
	rm -f ./src/*.c~
	rm -f ./dataReader/bin/*
	rm -f ./dataReader/obj/*.o
	rm -f ./dataReader/inc/*.h~
	rm -f ./dataReader/src/*.c~
	rm -f ./DataCreator/bin/*
	rm -f ./DataCreator/obj/*.o
	rm -f ./DataCreator/inc/*.h~
	rm -f ./DataCreator/src/*.c~
	rm -f ./DataCorruptor/bin/*
	rm -f ./DataCorruptor/obj/*.o
	rm -f ./DataCorruptor/inc/*.h~
	rm -f ./DataCorruptor/src/*.c~
