#OSDI LAB 3 

CC = aarch64-linux-gnu
CFLAGS = -ggdb -fPIC -Wall -nostdlib -nostartfiles -ffreestanding -Iinclude  
OLD = -ggdb -fPIC -Iinclude -Wall -ffreestanding -nostdinc -nostdlib -nostartfiles -mgeneral-regs-only
ASMOPS = -ggdb -fPIC -Iinclude
all: kernel8.img


SRC_DIR = src
BUILD_DIR = obj
SSRC_DIR = SRC

${BUILD_DIR}/%_S.o: ${SRC_DIR}/%.S
	${CC}-gcc ${ASMOPS} -c $< -o $@


${BUILD_DIR}/%.o: ${SRC_DIR}/%.c
	${CC}-gcc ${CFLAGS} -c $< -o $@

C_FILES = $(wildcard $(SRC_DIR)/*.c)
S_FILES = $(wildcard $(SRC_DIR)/*.S)
OBJ_FILES = $(C_FILES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
S_OBJ_FILES = $(S_FILES:$(SRC_DIR)/%.S=$(BUILD_DIR)/%_S.o)

kernel8.img: ${SRC_DIR}/link.ld ${OBJ_FILES} ${S_OBJ_FILES}
	${CC}-ld -Iinclude -T ${SRC_DIR}/link.ld -o ${BUILD_DIR}/kernel8.elf ${S_OBJ_FILES}  ${OBJ_FILES} -Map System.map
	${CC}-objcopy -O binary ${BUILD_DIR}/kernel8.elf kernel8.img

clean:
	rm -f kernel8.elf
	rm -f obj/*
debug:
	qemu-system-aarch64 -M raspi3 -kernel kernel8.img -serial pty -gdb tcp::8888 -S

run:
	qemu-system-aarch64 -M raspi3 -kernel kernel8.img -serial stdio 
