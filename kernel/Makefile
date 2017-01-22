# Nintendont kernel

#---------------------------------------------------------------------------------
# Clear the implicit built in rules
#---------------------------------------------------------------------------------

.SUFFIXES:
#---------------------------------------------------------------------------------
ifeq ($(strip $(DEVKITARM)),)
$(error "Please set DEVKITARM in your environment. export DEVKITARM=<path to>devkitARM")
endif

PREFIX	:= $(DEVKITARM)/bin/arm-none-eabi-
CC	:= $(PREFIX)gcc
CXX	:= $(PREFIX)g++
AS	:= $(PREFIX)as
LD	:= $(PREFIX)g++
STRIP	:= $(PREFIX)strip

ifeq ($(windows), 1)
	ZIP = zip/zip.exe
else
	ZIP = zip
endif

COMMONFLAGS := -mbig-endian -O3 -I. -Wall \
		-mcpu=arm926ej-s -msoft-float -mfloat-abi=soft \
		-fdata-sections -ffunction-sections -fno-builtin-toupper -fno-builtin-memcpy \
		-fno-builtin-memset -fno-builtin-memcmp -fno-builtin-malloc -fno-builtin-free \
		-fno-exceptions -DJSON_NOEXCEPTION=true
CFLAGS	 := -std=gnu89
CPPFLAGS := -I. -I../fatfs -I./PrimeMemoryDumping -I./PrimeMemoryDumping/common -I../codehandler
CXXFLAGS := -std=c++14 -Wno-unknown-pragmas -Wno-pragmas -Wno-missing-declarations -Wno-shadow \
		-Wno-unused-variable -Wno-strict-aliasing

ASFLAGS	:= -mbig-endian -mcpu=arm926ej-s
LDFLAGS	:= -static -nostartfiles -nodefaultlibs -mbig-endian -Wl,--gc-sections,-T,kernel.ld,-Map,kernel.map -n \
            -fno-exceptions

TARGET	:= kernel.elf
OBJECTS	:= start.o common.o alloc.o GCAM.o JVSIO.o JVSIOMessage.o FST.o DI.o RealDI.o \
	   Patch.o PatchTimers.o TRI.o PatchWidescreen.o ISO.o Stream.o adp.o \
	   EXI.o SRAM.o SI.o HID.o diskio.o Config.o utils_asm.o ES.o NAND.o \
	   main.o syscalls.o ReadSpeed.o vsprintf.o string.o prs.o \
	   SDI.o usb.o usbstorage.o PrimeMemoryDumping.o net.o new.o

LIBS	:= ../fatfs/libfatfs-arm.a be/libgcc.a be/libc.a be/libstdc++.a
ZIPFILE	:= ../loader/data/kernel.zip

# Bluetooth stack
OBJECTS	+= lwbt/bte.o lwbt/btmemb.o lwbt/btmemr.o lwbt/btpbuf.o lwbt/hci.o lwbt/l2cap.o lwbt/physbusif.o BT.o

.PHONY: FORCE

all: $(TARGET)

-include $(OBJECTS:.o=.d)

$(TARGET): kernel.ld $(OBJECTS)
	@echo  "LD	$@"
	$(LD) $(LDFLAGS) $(OBJECTS) $(LIBS) -o $@
	@$(STRIP) -s -g kernel.elf -o kernel.bin
	@echo  "ZIP	$(ZIPFILE)"
	@$(ZIP) -JXjq9 $(ZIPFILE) kernel.bin

%.o: %.s
	@echo  "AS	$@"
	@$(CC) $(COMMONFLAGS) $(CFLAGS) $(CPPFLAGS) -D_LANGUAGE_ASSEMBLY -c -MMD -MP -MF $(@:.o=.d) -x assembler-with-cpp -o $@ $<

%.o: %.S
	@echo  "AS	$@"
	@$(CC) $(COMMONFLAGS) $(CFLAGS) $(CPPFLAGS) -D_LANGUAGE_ASSEMBLY -c -MMD -MP -MF $(@:.o=.d) -x assembler-with-cpp -o $@ $<

%.o : %.c
	@echo  "CC	$@"
	@$(CC) $(COMMONFLAGS) $(CFLAGS) $(CPPFLAGS) -c -MMD -MP -MF $(@:.o=.d) -o $@ $<

%.o : %.cpp
	@echo  "CXX	$@"
	@$(CXX) $(COMMONFLAGS) $(CXXFLAGS) $(CPPFLAGS) -c -MMD -MP -MF $(@:.o=.d) -o $@ $<

clean:
	-$(RM) -f $(ZIPFILE) *.elf *.o *.bin *.d *.map lwbt/*.d lwbt/*.o option/*.d option/*.o PrimeMemoryDumping/prime1/*.o
