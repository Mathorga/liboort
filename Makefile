CCOMP = gcc

STD_CCOMP_FLAGS = -std=c++17 -g -fopenmp
OPENCV_INCLUDES = -Ilib/opencv/include/opencv4
OPENCV_INCLUDES = `pkg-config --cflags opencv`
CCOMP_FLAGS = $(STD_CCOMP_FLAGS) $(OPENCV_INCLUDES)
CLINK_FLAGS =

# OPENNN_LIBS = -L ./lib/opennn -lopennn
GTK_LIBS = `pkg-config --libs gtk+-2.0`
OPENCV_LIBS = `pkg-config --libs opencv`
STD_LIBS = -lstdc++ -lrt -lgomp -lpthread -ldl -lm
LIBS = $(OPENCV_LIBS) $(STD_LIBS) #$(OPENNN_LIBS)

SRC_DIR = ./src
BLD_DIR = ./bld
BIN_DIR = ./bin

MKDIR = mkdir -p
RM = rm -rf

all: create clean exe

exe: OortTest OortImgGrabber OortKnlMaker OortTrainer Oort #OortNNTest
%.o: $(SRC_DIR)/%.cpp
	$(CCOMP) $(CCOMP_FLAGS) -c $^ -o $(BLD_DIR)/$@

Oort: Oort.o \
	  utils.o \
	  Model.o \
	  Neuron.o \
	  SparsePerceptronModelParser.o \
	  SparsePerceptronModel.o \
	  SparsePerceptronNetwork.o \
	  LayeredPerceptronModel.o \
	  LayeredPerceptronNetwork.o \
	  PerceptronSynapse.o \
	  Synapse.o \
	  Perceptron.o \
	  KnowledgeParser.o \
	  Knowledge.o \
	  Experience.o
	$(CCOMP) $(CLINK_FLAGS) $(patsubst %.o, $(BLD_DIR)/%.o, $^) -o $(BIN_DIR)/$@ $(LIBS)

OortTest: OortTest.o \
		  utils.o \
		  Model.o \
		  Neuron.o \
		  SparsePerceptronModelParser.o \
		  SparsePerceptronModel.o \
		  SparsePerceptronNetwork.o \
		  LayeredPerceptronModel.o \
		  LayeredPerceptronNetwork.o \
		  PerceptronSynapse.o \
		  Synapse.o \
		  Perceptron.o \
		  KnowledgeParser.o \
		  Knowledge.o \
		  Experience.o
	$(CCOMP) $(CLINK_FLAGS) $(patsubst %.o, $(BLD_DIR)/%.o, $^) -o $(BIN_DIR)/$@ $(LIBS)

# OortNNTest: OortNNTest.o utils.o
# 	$(CCOMP) $(CLINK_FLAGS) $(patsubst %.o, $(BLD_DIR)/%.o, $^) -o $(BIN_DIR)/$@ $(LIBS)

OortImgGrabber: OortImgGrabber.o \
				utils.o
	$(CCOMP) $(CLINK_FLAGS) $(patsubst %.o, $(BLD_DIR)/%.o, $^) -o $(BIN_DIR)/$@ $(LIBS)

OortKnlMaker: OortKnlMaker.o \
			  utils.o \
			  Experience.o \
			  Knowledge.o \
			  KnowledgeParser.o \
			  Neuron.o
	$(CCOMP) $(CLINK_FLAGS) $(patsubst %.o, $(BLD_DIR)/%.o, $^) -o $(BIN_DIR)/$@ $(LIBS)

OortTrainer: OortTrainer.o \
			 utils.o \
			 Perceptron.o \
			 Synapse.o \
			 PerceptronSynapse.o \
			 Model.o \
			 SparsePerceptronModel.o \
			 SparsePerceptronNetwork.o \
			 SparsePerceptronModelParser.o \
			 Knowledge.o \
			 Experience.o \
			 KnowledgeParser.o \
			 Neuron.o
	$(CCOMP) $(CLINK_FLAGS) $(patsubst %.o, $(BLD_DIR)/%.o, $^) -o $(BIN_DIR)/$@ $(LIBS)

create:
	$(MKDIR) $(BLD_DIR)
	$(MKDIR) $(BIN_DIR)

clean:
	$(RM) $(BLD_DIR)/*
	$(RM) $(BIN_DIR)/*
