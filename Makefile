#OSDI LAB 2 

CC = aarch64-linux-gnu
CFLAGS = -ggdb -fPIC -Include -Wall -ffreestanding -nostdinc -nostdlib -nostartfiles -mgeneral-regs-only
ASMOPS = -ggdb -fPIC -Iinclude
all: kernel8.img



SRC_DIR = src
BUILD_DIR = obj

obj/start.o: src/start.S src/IRQ.S src/entry.S src/SYS.S
	${CC}-gcc ${CFLAGS} -c src/start.S -o obj/start.o
	${CC}-gcc ${CFLAGS} -c src/IRQ.S -o obj/IRQ.o
	${CC}-gcc ${CFLAGS} -c src/entry.S -o obj/entry.o
	${CC}-gcc ${CFLAGS} -c src/SYS.S -o obj/SYS.o



${BUILD_DIR}/%.o: ${SRC_DIR}/%.c
	${CC}-gcc ${CFLAGS} -c $< -o $@

C_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(C_FILES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)


kernel8.img: ${SRC_DIR}/link.ld ${OBJ_FILES} obj/start.o 
	${CC}-ld -Iinclude -T ${SRC_DIR}/link.ld -o ${BUILD_DIR}/kernel8.elf obj/start.o obj/IRQ.o obj/entry.o obj/SYS.o  ${OBJ_FILES} -Map System.map
	${CC}-objcopy -O binary ${BUILD_DIR}/kernel8.elf kernel8.img

clean:
	rm -f kernel8.elf
	rm -f obj/*
debug:
	qemu-system-aarch64 -M raspi3 -kernel kernel8.img -display none -gdb tcp::8888 -S

run:
	qemu-system-aarch64 -M raspi3 -kernel kernel8.img -serial stdio 
