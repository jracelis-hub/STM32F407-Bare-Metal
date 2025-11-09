CC=arm-none-eabi-g++
VERSION=-std=gnu++17
CPU=-mcpu=cortex-m4
INCLUDE=-I../inc
WARNING=-Wall -Werror
FLAGS=$(INCLUDE) $(WARNING) $(VERSION) $(CPU)

SRC=sys_clock.cpp
OBJECT=sys_clock.o

.PHONE: all clean

all: $(OBJECT)

%.o:%.cpp
	$(CC) -c $< -o $@ $(FLAGS)

clean:
	@rm $(OBJECT) 
