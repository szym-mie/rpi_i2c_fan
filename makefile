TARGET = main
TARGET_PREFIX = x_

LIB = main

SRCP = src/
OBJP = obj/
OUTP = out/

CSRCS = $(wildcard $(SRCP)*.c)
SSRCS = $(wildcard $(SRCP)*.s)
COBJS = $(patsubst $(SRCP)%.c,$(OBJP)%.o,$(filter-out $(SRCP)x_%.c,$(CSRCS)))
SOBJS = $(patsubst $(SRCP)%.s,$(OBJP)%.o,$(SSRCS))
LIBS = $(patsubst %,$(OUTP)%.a,$(LIB))
ETGTS = $(patsubst %,$(OUTP)%.elf,$(TARGET))
HTGTS = $(patsubst %,$(OUTP)%.hex,$(TARGET))

CC = avr-gcc
CCF += -Wall
CCF += -g
CCF += -std=c89

AS = avr-as
ASF += -g

DF += -mmcu=attiny84

AR = avr-ar
ARO = rcs

OC = avr-objcopy 

OD = avr-objdump
ODF += -S

AD = avrdude
ADF += -p t85

# sets XCCF, XASF, XADF, etc
-include makefile.in

.PHONY: all
all:
	@echo build:  \'make build\'
	@echo upload: \'make upload\'
	@echo inspect assembly: \'make see\'
	@echo clean:  \'make clean\'

.PHONY: build
build: $(HTGTS)

$(LIBS): $(OUTP)%.a: $(COBJS) $(SOBJS)
	$(AR) $(ARO) $@ $^

$(COBJS): $(OBJP)%.o: $(SRCP)%.c
	$(CC) $(CCF) $(XCCF) -c -o $@ $<

$(SOBJS): $(OBJP)%.o: $(SRCP)%.s
	$(AS) $(ASF) $(XASF) -o $@ $<

$(ETGTS): $(OUTP)%.elf: $(SRCP)$(TARGET_PREFIX)%.c $(LIBS)
	$(CC) $(CCF) $(XCCF) $(ECCF) $(DF) -o $@ $^

$(HTGTS): $(OUTP)%.hex: $(OUTP)%.elf
	$(OC) $(OCF) -F ihex $< $@

.PHONY: upload
upload:
	$(AD) $(ADF) $(XADF) -U:flash:w:$(HTGTS):x

.PHONY: see
see:
	$(OD) $(ODF) $(ETGTS) 

.PHONY: clean
clean:
	rm -rf $(OBJP)*
	rm -rf $(OUTP)*
