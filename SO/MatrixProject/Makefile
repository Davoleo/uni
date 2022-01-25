# Compiler settings
CC = gcc
CFLAGS = -Wall -O2
TFLAG = -lpthread

# Files
f_version1 = ver1.c
f_version2 = ver2.c
# f_version2.5 = ver2.5.c
f_version3 = ver3.c
header = utils.h

output_dir = out

all: version1 version2 version3 

# @ means output file
# ^ means ALL input files
version1: $(f_version1) $(header) | $(output_dir)
	$(CC) $(CFLAGS) $^ -o $(output_dir)/$@

version2: $(f_version2) $(header) | $(output_dir)
	$(CC) $(CFLAGS) $^ -o $(output_dir)/$@

# version2.5: $(f_version2.5) $(header)
# 	$(CC) -Wall $^ -o $@ $(TFLAG)

#TFLAG should always be at the end
version3: $(f_version3) $(header) | $(output_dir)
	$(CC) $(CFLAGS) $^ -o $(output_dir)/$@ $(TFLAG)

docs:
	doxygen

$(output_dir):
	@echo "Creating directory '$(output_dir)'..."
	mkdir -p $@

clean:
	rm -rf out
