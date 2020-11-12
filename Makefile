CC = g++

# -g	adds debugging information to the executable file
# -Wall turns on most, but not all, compiler warnings
CFLAGS = -g -Wall

INC=/FileManager/include/

VPATH = FileManager/src

OBJECTS = $(VPATH)/emlreader/EMLReader.o Search.o main.o

BUILDDIR = build

define cc-command
$(CC) $(INC) $< -o $@
endef

all: FileManager

%.o: %.cpp
	$(cc-command)

FileManager: $(OBJECTS)
	$(CC) $(CFLAGS) $? -o $@

clean:
	$(RM) $(TARGET) *.o *~