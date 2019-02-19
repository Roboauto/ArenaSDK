CC=g++

INCLUDE= -I../../../include/Arena \
         -I../../../include/Save \
         -I../../../include/GenTL \
         -I../../../GenICam/library/CPP/include

CFLAGS=-Wall -g -O2 -std=c++11 -Wno-unknown-pragmas

LDFLAGS = -L../../../lib64 \
          -L../../../GenICam/library/lib/Linux64_x64 \
          -L../../../ffmpeg


GENICAMLIBS = -lGCBase_gcc421_v3_0 \
              -lGenApi_gcc421_v3_0 \
              -lLog_gcc421_v3_0 \
              -llog4cpp_gcc421_v3_0 \
              -lMathParser_gcc421_v3_0 \
              -lNodeMapData_gcc421_v3_0 \
              -lXmlParser_gcc421_v3_0

FFMPEGLIBS = -lavcodec \
             -lavdevice \
             -lavfilter \
             -lavformat \
             -lavutil \
             -lswresample \
             -lswscale

LIBS= -larena -lsave -lgentl $(GENICAMLIBS) $(FFMPEGLIBS)
RM = rm -f
OUTDIR = ../../../OutputDirectory/Linux/x64Release/

SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:%.cpp=%.o)
DEPS = $(OBJS:%.o=%.d)

.PHONY: all
all: ${TARGET}

${TARGET}: ${OBJS}
	${CC} ${LDFLAGS} $^ -o $@ $(LIBS)
	-mkdir -p $(OUTDIR)
	-cp $(TARGET) $(OUTDIR)

%.o: %.cpp ${SRCS}
	${CC} ${INCLUDE}  ${LDFLAGS} -o $@ $< -c ${CFLAGS}

${DEPS}: %.cpp
	${CC} ${CLAGS} ${INCLUDE} -MM $< >$@

-include $(OBJS:.o=.d)

.PHONY: clean
clean:
	-${RM} ${TARGET} ${OBJS} ${DEPS}
