#pragma once

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
	int bo_size;
	int index_size;
	unsigned long long int bo_mask;
	unsigned long long int index_mask;
	unsigned long long int tag_mask;
	LRU* cache;
	//VictimCache* VC;
};

class L1Cache : public Cache
{
public:
	L1Cache(int cs, int bs, int assoc, int ht, int mt);
	bool parseRequest(char ref, unsigned long long int address, unsigned int bytes);
	int getWriteRefs();
	int getReadRefs();
	int getInstRefs();
	int i_hitCnt = 0;
	int d_hitCnt = 0;
	int i_missCnt = 0;
	int d_missCnt = 0;
protected:
	LRU* i_cache;
	int write_refs=0;
	int read_refs=0;
	int inst_refs=0;
};

class L2Cache : public Cache
{
public:
	L2Cache(int cs, int bs, int assoc, int ht, int mt, int tt, int bw);
	int getTransferTime();
	int getBusWidth();
	bool parseRequest(unsigned long long int address, unsigned int bytes);
protected:
	int transfertime;
	int buswidth;
};
