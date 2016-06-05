VERSION = 2.0
ZLIBOBJ = zlib/adler32.o zlib/compress.o zlib/crc32.o zlib/deflate.o zlib/gzio.o zlib/infback.o zlib/inffast.o zlib/inflate.o zlib/inftrees.o zlib/trees.o zlib/uncompr.o zlib/zutil.o
ENETOBJ = enet/host.o enet/list.o enet/memory.o enet/packet.o enet/peer.o enet/protocol.o enet/unix.o enet/win32.o
IRRNETOBJ = CNetManager.o SPacket.o 
LINKOBJ := $(IRRNETOBJ) $(ENETOBJ) $(ZLIBOBJ)

###############
#Compiler flags
CXXINCS = -I../include -Izlib -Ienet/include
CPPFLAGS = $(CXXINCS)
CXXFLAGS = -Wall -fexpensive-optimizations -O3

ifdef PROFILE
CXXFLAGS += -pg
endif
CFLAGS := -fexpensive-optimizations -O3

#Linux specific options
STATIC_LIB = libirrnet.a
LIB_PATH = ../lib/$(STATIC_LIB)
INSTALL_DIR = /usr/local/lib
staticlib install: SYSTEM = Linux
staticlib: LDFLAGS = --no-export-all-symbols --add-stdcall-alias
####################
all linux: staticlib

$(STATIC_LIB): $(LINKOBJ)
	$(AR) rs $@ $^

# Copies static lib into /lib/Linux
staticlib: $(STATIC_LIB)
	cp $^ $(LIB_PATH)

# Create dependency files for automatic recompilation
%.d:%.cpp
	$(CXX) $(CPPFLAGS) -MM -MF $@ $<

-include $(LINKOBJ:.o=.d)

clean:
	$(RM) $(LINKOBJ) $(SHARED_LIB).$(VERSION) $(STATIC_LIB) $(LINKOBJ:.o=.d)

withirrlicht:
CXXINCS += -Iirrlicht/include -DCOMPILE_WITH_IRRLICHT
all staticlib clean
	
.PHONY: all staticlib clean

