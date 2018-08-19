.SUFFIXES:
	%:: SCCS/s.%
	%:: RCS/%
	%:: RCS/%,v
	%:: %,v
	%:: s.%

Q		?= @
include ../../../config.mk


TARGET	:= 2mm
SOURCE	:= $(TARGET).cpp

.PHONY: all check clean cleanall

all: $(TARGET).sse-scalar $(TARGET).sse-4x $(TARGET).sse-8x $(TARGET).sse-16x $(TARGET).avx-scalar $(TARGET).avx-4x $(TARGET).avx-8x $(TARGET).avx-16x

ifeq ($(VERBOSE), 1)
	CFLAGS		+= -v
endif


#DATASETSIZE='-DEXTRALARGE_DATASET'
#DATASETSIZE='-DLARGE_DATASET'
DATASETSIZE='-DSTANDARD_DATASET'
#DATASETSIZE='-DSMALL_DATASET'
#DATASETSIZE='-DMINI_DATASET'


OWNFLAGS        += -fsierra -Xclang -load -Xclang ${INSTALL_DIR}/lib/libRVCodeGen.so #-mllvm -debug-only=rvcodegen
OWNFLAGS	+= -fno-vectorize -fno-slp-vectorize -fno-slp-vectorize-aggressive
OWNFLAGS += -DPOLYBENCH_TIME $(DATASETSIZE)

EXTRA_FLAGS=-I. -I../../../utilities ../../../utilities/polybench.c

CFLAGS                  += -O3 $(INCLUDES)
#CXXFLAGS                += -S $(CFLAGS) -std=c++11 $(OWNFLAGS)
CXXFLAGS                += $(CFLAGS) -std=c++11 $(OWNFLAGS) $(EXTRA_FLAGS)





$(TARGET).sse-scalar:	$(SOURCE)
	@echo "$(CXX) $<    ====>    $@"
	$(Q)$(CXX) $(CXXFLAGS) -o $@ $< $(SSE) -DLENGTH=1

$(TARGET).sse-4x:	$(SOURCE)
	@echo "$(CXX) $<    ====>    $@"
	$(Q)$(CXX) $(CXXFLAGS) -o $@ $< $(SSE) -DLENGTH=4

$(TARGET).sse-8x:	$(SOURCE)
	@echo "$(CXX) $<    ====>    $@"
	$(Q)$(CXX) $(CXXFLAGS) -o $@ $< $(SSE) -DLENGTH=8

$(TARGET).sse-16x:	$(SOURCE)
	@echo "$(CXX) $<    ====>    $@"
	$(Q)$(CXX) $(CXXFLAGS) -o $@ $< $(SSE) -DLENGTH=16

$(TARGET).avx-scalar:	$(SOURCE)
	@echo "$(CXX) $<    ====>    $@"
	$(Q)$(CXX) $(CXXFLAGS) -o $@ $< $(AVX) -DLENGTH=1

$(TARGET).avx-4x:	$(SOURCE)
	@echo "$(CXX) $<    ====>    $@"
	$(Q)$(CXX) $(CXXFLAGS) -o $@ $< $(AVX) -DLENGTH=4

$(TARGET).avx-8x:	$(SOURCE)
	@echo "$(CXX) $<    ====>    $@"
	$(Q)$(CXX) $(CXXFLAGS) -o $@ $< $(AVX) -DLENGTH=8

$(TARGET).avx-16x:	$(SOURCE)
	@echo "$(CXX) $<    ====>    $@"
	$(Q)$(CXX) $(CXXFLAGS) -o $@ $< $(AVX) -DLENGTH=16


clean:
	@rm -f $(TARGET).sse* $(TARGET).avx*

