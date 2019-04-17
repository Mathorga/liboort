CCOMP			= gcc
CCOMP_FLAGS		= -std=c++17 -g -fopenmp -Ilib/opencv/include/opencv4 `pkg-config --cflags gtk+-2.0`
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
CLINK_FLAGS		=

BIN_DIR			= ./bin
OORT			= $(BIN_DIR)/Oort
OORT_TEST		= $(BIN_DIR)/OortTest
OORT_TRAIN		= $(BIN_DIR)/OortTrain
OORTNN_TEST		= $(BIN_DIR)/OortNNTest
OORTCV_TEST		= $(BIN_DIR)/OortCVTest
SPIKING_TEST	= $(BIN_DIR)/SpikingTest

RM				= rm -rf

all: clean exe

exe: $(OORT_TEST) $(OORTCV_TEST) #$(OORTNN_TEST) $(OORT) $(OPENNN_TEST)

%.o: %.cpp
	$(CCOMP) $(CCOMP_FLAGS) -c $<

$(OORT): Oort.o SimpleBrain.o Model.o utils.o
	$(CCOMP) $(CLINK_FLAGS) $^ -o $@ $(LIBS)

$(OORT_TEST): OortTest.o SimpleBrain.o ModelParser.o Model.o Knowledge.o utils.o
	$(CCOMP) $(CLINK_FLAGS) $^ -o $@ $(LIBS)

$(OPENNN_TEST): OpenNNTest.o utils.o
	$(CCOMP) $(CLINK_FLAGS) $^ -o $@ $(LIBS)

$(OORTNN_TEST): OortNNTest.o utils.o
	$(CCOMP) $(CLINK_FLAGS) $^ -o $@ $(LIBS)

$(OORTCV_TEST): OortCVTest.o utils.o
	$(CCOMP) $(CLINK_FLAGS) $^ -o $@ $(LIBS)

clean:
	$(RM) $(BIN_DIR)/*
	$(RM) *.o
	$(RM) *.ppm
	$(RM) *.dat
	$(RM) *.log
