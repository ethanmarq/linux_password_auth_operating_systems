CC      = gcc
CFLAGS  = -Wall -Wextra
LDLIBS  = -lcrypto -lpthread
TARGET  = hash512 asg1

all: $(TARGET)

hash512: hash512.c
	$(CC) $(CFLAGS) hash512.c -o $@ $(LDFLAGS) $(LDLIBS)

asg1: asg1.c
	$(CC) $(CFLAGS) -pthread asg1.c -o $@ $(LDFLAGS) $(LDLIBS)


clean:
	rm -f $(TARGETS)
