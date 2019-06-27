CCOMP = gcc

STD_CCOMP_FLAGS = -std=c++17 -g -fopenmp
OPENCV_INCLUDES = -Ilib/opencv/include/opencv4
#GTK_INCLUDES = `pkg-config --cflags gtk+-2.0`
GTK_INCLUDES = -pthread -I/usr/include/gtk-2.0 \
						-I/usr/lib/x86_64-linux-gnu/gtk-2.0/include \
						-I/usr/include/gio-unix-2.0/ \
						-I/usr/include/cairo \
						-I/usr/include/pango-1.0 \
						-I/usr/include/atk-1.0 \
						-I/usr/include/cairo \
						-I/usr/include/pixman-1 \
						-I/usr/include/libpng12 \
						-I/usr/include/gdk-pixbuf-2.0 \
						-I/usr/include/libpng12 \
						-I/usr/include/pango-1.0 \
						-I/usr/include/harfbuzz \
						-I/usr/include/pango-1.0 \
						-I/usr/include/glib-2.0 \
						-I/usr/lib/x86_64-linux-gnu/glib-2.0/include \
						-I/usr/include/freetype2
CCOMP_COMPLETE_FLAGS = $(STD_CCOMP_FLAGS) $(OPENCV_INCLUDES) $(GTK_INCLUDES)
CCOMP_HEADLESS_FLAGS = $(STD_CCOMP_FLAGS) $(OPENCV_INCLUDES)
CCOMP_FLAGS = $(CCOMP_COMPLETE_FLAGS)
CLINK_FLAGS =

OPENNN_LIBS = -L ./lib/opennn -lopennn
#GTK_LIBS = `pkg-config --libs gtk+-2.0`
GTK_LIBS = -lgtk-x11-2.0 \
		   -lgdk-x11-2.0 \
		   -lpangocairo-1.0 \
		   -latk-1.0 \
		   -lcairo \
		   -lgdk_pixbuf-2.0 \
		   -lgio-2.0 \
		   -lpangoft2-1.0 \
		   -lpango-1.0 \
		   -lgobject-2.0 \
		   -lglib-2.0 \
		   -lfontconfig \
		   -lfreetype
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

exe: OortTest OortTrainer OortImgGrabber #OortNNTest Oort

%.o: $(SRC_DIR)/%.cpp
	$(CCOMP) $(CCOMP_FLAGS) -c $^ -o $(BLD_DIR)/$@

Oort: Oort.o \
	  SimpleBrain.o \
	  Model.o \
	  utils.o
	$(CCOMP) $(CLINK_FLAGS) $(patsubst %.o, $(BLD_DIR)/%.o, $^) -o $(BIN_DIR)/$@ $(STD_LIBS)

OortTrainer: OortTrainer.o \
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

OortTest: OortTest.o \
		  Knowledge.o \
		  utils.o \
		  Model.o \
		  Neuron.o \
		  WeightedModel.o \
		  SparsePerceptronModelParser.o \
		  SparsePerceptronModel.o \
		  SparsePerceptronNetwork.o \
		  LayeredPerceptronModel.o \
		  PerceptronSynapse.o \
		  Synapse.o \
		  Perceptron.o
	$(CCOMP) $(CLINK_FLAGS) $(patsubst %.o, $(BLD_DIR)/%.o, $^) -o $(BIN_DIR)/$@ $(STD_LIBS)

OortNNTest: OortNNTest.o utils.o
	$(CCOMP) $(CLINK_FLAGS) $(patsubst %.o, $(BLD_DIR)/%.o, $^) -o $(BIN_DIR)/$@ $(LIBS)

OortImgGrabber: OortImgGrabber.o utils.o
	$(CCOMP) $(CLINK_FLAGS) $(patsubst %.o, $(BLD_DIR)/%.o, $^) -o $(BIN_DIR)/$@ $(LIBS)

create:
	$(MKDIR) $(BLD_DIR)
	$(MKDIR) $(BIN_DIR)

clean:
	$(RM) $(BLD_DIR)/*
	$(RM) $(BIN_DIR)/*
