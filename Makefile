CC=arm-none-eabi-g++
INCLUDE=-I../
WARNING=-Wall -Werror
FLAGS=$(INCLUDE) $(WARNING)
# Directories

.PHONY: clean

%.c:%.o
	$(CC) -c $@ -o $^ $(FLAGS)

clean:
	@rm *.o
