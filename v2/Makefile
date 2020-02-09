CCOMP = gcc

STD_CCOMP_FLAGS = -std=c++17 -Wall -pedantic -g -fopenmp
OPENCV_INCLUDES = -Ilib/opencv/include/opencv4
OPENCV_INCLUDES = `pkg-config --cflags opencv`
CCOMP_FLAGS = $(STD_CCOMP_FLAGS) $(OPENCV_INCLUDES)
CLINK_FLAGS =

# OPENNN_LIBS = -L ./lib/opennn -lopennn
GTK_LIBS = `pkg-config --libs gtk+-2.0`
OPENCV_LIBS = `pkg-config --libs opencv`
STD_LIBS = -lstdc++ -lrt -lgomp -lpthread -ldl -lm #-lwiringPi
LIBS = $(OPENCV_LIBS) $(STD_LIBS) #$(OPENNN_LIBS)

SRC_DIR = ./src
BLD_DIR = ./bld
BIN_DIR = ./bin

MKDIR = mkdir -p
RM = rm -rf

all: default

default: create clean defaultExe

#pi: create clean piExe

defaultExe: OortTest

#piExe: OortTest OortImgGrabber OortKnlMaker OortTrainer OortPi

%.o: $(SRC_DIR)/%.cpp
	$(CCOMP) $(CCOMP_FLAGS) -c $^ -o $(BLD_DIR)/$@

OortTest: OortTest.o \
		  Model.o \
		  GDTrainer.o \
		  Trainer.o \
		  utils.o \
		  math.o
	$(CCOMP) $(CLINK_FLAGS) $(patsubst %.o, $(BLD_DIR)/%.o, $^) -o $(BIN_DIR)/$@ $(LIBS)

create:
	$(MKDIR) $(BLD_DIR)
	$(MKDIR) $(BIN_DIR)

clean:
	$(RM) $(BLD_DIR)/*
	$(RM) $(BIN_DIR)/*
