CC=arm-none-eabi-g++
INCLUDE=-I../inc
WARNING=-Wall -Werror
FLAGS=$(INCLUDE) $(WARNING)

SRC=sys_clock.cpp
OBJECT=sys_clock.o

.PHONE: all clean

all: $(OBJECT)

$(OBJECT):$(SRC)
	$(CC) -c $< -o $@ $(FLAGS)

clean:
	@rm $(OBJECT) 
