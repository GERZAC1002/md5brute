CC = gcc
CFLAGS = -Wall -ffast-math -Os -s -fno-ident -fno-math-errno -ffunction-sections -fdata-sections -fno-stack-protector -fno-unwind-tables -fno-asynchronous-unwind-tables -Wl,--build-id=none -Wl,-z,norelro -Wl,--gc-sections -Wl,--hash-style=gnu 
ADD = -lpthread -lcrypto -static

bruteforcemd5:
	$(CC) $(CFLAGS) -o bruteforcemd5_v3 bruteforcemd5_v3.c $(ADD)


clean:
	rm -f bruteforcemd5 bruteforcemd5_v2 bruteforcemd5_v3
