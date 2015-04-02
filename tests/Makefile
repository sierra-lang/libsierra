.SUFFIXES:
	%:: SCCS/s.%
	%:: RCS/%
	%:: RCS/%,v
	%:: %,v
	%:: s.%

Q						?= @

LLDIR				:= llvm/
BINDIR			:= bin/

CFG					?= ../default

DUMMY				:= $(shell mkdir -p $(BINDIR))
DUMMY				:= $(shell mkdir -p $(LLDIR))

PWD					:= $(shell pwd)
SRC					:= $(sort $(subst $(PWD), ".", $(shell find . -name '*.cpp')))
TARGET			:= $(SRC:%.cpp=%)
TARGET2			:= $(SRC:%.cpp=$(BINDIR)/%)


.PHONY: all check clean cleanall

all: $(TARGET2)

-include $(CFG).cfg

ifeq ($(VERBOSE), 1)
	CFLAGS		+= -v
endif

CFLAGS			+= -Wall -W -pedantic -O2
CXXFLAGS		+= $(CFLAGS) -std=c++11

$(BINDIR)/% : %.cpp
	@echo "===> $(CXX) $<   ->   $*"
	-$(Q)$(CXX) $(CXXFLAGS) $(INCLUDES) -emit-llvm -S -o $(LLDIR)/$*.ll $<
	-$(Q)$(CXX) $(CXXFLAGS) -o $(BINDIR)/$* $(LLDIR)/$*.ll

check: all
	@./tests.sh $(TARGET)

cleanall: clean

clean:
	@rm -fr $(BINDIR) $(LLDIR)
