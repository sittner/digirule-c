DEVICE = 18f43k20
TARGET = digirule
CPUFRQ = 8000000

OBJS = \
  main.p1 \
  randgen2.p1 \
  leds.p1 \
  buttons.p1 \
  logic.p1 \
  flipflop.p1 \
  counter.p1 \
  shiftreg.p1 \
  povmsg.p1 \
  dice.p1 \
  game.p1 \

AFLAGS = -Q --chip=$(DEVICE)
CFLAGS = -D_XTAL_FREQ=$(CPUFRQ) -P --asmlist
LFLAGS = 

.PHONY: clean program

$(TARGET).hex: $(OBJS)
	picc18 $(AFLAGS) $(LFLAGS) -O$(TARGET).cof -M$(TARGET).map $(OBJS)

%.p1: %.c
	picc18 $(AFLAGS) $(CFLAGS) --pass1 $<

program: $(TARGET).hex
	pk2cmd -M -PPIC$(DEVICE) -F$(TARGET).hex

clean:
	rm -f *.d *.p1 *.pre
	rm -f *.as *.cmf *.cof *.hex *.hxl *.lst *.map *.obj *.rlf *.sdb *.sym

