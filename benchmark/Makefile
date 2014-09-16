.PHONY: all check clean clean-all

TARGETS=aobench/ mandelbrot/ options/ rgb2gray/ volume/

all:
	@for TARGET in $(TARGETS); do $(MAKE) $(MFLAGS) -C $${TARGET}; done

check:
	@for TARGET in $(TARGETS); do $(MAKE) $(MFLAGS) -C $${TARGET} check; done

clean:
	@for TARGET in $(TARGETS); do $(MAKE) $(MFLAGS) -C $${TARGET} clean; done

clean-all:
	@for TARGET in $(TARGETS); do $(MAKE) $(MFLAGS) -C $${TARGET} clean-all; done
