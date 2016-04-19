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
	bool vc_hit = false;
	bool address_overflow = false;
	unsigned long long int next_address;
	int next_bytes = 0;
	LRU* cache;
protected:
	int cachesize;
	int blocksize;
	int associativity;
	int hittime;
	int misstime;
	int bo_size;
	int index_size;
	int buswidth;
	unsigned long long int bo_mask;
	unsigned long long int index_mask;
	unsigned long long int tag_mask;
	//VictimCache* VC;
};

class L1Cache : public Cache
{
public:
	L1Cache(int cs, int bs, int assoc, int ht, int mt);
	~L1Cache();
	bool parseRequest(char ref, unsigned long long int address, unsigned int bytes);
	int getWriteRefs();
	int getReadRefs();
	int getInstRefs();
	unsigned long long int i_hitCnt = 0;
	unsigned long long int d_hitCnt = 0;
	unsigned long long int i_missCnt = 0;
	unsigned long long int d_missCnt = 0;
	unsigned long long int i_dirty_kickCnt = 0;
	unsigned long long int d_dirty_kickCnt = 0;
	bool dirtyKickout = false;
	unsigned long long int dirtyAddress;
	int extra_writes=0;
	int realign(unsigned long long int address, unsigned int bo, unsigned int bytes);
	LRU* i_cache;
protected:
	int write_refs=0;
	int read_refs=0;
	int inst_refs=0;
};

class L2Cache : public Cache
{
public:
	L2Cache(int cs, int bs, int assoc, int ht, int mt, int tt, int bw);
	~L2Cache();
	int getTransferTime();
	int getBusWidth();
	int hitCnt = 0;
	int missCnt = 0;
	bool parseRequest(unsigned long long int address, unsigned int bytes);
	void dirtyWrite(unsigned long long int address);
protected:
	int transfertime;
};
