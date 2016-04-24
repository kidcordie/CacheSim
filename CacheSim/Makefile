OBJS = CacheSim.o CacheClass.o LRU.o stdafx.o
CC = g++
DEBUG = -g -std=c++11
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

CacheSim : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o CacheSim

CacheSim.o : stdafx.h CacheSim.cpp
	$(CC) $(CFLAGS) CacheSim.cpp

CacheClass.o : CacheClass.h CacheClass.cpp stdafx.h
	$(CC) $(CFLAGS) CacheClass.cpp

LRU.o : LRU.h LRU.cpp
	$(CC) $(CFLAGS) LRU.cpp

stdafx.o : stdafx.h stdafx.cpp
	$(CC) $(CFLAGS) stdafx.cpp

clean:
	\rm *.o CacheSim
