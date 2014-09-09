.SUFFIXES:
	%:: SCCS/s.%
	%:: RCS/%
	%:: RCS/%,v
	%:: %,v
	%:: s.%

CFG					?= default

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
	$(Q)$(CXX) $(CXXFLAGS) -emit-llvm -S -o $@.ll $<
	$(Q)$(CXX) $(CXXFLAGS) -o $@ $@.ll

check: all
	@./tests.sh $(TARGET)

clean:
	@for FILE in $(TARGET); do rm -f $${FILE}; done

clean-all:
	@for FILE in $(TARGET); do rm -f $${FILE} $${FILE}.ll; done
