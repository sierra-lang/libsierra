.PHONY: all check clean clean-all

Q						?= @
CFG					?= default

TARGET			:= aobench
SOURCE			:= $(TARGET).cpp

all: $(TARGET).sse-scalar $(TARGET).sse-4x $(TARGET).sse-8x $(TARGET).avx-scalar $(TARGET).avx-8x $(TARGET).avx-16x

-include ../../$(CFG).cfg

ifeq ($(VERBOSE), 1)
	CFLAGS		+= -v
endif

CFLAGS			+= -O2 $(INCLUDES)
CXXFLAGS		+= $(CFLAGS) -std=c++11

DUMMY				:= $(shell echo $(CXXFLAGS) > make.debug)

$(TARGET).sse-scalar:	$(SOURCE)
	@echo "$(CXX) $<    ====>    $@"
	$(Q)$(CXX) $(CXXFLAGS) -o $@ $< -msse4.2 -DLENGTH=1

$(TARGET).sse-4x:	$(SOURCE)
	@echo "$(CXX) $<    ====>    $@"
	$(Q)$(CXX) $(CXXFLAGS) -o $@ $< -msse4.2 -DLENGTH=4

$(TARGET).sse-8x:	$(SOURCE)
	@echo "$(CXX) $<    ====>    $@"
	$(Q)$(CXX) $(CXXFLAGS) -o $@ $< -msse4.2 -DLENGTH=8

$(TARGET).avx-scalar:	$(SOURCE)
	@echo "$(CXX) $<    ====>    $@"
	$(Q)$(CXX) $(CXXFLAGS) -o $@ $< -mavx -DLENGTH=1

$(TARGET).avx-8x:	$(SOURCE)
	@echo "$(CXX) $<    ====>    $@"
	$(Q)$(CXX) $(CXXFLAGS) -o $@ $< -mavx -DLENGTH=8

$(TARGET).avx-16x:	$(SOURCE)
	@echo "$(CXX) $<    ====>    $@"
	$(Q)$(CXX) $(CXXFLAGS) -o $@ $< -mavx -DLENGTH=16

check: all
	$(Q)-./test.sh

clean:
	$(Q)rm -f *.ppm

clean-all: clean
	$(Q)rm -f $(TARGET).sse* $(TARGET).avx*
