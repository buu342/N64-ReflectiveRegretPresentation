################################################################
#                    Code files and ROM name                   #
################################################################

CODECFILES  = main.c graphic.c helper.c slide_common.c sausage64.c text.c datastructs.c
CODEHFILES  =
OBJECTINC   = slides/slidesobj.o

DEBUGFILES = debug.c usb.c

TARGETS = presentation.n64

REGISTRATION = "REGRET" B RR I

PADDING = 32


################################################################
#                         NuSys Config                         #
################################################################

# NuSys
N64KITDIR	= c:/nintendo/n64kit
NUSYSDIR	= $(N64KITDIR)/nusys
NUSYSINC	= $(NUSYSDIR)/include
NUSYSLIB	= $(NUSYSDIR)/lib
NUOBJ		= $(NUSYSLIB)/nusys.o

# NuSys STD lib
NUSYSSYDDIR = $(N64KITDIR)/nustd
NUSYSSTDINC = $(NUSYSSYDDIR)/include
NUSYSSTDLIB = $(NUSYSSYDDIR)/lib


################################################################
#                       Compiler Settings                      #
################################################################

CC  = gcc
LD  = ld
MAKEROM = mild


################################################################
#                         Make Commands                        #
################################################################

default: $(TARGETS)


################################################################
#     Don't touch below unless you know what you're doing!     #
################################################################

include $(ROOT)/usr/include/make/PRdefs

CODESEGMENT = codesegment.o
OBJECTS		= $(CODESEGMENT)
APP         = $(TARGETS:.n64=.out)


################################################################
#                     ROM debug mode check                     #
################################################################

ifeq ($(DEBUG_MODE), 0)
    CODEOBJECTS     = $(CODECFILES:.c=.o) $(OBJECTINC) $(NUOBJ)
    OPTIMIZER       = -O2
    LCDEFS          = -D_FINALROM -DNDEBUG -DF3DEX_GBI_2 -DNOT_SPEC
    N64LIB          = -lnusys_d -lnustd -lgultra_rom
    MAKEROMFLAGS    = 
else
    CODEOBJECTS     = $(CODECFILES:.c=.o) $(OBJECTINC) $(NUOBJ) $(DEBUGFILES:.c=.o)
    OPTIMIZER       = -g
    LCDEFS          = -DDEBUG  -DF3DEX_GBI_2 -DNOT_SPEC
    N64LIB          = -lnusys_d -lnustd_d -lgultra_d 
    MAKEROMFLAGS    = -d
endif


################################################################
#                        Linker Settings                       #
################################################################

LCINCS =	-I. -I$(ROOT)/usr/include/PR -I $(ROOT)/usr/include -I$(NUSYSINC) -I$(NUSYSSTDINC)
LCOPTS =	-G 0
LDIRT  =	$(APP)
LDFLAGS=	$(MKDEPOPT) -L$(ROOT)/usr/lib -L$(ROOT)/usr/lib/PR -L$(NUSYSLIB) -L$(NUSYSSTDLIB) $(N64LIB) -L$(GCCDIR)/mipse/lib -lkmc


################################################################
#                          Compilation                         #
################################################################

include $(COMMONRULES)

$(CODESEGMENT): $(CODEOBJECTS)
    $(LD) -o $(CODESEGMENT) -r $(CODEOBJECTS) $(LDFLAGS)

$(TARGETS): $(OBJECTS)
    $(MAKEROM) spec $(MAKEROMFLAGS) -I$(NUSYSINC) -r $(TARGETS) -e $(APP) -s $(PADDING)
    @makemask $(TARGETS)
ifeq ($(ALLOWREGISTER), 1)
    @nrdc $(TARGETS) $(REGISTRATION)
endif
