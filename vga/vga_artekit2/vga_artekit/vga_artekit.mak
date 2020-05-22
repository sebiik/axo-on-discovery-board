#  Project Name
PROJECT=vga_artekit

#  Type of CPU/MCU in target hardware
CPU = cortex-m4

#  Define the external crystal (HSE) frequency used as the PLL clock, in Hz
HSE_VALUE = 8000000

#  Build the list of object files needed.  All object files will be built in
#  the working directory, not the source directories.
#
#  You will need as a minimum your $(PROJECT).o file and the startup_stm32f4xx.o
#  object file.  Depending on where your code sets up the MCU's clocks and
#  PLL, you may also need some kind of initialization file, typically
#  system_stm32f4xx.o.  Finally, you will need whatever STMicros' standard
#  peripherals objects you use, such as stm32f4xx_gpio.o.
OBJECTS	= main.o \
		  demo.o \
		  font5x7.o \
		  gdi.o \
		  mth.o \
		  sys.o \
		  video.o \
	      misc.o \
	      stm32f4xx_gpio.o \
	      stm32f4xx_dma.o \
	      stm32f4xx_rcc.o  \
	      stm32f4xx_spi.o  \
	      stm32f4xx_tim.o  \
	      startup_stm32f4xx.o \
	      system_stm32f4xx.o
	      
#  Select the toolchain by providing a path to the top level
#  directory; this will be the folder that holds the
#  arm-none-eabi subfolders.
TOOLPATH = C:/CodeSourcery/SourceryG++Lite

#  Provide a base path to the STM32F4 firmware release folder.
#  This is the folder containing all of the original STMicros
#  examples, libraries, and includes for the STM32F4 Discovery
#  board.
STM32F4_BASEPATH = C:/projects/STM32F4-Discovery_FW_V1.1.0

#
#  Select the target type.  This is typically arm-none-eabi.
#  If your toolchain supports other targets, those target
#  folders should be at the same level in the toolchain as
#  the arm-none-eabi folders.
TARGETTYPE = arm-none-eabi

#  Describe the various include and source directories needed.
#  These usually point to files from whatever distribution
#  you are using (such as STM32F4 Discovery).  This can also
#  include paths to any needed GCC includes or libraries.
STM32F4_INC      = $(STM32F4_BASEPATH)/Libraries/CMSIS/ST/STM32F4xx/Include
STM32F4DISC_INC  = $(STM32F4_BASEPATH)/Utilities/STM32F4-Discovery
STDPERIPH_INC    = $(STM32F4_BASEPATH)/Libraries/STM32F4xx_StdPeriph_Driver/inc
CMSIS_INC        = $(STM32F4_BASEPATH)/Libraries/CMSIS/Include
GCC_INC          = $(TOOLPATH)/$(TARGETTYPE)/include


#  All possible source directories other than '.' must be defined in
#  the VPATH variable.  This lets make tell the compiler where to find
#  source files outside of the working directory.  If you need more
#  than one directory, separate them with ':'.
VPATH = $(STM32F4_BASEPATH)/Libraries/STM32F4xx_StdPeriph_Driver/src

				
#  List of directories to be searched for include files during compilation
INCDIRS  = -I$(GCC_INC)
INCDIRS += -I$(CMSIS_INC)
INCDIRS += -I$(STDPERIPH_INC)
INCDIRS += -I$(STM32F4DISC_INC)
INCDIRS += -I$(STM32F4_INC)
INCDIRS += -I.


# Name and path to the linker script
LSCRIPT = $(PROJECT).ld


OPTIMIZATION = 0
DEBUG = -g

#  List the directories to be searched for libraries during linking.
#  Optionally, list archives (libxxx.a) to be included during linking. 
LIBDIRS  = -L"$(TOOLPATH)/$(TARGETTYPE)/lib"
LIBS = -lc

#  Compiler options
GCFLAGS = -Wall -fno-common -mcpu=$(CPU) -mthumb -O$(OPTIMIZATION) $(DEBUG)
GCFLAGS += $(INCDIRS)
GCFLAGS += -D__STARTUP_CLEAR_BSS
GCFLAGS += -DHSE_VALUE=$(HSE_VALUE)
#GCFLAGS += -DSTM32F30X


