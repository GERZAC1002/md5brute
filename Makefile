CC = gcc
CFLAGS = -Wall -ffast-math -Os -s -fno-ident -fno-math-errno -ffunction-sections -fdata-sections -fno-stack-protector -fno-unwind-tables -fno-asynchronous-unwind-tables -Wl,--build-id=none -Wl,-z,norelro -Wl,--gc-sections -Wl,--hash-style=gnu 
ADD = -lpthread -lcrypto -static

md5brute:
	$(CC) $(CFLAGS) -o md5brute md5brute.c $(ADD)


clean:
	rm -f md5brute
