#pragma once

class VictimCache
{
public:
	VictimCache(int bo);
protected:
	int block_offset;
	int bo_size;
	int tag_size;
};

class Cache
{
public:
	Cache(int cs, int bs, int assoc, int ht, int mt);
	int getCacheSize();
	int getBlockSize();
	int getAssociativity();
	int getHitTime();
	int getMissTime();
	~Cache();

protected:
	int cachesize;
	int blocksize;
	int associativity;
	int hittime;
	int misstime;
	int index_size;
	int bo_size;
	int tag_size;
	int* cache;
	VictimCache* VC;
};

class L2Cache : public Cache
{
public:
	L2Cache(int cs, int bs, int assoc, int ht, int mt, int tt, int bw);
	int getTransferTime();
	int getBusWidth();
protected:
	int transfertime;
	int buswidth;
};
