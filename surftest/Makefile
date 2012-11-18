CC = g++
CFLAGS	= 
LDFLAGS	=
#INCLUDES = -I/usr/local/include/opencv
#LIBS	= -L/usr/local/lib -lcxcore -lcv -lhighgui -lcvaux -lml
INCLUDES  = ${shell pkg-config opencv --cflags} 
LIBS += ${shell pkg-config opencv --libs}

TARGET	= surftest
OBJS	= surftest.o

all:	$(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS) $(LIBS)

clean:
	-rm -f $(TARGET) *.o *~

.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $<


