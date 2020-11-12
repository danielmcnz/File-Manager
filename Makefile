.SUFFIXES:

CC = clang++

# -g	adds debugging information to the executable file
# -Wall turns on most, but not all, compiler warnings
CFLAGS = --std=c++17 -g -Wall

INC=-IFileManager/include/

VPATH = FileManager/src

CPP_FILES := $(wildcard $(VPATH)/*/*.cpp)
OBJ_FILES := $(patsubst $(VPATH)/%,build/%,$(CPP_FILES:.cpp=.o))

TARGET = test

.PHONY: all clean

all: $(TARGET) $(CPP_FILES)

$(OBJ_FILES): build/%.o: $(VPATH)/%.cpp $(CPP_FILES)

$(TARGET): $(OBJ_FILES)
	mkdir "build/emlreader"
	mkdir "build/search"
	$(CC) $(CC_FLAGS) $(INC) -o $@ $<

# build/%.o: src/%.cpp
# 	mkdir -p $(dir $@)
# 	$(CC) $(CC_FLAGS) $(INC) -c -o $@ $<

# define cc-command
# $(CC) $(INC) $< -o $@
# endef

# all: FileManager

# %.o: %.cpp
# 	$(cc-command)

# FileManager: $(OBJECTS)
# 	$(CC) $(CFLAGS) $? -o $@

# clean:
# 	$(RM) $(TARGET) *.o *~