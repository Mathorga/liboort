CCOMP			= gcc
CCOMP_FLAGS		= -std=c++17 -g -fopenmp
CCOMP_LIBS		= -lm -lstdc++ -lrt -lgomp
CLINK_FLAGS		=

BIN_DIR			= ./bin
OORT			= $(BIN_DIR)/Oort
OORT_TEST		= $(BIN_DIR)/OortTest
OORT_TRAIN		= $(BIN_DIR)/OortTrain

RM				= rm -rf

all: clean exe

exe: $(OORT) $(OORT_TEST)

%.o: %.cpp
	$(CCOMP) $(CCOMP_FLAGS) -c $<

$(OORT): Oort.o SimpleBrain.o Model.o utils.o
	$(CCOMP) $(CLINK_FLAGS) $^ -o $@ -lm $(CCOMP_LIBS)

$(OORT_TEST): OortTest.o SimpleBrain.o ModelParser.o Model.o Knowledge.o utils.o
	$(CCOMP) $(CLINK_FLAGS) $^ -o $@ -lm $(CCOMP_LIBS)

clean:
	$(RM) $(BIN_DIR)/*
	$(RM) *.o
	$(RM) *.ppm
	$(RM) *.dat
	$(RM) *.log
