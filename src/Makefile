FILES=RF_DataProb.cpp RF_Tree.cpp RF_RandomForest.cpp RF_Utils.cpp RF_Train.cpp RF_Test.cpp RF_IO.cpp RF_DataSampleCont.cpp RF_DataSample.cpp
OBJ=${FILES:.cpp=.o}
FLAGS=-Wall -g -O0 -pipe -pedantic `pkg-config --cflags --libs opencv`

EXE=RF_Utils

CC=g++
RM=rm -rf

.PHONY: all clean run

all: $(OBJ)
	$(CC) $(FLAGS) $(LIBS) $(OBJ) -o $(EXE)

#exe: $(EXE)

run:
	./$(EXE)

clean:
	$(RM) *.o

%: %.cpp
	$(CC) -o $@ $^ $(FLAGS) $(LIBS)

#zavislosti

RF_DataProb.o: RF_DataProb.cpp RF_DataProb.h
RF_Tree.o: RF_Tree.cpp RF_Tree.h RF_DataProb.h
RF_RandomForest.cpp: RF_RandomForest.cpp RF_RandomForest.h RF_DataSampleCont.h RF_Tree.h
RF_Utils.o: RF_Utils.cpp RF_Utils.h RF_Train.h RF_Test.h
RF_Train.o: RF_Train.cpp RF_Train.h RF_IO.h RF_DataSampleCont.h RF_RandomForest.h
RF_Test.o: RF_Test.cpp RF_Test.h
RF_IO.o: RF_IO.cpp RF_IO.h RF_DataSampleCont.h RF_DataSample.h RF_RandomForest.h
RF_DataSampleCont.o: RF_DataSampleCont.cpp RF_DataSampleCont.h RF_DataSample.h
RF_DataSample.o: RF_DataSample.cpp RF_DataSample.h


$(EXE): $(FILES) $(DEPS)
