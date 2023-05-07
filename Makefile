ARCH = x86_64

SRCDIR = src

CC = $(ARCH)-elf-gcc
CPP = $(ARCH)-elf-g++
LD = $(ARCH)-elf-ld
AR = $(ARCH)-elf-ar

CFLAGS = -ffreestanding \
	 -fvisibility=protected \
	 -fno-stack-protector \
	 -fno-omit-frame-pointer \
	 -fno-builtin-g       \
	 -fno-stack-check     \
	 -I $(SRCDIR)/include    \
	 -m64                 \
	 -mabi=sysv           \
	 -mno-80387           \
	 -mno-mmx             \
	 -mno-sse             \
	 -mno-sse2            \
	 -mno-red-zone        \
	 -fpermissive         \
	 -Wall                \
	 -Wno-write-strings   \
	 -Og                  \
	 -fno-rtti            \
	 -fno-exceptions      \
	 -fno-lto             \
	 -fno-pie             \
	 -fPIC \
	 -march=x86-64        \
	 -ggdb


ASMFLAGS = -f elf64

LDFLAGS = -shared \
	  -T $(SRCDIR)/mkmix64.ld \
	  -nostdlib               \
	  -m elf_$(ARCH)          \
	  -z max-page-size=0x1000

rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

CPPSRC = $(call rwildcard,$(SRCDIR),*.cpp)
OBJS = $(patsubst $(SRCDIR)/%.cpp, $(SRCDIR)/%.o, $(CPPSRC))

$(SRCDIR)/%.o: $(SRCDIR)/%.cpp
	@ mkdir -p $(@D)
	@ echo !==== COMPILING MKMI $^ && \
	$(CPP) $(CFLAGS) -c $^ -o $@

dynamic: $(OBJS)
	@ echo !==== LINKING
	$(LD) $(LDFLAGS) -o libmkmi.so $(OBJS)

static: $(OBJS)
	@ echo !==== ARCHIVING
	$(AR) rcs libmkmi.a $(OBJS)

clean:
	@rm $(OBJS)
