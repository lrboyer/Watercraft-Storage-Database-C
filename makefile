CC=gcc
CFLAGS=-Wall -g
LFLAGS=-lm
TARGET=sll


#sets C_SRCS equal to any c files found in the folder/folders automatically 
C_SRCS := \
	$(wildcard *.c) \
	$(wildcard src/*.c) \
	$(wildcard src/**/*.c)
#sets HDRS equal to any header files found in the folder/folders automatically 
HDRS := \
	$(wildcard *.h) \
	$(wildcard src/*.h) \
	$(wildcard src/**/*.h)

# Generate sources (puts everything together into a .o file)
OBJS := $(patsubst %.c, bin/%.o, $(wildcard *.c))
OBJS += $(filter %.o, $(patsubst src/%.c, bin/%.o, $(C_SRCS)))

# default target and when done prints it out
all: build
				@echo "All Done!"

#Link all built objects this compiles our code
build: $(OBJS)
				$(CC) $(OBJS) -o $(TARGET) $(LFLAGS)

#This makes a bin folder and neccessary subfolders and puts the .o file in it and compiles
bin/%.o: %.c $(HDRS)
					@mkdir -p $(dir $@)
					$(CC) $(CFLAGS) -c $< -o $@

#makes a src folder and puts the .o files in it and compiles
bin/%.o: src/%.c $(HDRS)
					@mkdir -p $(dir $@)
					$(CC) $(CFLAGS) -c $< -o $@

#this removes the lab4 executable and bin folder
clean:
				rm -f $(TARGET)
				rm -rf bin

#this runs the executable lab4 aka ./lab4
run: build

				./$(TARGET) watercraft.txt

# this prints out to the terminal the sources, headers, and 
#objs that the makefile has found in the folders
which:
				@echo "FOUND SOURCES: ${C_SRCS}"
				@echo "FOUND HEADERS: ${HDRS}"
				@echo "TARGET OBJS: ${OBJS}"