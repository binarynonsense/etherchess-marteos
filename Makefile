.PHONY: clean default etherchess.exe

CC = mgcc
#CFLAGS = -Wall -I../../arch/drivers/svga
CFLAGS = -Wall -I/home/alvaro/bin/marte/arch/drivers/svga
LDFLAGS = -lsvga -lm
GNATMAKE = mgnatmake
ADAFLAGS = -gnata -gnato -g

default: etherchess.exe

etherchess.exe: 
	$(CC) $(CFLAGS) main.c draw.c net.c fonts.c $(LDFLAGS) -o $@;

clean:
	@exec echo -e "\n>> Cleaning... ";
	@find \( -name '*.[oa]' -or -name '*~*' -or -name '*.ali' -or -name '*.log' \
		-or -name '*.exe' -or -name 'mprogram' -or -name 'a.out' \) -print -delete
	@exec echo ">> End Cleaning"
