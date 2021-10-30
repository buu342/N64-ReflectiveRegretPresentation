################################################################
#                  Code files and Object name                  #
################################################################

CODEFILES = slides.c \
            slide00.c \
            slide01.c \
            slide02.c \
            slide03.c \
            slide04.c \
            slide05.c \
            slide06.c \
            slide07.c \
            slide08.c \
            slide09.c \
            slide10.c \
            slide11.c \
            slide12.c \
            slide13.c \
            slide14.c \
            slide15.c \
            slide16.c \
            slide17.c \
            slide18.c \
            slide19.c \
            slide20.c 
            
OBJECTNAME = slidesobj.o


############################################################################
# DO NOT CHANGE ANYTHING BELOW THIS LINE UNLESS YOU KNOW WHAT YOU'RE DOING #
############################################################################

include $(ROOT)/usr/include/make/PRdefs

TARGETS = $(OBJECTNAME)
CODEOBJECTS = $(CODEFILES:.c=.o)


################################################################
#                         NuSys Config                         #
################################################################

N64KITDIR    = c:\nintendo\n64kit
NUSYSINCDIR  = $(N64KITDIR)\nusys\include
NUSYSLIBDIR  = $(N64KITDIR)\nusys\lib
NUSTDINC     = $(N64KITDIR)\nustd\include
NUSTDLIB     = $(N64KITDIR)\nustd\lib


################################################################
#                     ROM debug mode check                     #
################################################################

ifeq ($(DEBUG_MODE), 0)
    OPTIMIZER       = -O2
else
    OPTIMIZER       = -g
endif


################################################################
#                        Linker Settings                       #
################################################################

default: $(TARGETS)

N64GCC_PATH =	$(ROOT)\gcc\mipse
N64GCC_BIN =	$(N64GCC_PATH)\bin
N64GCC_INC =	$(ROOT)\usr\include

CC =		$(N64GCC_BIN)\gcc
AS =		$(N64GCC_BIN)\as
LD =		$(N64GCC_BIN)\ld
MAKEROM =	mild

AUDIO_CDEFS = -DNUALSTL -DN_AUDIO
NUAUDIOLIB = -lnualstl_n -ln_numus -ln_gaudio_sc
GBI = -DF3DEX_GBI_2

LCINCS =	-I. -I$(ROOT)/usr/include/PR -I $(ROOT)/usr/include -I$(NUSYSINCDIR) -I$(NUSTDINC)

################################################################
#                          Compilation                         #
################################################################

include $(COMMONRULES)

$(TARGETS): $(CODEOBJECTS)
    $(CC) -g -G 0 -c $(LCINCS) $(CC_DEF) $(CODEFILES)
    $(LD) -r $(CODEOBJECTS) -o $(OBJECTNAME)

