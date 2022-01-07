# Compiler settings
CC = gcc
CFLAGS = -Wall -O2
TFLAG = -lpthread

# Files
f_version1 = ver1.c
f_version2 = ver2.c
f_version3 = ver3.c
header = utils.h

all: version1 version2 version3

# @ means output file
# ^ means ALL input files
version1: $(f_version1) $(header)
	$(CC) $(CFLAGS) $^ -o $@

version2: $(f_version2) $(header)
	$(CC) $(CFLAGS) $^ -o $@

#TFLAG should always be at the end
version3: $(f_version3) $(header)
	$(CC) $(CFLAGS) $^ -o $@ $(TFLAG)

clean:
	rm -f version1 version2 version3
