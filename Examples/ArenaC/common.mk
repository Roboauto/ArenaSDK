CC=g++

INCLUDE = -I../../../include/ArenaC \
          -I../../../include/SaveC

CFLAGS=-Wall -g -O2 -Wno-unknown-pragmas

LDFLAGS = -L../../../lib64 \
          -L../../../GenICam/library/lib/Linux64_x64 \
          -L../../../ffmpeg

LIBS = -larenac \
       -larena \
       -lsavec \
       -lsave \
       -lgentl \
       -lGCBase_gcc421_v3_0 \
       -lGenApi_gcc421_v3_0 \
       -lLog_gcc421_v3_0 \
       -llog4cpp_gcc421_v3_0 \
       -lMathParser_gcc421_v3_0 \
       -lNodeMapData_gcc421_v3_0 \
       -lXmlParser_gcc421_v3_0 \
       -lavcodec \
       -lavdevice \
       -lavfilter \
       -lavformat \
       -lavutil \
       -lswresample \
       -lswscale


RM = rm -f
OUTDIR = ../../../OutputDirectory/Linux/x64Release/

SRCS = $(wildcard *.c)
OBJS = $(SRCS:%.c=%.o)
DEPS = $(OBJS:%.o=%.d)

.PHONY: all
all: ${TARGET}

${TARGET}: ${OBJS}
	${CC} ${LDFLAGS} $^ ${LIBS} -o $@
	-mkdir -p $(OUTDIR)
	-cp $(TARGET) $(OUTDIR)

%.o: %.c ${SRCS}
	${CC} ${INCLUDE}  ${LDFLAGS} ${LIBS} -o $@ $< -c ${CFLAGS}

${DEPS}: %.c
	${CC} ${CLAGS} ${INCLUDE} -MM $< >$@

-include $(OBJS:.o=.d)

.PHONY: clean
clean:
	-${RM} ${TARGET} ${OBJS} ${DEPS}
