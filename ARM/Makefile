CCOMP			= gcc

CCOMP_FLAGS		= -std=c++17 -g -fopenmp -Ilib/opencv/include/opencv4 `pkg-config --cflags gtk+-2.0`
CLINK_FLAGS		=

OPENNN_LIBS		= -L ./lib/opennn -lopennn
OPENCV_3P_LIBS	= -L ./lib/opencv/lib/opencv4/3rdparty -lade \
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
													   -lzlib \
													   `pkg-config --libs gtk+-2.0`
OPENCV_LIBS		= -L ./lib/opencv/lib -lopencv_video \
									  -lopencv_videoio \
									  -lopencv_imgcodecs \
									  -lopencv_imgproc \
									  -lopencv_core \
									  -lopencv_highgui \
									  -lopencv_video \
									  -lopencv_videoio \
									  -lopencv_objdetect \
									  $(OPENCV_3P_LIBS)
#OPENCV_LIBS		= `pkg-config --libs opencv`
LIBS			= $(OPENNN_LIBS) $(OPENCV_LIBS) -lstdc++ -lrt -lgomp -lpthread -ldl -lm

SRC_DIR			= ./src
BLD_DIR			= ./bld
BIN_DIR			= ./bin

RM				= rm -rf

all: clean exe

exe: OortTest OortCVTest #OortNNTest Oort

%.o: $(SRC_DIR)/%.cpp
	$(CCOMP) $(CCOMP_FLAGS) -c $^ -o $(BLD_DIR)/$@

Oort: Oort.o SimpleBrain.o Model.o utils.o
	$(CCOMP) $(CLINK_FLAGS) $(patsubst %.o, $(BLD_DIR)/%.o, $^) -o $(BIN_DIR)/$@ $(LIBS)

OortTest: OortTest.o SimpleBrain.o ModelParser.o Model.o Knowledge.o utils.o
	$(CCOMP) $(CLINK_FLAGS) $(patsubst %.o, $(BLD_DIR)/%.o, $^) -o $(BIN_DIR)/$@ $(LIBS)

OortNNTest: OpenNNTest.o utils.o
	$(CCOMP) $(CLINK_FLAGS) $(patsubst %.o, $(BLD_DIR)/%.o, $^) -o $(BIN_DIR)/$@ $(LIBS)

OortCVTest: OortCVTest.o utils.o
	$(CCOMP) $(CLINK_FLAGS) $(patsubst %.o, $(BLD_DIR)/%.o, $^) -o $(BIN_DIR)/$@ $(LIBS)

clean:
	$(RM) $(BIN_DIR)/*
	$(RM) $(BLD_DIR)/*
