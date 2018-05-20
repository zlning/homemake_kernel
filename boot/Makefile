C_SRCS = $(wildcard *.c)
S_SRCS = $(wildcard *.s)
C_OBJS = $(patsubst %.c, %.o, $(C_SRCS))
S_OBJS += $(patsubst %.s, %.o, $(S_SRCS))
BOOTELF = bootelf
TARGET = testboot.bin
.PHONY: all clean
all : $(TARGET)
$(TARGET):$(C_OBJS) $(S_OBJS)
	arm-linux-ld -Tnand.lds -o $(BOOTELF) $^
	arm-linux-objcopy -O binary -S $(BOOTELF) $@
    
$(C_OBJS):$(C_SRCS)
	arm-linux-gcc -c $< -o $@
$(S_OBJS):$(S_SRCS)
	arm-linux-gcc -c $< -o $@

clean:
	rm *.o $(BOOTELF) $(TARGET)
#start.o:start.s
#	arm-linux-gcc -c $< -o $@
    
#main.o:main.c
#	arm-linux-gcc -c $< -o $@ 