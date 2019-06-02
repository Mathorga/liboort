CCOMP = gcc

STD_CCOMP_FLAGS = -std=c++17 -g -fopenmp
OPENCV_INCLUDES = -Ilib/opencv/include/opencv4
GTK_INCLUDES = `pkg-config --cflags gtk+-2.0`
CCOMP_COMPLETE_FLAGS = $(STD_CCOMP_FLAGS) $(OPENCV_INCLUDES) $(GTK_INCLUDES)
CCOMP_HEADLESS_FLAGS = $(STD_CCOMP_FLAGS) $(OPENCV_INCLUDES)
CCOMP_FLAGS = $(CCOMP_COMPLETE_FLAGS)
CLINK_FLAGS =

OPENNN_LIBS = -L ./lib/opennn -lopennn
GTK_LIBS = `pkg-config --libs gtk+-2.0`
OPENCV_3P_LIBS = -L ./lib/opencv/lib/opencv4/3rdparty -lade \
                                                      -lIlmImf \
                                                      -lippiw \
                                                      -lippicv \
                                                      -littnotify \
                                                      -llibjasper \
                                                      -llibjpeg-turbo \
                                                      -llibpng \
                                                      -llibprotobuf \
                                                      -llibtiff \
                                                      -llibwebp \
                                                      -lquirc \
                                                      -lzlib
OPENCV_LIBS = -L ./lib/opencv/lib -lopencv_video \
                                  -lopencv_videoio \
                                  -lopencv_imgcodecs \
                                  -lopencv_imgproc \
                                  -lopencv_core \
                                  -lopencv_highgui \
                                  -lopencv_video \
                                  -lopencv_videoio \
                                  -lopencv_objdetect \
                                  $(OPENCV_3P_LIBS)
#OPENCV_LIBS = `pkg-config --libs opencv`
STD_LIBS = -lstdc++ -lrt -lgomp -lpthread -ldl -lm
HEADLESS_LIBS = $(OPENNN_LIBS) $(OPENCV_LIBS) $(STD_LIBS)
COMPLETE_LIBS = $(OPENNN_LIBS) $(OPENCV_LIBS) $(GTK_LIBS) $(STD_LIBS)
LIBS = $(COMPLETE_LIBS)

SRC_DIR = ./src
BLD_DIR = ./bld
BIN_DIR = ./bin

MKDIR = mkdir -p
RM = rm -rf

# Check if headless build.
ifeq ($(BUILD), headless)
	CCOMP_FLAGS = $(CCOMP_HEADLESS_FLAGS)
	LIBS = $(HEADLESS_LIBS)
endif

all: create clean exe

exe: OortTest #OortCVTest OortNNTest Oort

%.o: $(SRC_DIR)/%.cpp
	$(CCOMP) $(CCOMP_FLAGS) -c $^ -o $(BLD_DIR)/$@

Oort: Oort.o \
	  SimpleBrain.o \
	  Model.o \
	  utils.o
	$(CCOMP) $(CLINK_FLAGS) $(patsubst %.o, $(BLD_DIR)/%.o, $^) -o $(BIN_DIR)/$@ $(STD_LIBS)

OortTest: OortTest.o \
		  SimpleBrain.o \
		  SimpleModelParser.o \
		  SimpleModel.o \
		  Knowledge.o \
		  utils.o \
		  Model.o \
		  Neuron.o \
		  WeightedModel.o \
		  SparsePerceptronModelParser.o \
		  SparsePerceptronModel.o \
		  SparsePerceptronNetwork.o \
		  PerceptronSynapse.o \
		  Synapse.o \
		  Perceptron.o
	$(CCOMP) $(CLINK_FLAGS) $(patsubst %.o, $(BLD_DIR)/%.o, $^) -o $(BIN_DIR)/$@ $(STD_LIBS)

OortNNTest: OpenNNTest.o utils.o
	$(CCOMP) $(CLINK_FLAGS) $(patsubst %.o, $(BLD_DIR)/%.o, $^) -o $(BIN_DIR)/$@ $(LIBS)

OortCVTest: OortCVTest.o utils.o
	$(CCOMP) $(CLINK_FLAGS) $(patsubst %.o, $(BLD_DIR)/%.o, $^) -o $(BIN_DIR)/$@ $(LIBS)

create:
	$(MKDIR) $(BLD_DIR)
	$(MKDIR) $(BIN_DIR)

clean:
	$(RM) $(BLD_DIR)/*
	$(RM) $(BIN_DIR)/*
