.PHONY: all check clean clean-all

CFG ?= default

TARGET=options
SOURCE=$(TARGET).cpp

all: $(TARGET).sse-scalar $(TARGET).sse-4x $(TARGET).sse-8x $(TARGET).avx-scalar $(TARGET).avx-8x $(TARGET).avx-16x

-include ../../$(CFG).cfg

CFLAGS+=$(INCLUDES)
CXXFLAGS+=$(CFLAGS) -std=c++11

$(TARGET).sse-scalar:	$(SOURCE)
	@echo "$(CXX) $<    ====>    $@"
	@$(CXX) $(CXXFLAGS) -o $@ $< -msse4.2 -DLENGTH=1

$(TARGET).sse-4x:	$(SOURCE)
	@echo "$(CXX) $<    ====>    $@"
	@$(CXX) $(CXXFLAGS) -o $@ $< -msse4.2 -DLENGTH=4

$(TARGET).sse-8x:	$(SOURCE)
	@echo "$(CXX) $<    ====>    $@"
	@$(CXX) $(CXXFLAGS) -o $@ $< -msse4.2 -DLENGTH=8

$(TARGET).avx-scalar:	$(SOURCE)
	@echo "$(CXX) $<    ====>    $@"
	@$(CXX) $(CXXFLAGS) -o $@ $< -mavx -DLENGTH=1

$(TARGET).avx-8x:	$(SOURCE)
	@echo "$(CXX) $<    ====>    $@"
	@$(CXX) $(CXXFLAGS) -o $@ $< -mavx -DLENGTH=8

$(TARGET).avx-16x:	$(SOURCE)
	@echo "$(CXX) $<    ====>    $@"
	@$(CXX) $(CXXFLAGS) -o $@ $< -mavx -DLENGTH=16

check: all
	@-./test.sh

clean:
	@rm -f *.ppm

clean-all: clean
	@rm -f $(TARGET).sse* $(TARGET).avx*
