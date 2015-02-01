.SUFFIXES:
	%:: SCCS/s.%
	%:: RCS/%
	%:: RCS/%,v
	%:: %,v
	%:: s.%

Q		?= @
CFG	?= ../../default

TARGET	:= volume
SOURCE	:= $(TARGET).cpp


.PHONY: all check clean cleanall

all: $(TARGET).sse-scalar $(TARGET).sse-4x $(TARGET).sse-8x $(TARGET).avx-scalar $(TARGET).avx-8x $(TARGET).avx-16x

-include $(CFG).cfg

ifeq ($(VERBOSE), 1)
	CFLAGS		+= -v
endif

CFLAGS			+= -O2 $(INCLUDES)
CXXFLAGS		+= $(CFLAGS) -std=c++11

$(TARGET).sse-scalar:	$(SOURCE)
	@echo "$(CXX) $<    ====>    $@"
	$(Q)$(CXX) $(CXXFLAGS) -o $@ $< $(SSE) -DLENGTH=1

$(TARGET).sse-4x:	$(SOURCE)
	@echo "$(CXX) $<    ====>    $@"
	$(Q)$(CXX) $(CXXFLAGS) -o $@ $< $(SSE) -DLENGTH=4

$(TARGET).sse-8x:	$(SOURCE)
	@echo "$(CXX) $<    ====>    $@"
	$(Q)$(CXX) $(CXXFLAGS) -o $@ $< $(SSE) -DLENGTH=8

$(TARGET).avx-scalar:	$(SOURCE)
	@echo "$(CXX) $<    ====>    $@"
	$(Q)$(CXX) $(CXXFLAGS) -o $@ $< $(AVX) -DLENGTH=1

$(TARGET).avx-8x:	$(SOURCE)
	@echo "$(CXX) $<    ====>    $@"
	$(Q)$(CXX) $(CXXFLAGS) -o $@ $< $(AVX) -DLENGTH=8

$(TARGET).avx-16x:	$(SOURCE)
	@echo "$(CXX) $<    ====>    $@"
	$(Q)$(CXX) $(CXXFLAGS) -o $@ $< $(AVX) -DLENGTH=16

check: all
	@-./test.sh

clean:
	@rm -f *.ppm

cleanall: clean
	@rm -f $(TARGET).sse* $(TARGET).avx*
