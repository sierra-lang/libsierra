.PHONY: all check clean cleanall

TARGETS=aobench/ mandelbrot/ options/ volume/

all:
	@for TARGET in $(TARGETS); do $(MAKE) $(MFLAGS) -C $${TARGET}; done

check:
	@for TARGET in $(TARGETS); do $(MAKE) $(MFLAGS) -C $${TARGET} check; done

clean:
	@for TARGET in $(TARGETS); do $(MAKE) $(MFLAGS) -C $${TARGET} clean; done

cleanall:
	@for TARGET in $(TARGETS); do $(MAKE) $(MFLAGS) -C $${TARGET} cleanall; done
