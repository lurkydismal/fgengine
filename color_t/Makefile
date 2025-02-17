SRCDIR                = .
SUBDIRS               =
DLLS                  =
LIBS                  = libcolor_t.a
EXES                  =



### Common settings

CEXTRA                =
CXXEXTRA              =
RCEXTRA               =
DEFINES               =
INCLUDE_PATH          = -I include \
			-I ../stdfunc/include
DLL_PATH              =
DLL_IMPORTS           =
LIBRARY_PATH          =
LIBRARIES             = -lSDL3


### libcolor_t.a sources and settings

libcolor_t_a_MODULE       = libcolor_t.a
libcolor_t_a_C_SRCS       = src/color_t.c
libcolor_t_a_CXX_SRCS     =
libcolor_t_a_RC_SRCS      =
libcolor_t_a_LDFLAGS      =
libcolor_t_a_ARFLAGS      = rc
libcolor_t_a_DLL_PATH     =
libcolor_t_a_DLLS         =
libcolor_t_a_LIBRARY_PATH =
libcolor_t_a_LIBRARIES    =

libcolor_t_a_OBJS         = $(libcolor_t_a_C_SRCS:.c=.o) \
			$(libcolor_t_a_CXX_SRCS:.cpp=.o) \
			$(libcolor_t_a_RC_SRCS:.rc=.res)



### Global source lists

C_SRCS                = $(libcolor_t_a_C_SRCS)
CXX_SRCS              = $(libcolor_t_a_CXX_SRCS)
RC_SRCS               = $(libcolor_t_a_RC_SRCS)


### Tools

CC = ccache gcc
CXX = ccache g++
RC = rcc
AR = ar


### Generic targets

all: $(SUBDIRS) $(DLLS:%=%.so) $(LIBS) $(EXES)

### Build rules

.PHONY: all clean dummy

$(SUBDIRS): dummy
	@cd $@ && $(MAKE)

# Implicit rules

.SUFFIXES: .cpp .cxx .rc .res
DEFINCL = $(INCLUDE_PATH) $(DEFINES) $(OPTIONS)

.c.o:
	$(CC) -c $(CFLAGS) $(CEXTRA) $(DEFINCL) -o $@ $<

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(CXXEXTRA) $(DEFINCL) -o $@ $<

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(CXXEXTRA) $(DEFINCL) -o $@ $<

.rc.res:
	$(RC) $(RCFLAGS) $(RCEXTRA) $(DEFINCL) -fo$@ $<

# Rules for cleaning

CLEAN_FILES     = y.tab.c y.tab.h lex.yy.c core *.orig *.rej \
                  \\\#*\\\# *~ *% .\\\#*

clean:: $(SUBDIRS:%=%/__clean__) $(EXTRASUBDIRS:%=%/__clean__)
	$(RM) $(CLEAN_FILES) $(RC_SRCS:.rc=.res) $(C_SRCS:.c=.o) $(CXX_SRCS:.cpp=.o)
	$(RM) $(DLLS:%=%.so) $(LIBS) $(EXES) $(EXES:%=%.so)

$(SUBDIRS:%=%/__clean__): dummy
	cd `dirname $@` && $(MAKE) clean

$(EXTRASUBDIRS:%=%/__clean__): dummy
	-cd `dirname $@` && $(RM) $(CLEAN_FILES)

### Target specific build rules
DEFLIB = $(LIBRARY_PATH) $(LIBRARIES) $(DLL_PATH) $(DLL_IMPORTS:%=-l%)

$(libcolor_t_a_MODULE): $(libcolor_t_a_OBJS)
	$(AR) $(libcolor_t_a_ARFLAGS) $@ $(libcolor_t_a_OBJS)


