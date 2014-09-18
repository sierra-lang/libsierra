.SUFFIXES:
	%:: SCCS/s.%
	%:: RCS/%
	%:: RCS/%,v
	%:: %,v
	%:: s.%

LLDIR				:= llvm/
BINDIR			:= bin/

CFG					?= default

DUMMY				:= $(shell mkdir -p $(BINDIR))
DUMMY				:= $(shell mkdir -p $(LLDIR))

PWD					:= $(shell pwd)
SRC					:= $(sort $(subst $(PWD), ".", $(shell find . -name '*.cpp')))
TARGET			:= $(SRC:%.cpp=%)


.PHONY: all check clean

all: $(TARGET)

-include $(CFG).cfg


ifeq ($(VERBOSE), 1)
	CXXFLAGS	+= -v
endif

CFLAGS		+= -Wall -W -pedantic
CXXFLAGS	+= $(CFLAGS) -std=c++11

% : %.cpp
	@echo "===> $(CXX) $<   ->   $@"
	$(Q)$(CXX) $(CXXFLAGS) $(INCLUDES) -emit-llvm -S -o $(LLDIR)/$@.ll $<
	$(Q)$(CXX) $(CXXFLAGS) -o $(BINDIR)/$@ $(LLDIR)/$@.ll

check: all
	@./tests.sh $(TARGET)

clean:
	@rm -fr $(BINDIR) $(LLDIR)