#  Linker options
LDFLAGS  = -nostdlib -nostartfiles -Map=$(PROJECT).map -T$(LSCRIPT)
LDFLAGS += --cref
LDFLAGS += $(LIBDIRS)
LDFLAGS += $(LIBS)


#  Assembler options
ASLISTING = -alhs
ASFLAGS = $(ASLISTING) -mcpu=$(CPU)


#  Tools paths
#
#  Define an explicit path to the GNU tools used by make.
#  If you are ABSOLUTELY sure that your PATH variable is
#  set properly, you can remove the BINDIR variable.
#
BINDIR = $(TOOLPATH)/bin

CC = $(BINDIR)/arm-none-eabi-gcc
AS = $(BINDIR)/arm-none-eabi-as
AR = $(BINDIR)/arm-none-eabi-ar
LD = $(BINDIR)/arm-none-eabi-ld
OBJCOPY = $(BINDIR)/arm-none-eabi-objcopy
SIZE = $(BINDIR)/arm-none-eabi-size
OBJDUMP = $(BINDIR)/arm-none-eabi-objdump

#  Define a command for removing folders and files during clean.  The
#  simplest such command is Linux' rm with the -f option.  You can find
#  suitable versions of rm on the web.
REMOVE = rm -f

#########################################################################

all:: $(PROJECT).hex $(PROJECT).bin stats dump

$(PROJECT).bin: $(PROJECT).elf
	$(OBJCOPY) -O binary -j .text -j .data $(PROJECT).elf $(PROJECT).bin

$(PROJECT).hex: $(PROJECT).elf
	$(OBJCOPY) -R .stack -O ihex $(PROJECT).elf $(PROJECT).hex

#  Linker invocation
#  Uncomment one of the two lines that begin $(LD).
#  If you use the longer line, any errors will be reformatted for use by the Visual Studio
#  Intellisense application, so you can double-click on the error and go directly to the source
#  line.  If you use the shorter line, you get the regular GCC error format.
$(PROJECT).elf: $(OBJECTS)
#	$(LD) $(OBJECTS) $(LDFLAGS) -o $(PROJECT).elf 2>&1 | sed -e "s/\(\w\+\):\([ 0-9]\+\):/\1(\2):/"
	$(LD) $(OBJECTS) $(LDFLAGS) -o $(PROJECT).elf

stats: $(PROJECT).elf
	$(SIZE) $(PROJECT).elf
	
dump: $(PROJECT).elf
	$(OBJDUMP) -h $(PROJECT).elf	

clean:
	$(REMOVE) *.o
	$(REMOVE) $(PROJECT).hex
	$(REMOVE) $(PROJECT).elf
	$(REMOVE) $(PROJECT).map
	$(REMOVE) $(PROJECT).bin
	$(REMOVE) *.lst

#  The toolvers target provides a sanity check, so you can determine
#  exactly which version of each tool will be used when you build.
#  If you use this target, make will display the first line of each
#  tool invocation.
#  To use this feature, enter from the command-line:
#    make -f $(PROJECT).mak toolvers
toolvers:
	$(CC) --version | sed q
	$(AS) --version | sed q
	$(LD) --version | sed q
	$(AR) --version | sed q
	$(OBJCOPY) --version | sed q
	$(SIZE) --version | sed q
	$(OBJDUMP) --version | sed q
	
#########################################################################
#  Default rules to compile .c and .cpp file to .o
#  and assemble .s files to .o

#  There are two options for compiling .c files to .o; uncomment only one.
#  The shorter option is suitable for making from the command-line.
#  The option with the sed script on the end is used if you want to
#  compile from Visual Studio; the sed script reformats error messages
#  so Visual Studio's IntelliSense feature can track back to the source
#  file with the error.
.c.o :
	@echo Compiling $<, writing to $@...
#	$(CC) $(GCFLAGS) -c $< -o $@
	$(CC) $(GCFLAGS) -c $< 2>&1 | sed -e 's/\(\w\+\):\([ 0-9]\+\):/\1(\2):/'

.cpp.o :
	@echo Compiling $<, writing to $@...
	$(CC) $(GCFLAGS) -c $<

.s.o :
	@echo Assembling $<, writing to $@...
	$(AS) $(ASFLAGS) -o $@ $<  > $(basename $@).lst

#########################################################################
