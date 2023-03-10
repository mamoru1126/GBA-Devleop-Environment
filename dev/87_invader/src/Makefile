SHELL		:= sh
NAME		:= Test
GAMECODE	:= Test

MAPFILE		:=	$(NAME).map
TARGET_ELF	:=	$(NAME).elf
TARGET_BIN	:=	$(NAME).gba

PREFIX		:= arm-eabi-
AS			:= $(PREFIX)as
CC 			:= $(PREFIX)gcc
LD 			:= $(PREFIX)gcc
AR 			:= $(PREFIX)ar
OBJCOPY		:= $(PREFIX)objcopy

#=============================================================================
OBJDIR	:= obj
RESDIR	:= res
INCDIR	:= 

AFILES	:= 
CFILES	:= irq_arm.c ad_arm.c lib.c rand.c minix.c gbfs.c main.c screen.c invader.c haribote.c
SFILES	:= gba_crt0.s bios_arm.s div_arm.s \
	$(RESDIR)/mplus_s10r.s \
	$(RESDIR)/mplus_sfnt.s \
	$(RESDIR)/spr.s \

OFILES	:= $(addprefix $(OBJDIR)/,$(SFILES:.s=.o) $(CFILES:.c=.o))
DFILES	:= $(addprefix $(OBJDIR)/,$(CFILES:.c=.d))

ASFLAGS	:= -mthumb-interwork
CFLAGS	:= -mthumb-interwork -nostdlib -mcpu=arm7tdmi -Wall -W -Wshadow -Wno-unused-parameter $(foreach incdir,$(INCDIR),-I$(incdir) )
LDFLAGS	:= -Map $(MAPFILE) -Wall -mthumb-interwork -specs=gba.specs -nostartfiles

#=============================================================================

#DEBUG := 1
#PROFILE := 0

ifndef DEBUG
	CFLAGS	+= -O3
else
    ASFLAGS	+= -g
    CFLAGS	+= -g -O0 -DDEBUG
ifdef PROFILE
    ASFLAGS	+= -pg
    CFLAGS	+= -pg
    AFILES	+= prof/libpgba.a
endif
endif

CFLAGS_THUMB:= $(CFLAGS) -mthumb
CFLAGS_ARM	:= $(CFLAGS) -marm

#=============================================================================

$(TARGET_BIN): $(TARGET_ELF)
	@$(PREFIX)objcopy -v -O binary $< $@
	@gbafix $@ -t$(NAME) -c$(GAMECODE) -m00 -r01

$(TARGET_ELF): $(OFILES) $(AFILES) makefile.txt
	@echo Linking $@
	@echo > $(MAPFILE)
	@$(LD) -o $@ $(OFILES) $(AFILES) -Wl,$(LDFLAGS)

#=============================================================================

.PHONY: all clean data
all: clean data $(TARGET_BIN) ;

clean:
	rm -f $(OFILES) $(DFILES) $(MAPFILE) $(TARGET_ELF) $(TARGET_BIN)

.SUFFIXES: .s .c .o .a .d

$(OBJDIR)/%_arm.o: %_arm.c
	@echo compiling $<
	@$(CC) -MMD $(CFLAGS_ARM) -c $< -o $@

$(OBJDIR)/%.o: %.c
	@echo compiling $<
	@$(CC) -MMD $(CFLAGS_THUMB) -c $< -o $@

$(OBJDIR)/%.o: %.s
	@echo assembling $<
	@$(AS) $(ASFLAGS) $< -o $@

-include $(DFILES)
