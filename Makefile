CC = g++
CFLAGS	= 
LDFLAGS	=
#INCLUDES = -I/usr/local/include/opencv
#LIBS	= -L/usr/local/lib -lcxcore -lcv -lhighgui -lcvaux -lml
INCLUDES  = ${shell pkg-config opencv --cflags} 
LIBS += ${shell pkg-config opencv --libs}

TARGET = kadai3 kadai5

all:	$(TARGET)


$(TARGET):%: %.o
	$(CC) $(LDFLAGS) -o $@ $^ $(LIBS)


.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $<

clean:
	-rm -f $(TARGET) *.o *~

