#include "stdafx.h"



Cache::Cache(int cs, int bs, int assoc, int ht, int mt)
{
	cachesize = cs;
	blocksize = bs;
	associativity = assoc;
	hittime = ht;
	misstime = mt;
	//subtract 1 because it takes size-1 bits to represent the size
	index_size = int(log2f(cs)) - 1;
	bo_size = int(log2f(bs)) - 1;
	bo_mask = ~(0xffffffffffffffff << (bo_size));
	index_mask = (~(0xffffffffffffffff << (bo_size + index_size))) - bo_mask;
	tag_mask = 0xffffffffffffffff - bo_mask - index_mask;
	cache = new LRU(cs, associativity);
}	

Cache::~Cache()
{
	std::cout << "deleting cache" << std::endl;
	delete(cache);
}

int Cache::getCacheSize()
{
	return cachesize;
};

int Cache::getBlockSize()
{
	return blocksize;
};

int Cache::getAssociativity()
{
	return associativity;
};

int Cache::getHitTime()
{
	return hittime;
};

int Cache::getMissTime()
{
	return misstime;
};


L1Cache::L1Cache(int cs, int bs, int assoc, int ht, int mt) :Cache(cs, bs, assoc, ht, mt)
{
	i_cache = new LRU(cs, associativity);
}

//Returns Boolean value True if Hit False if Miss
bool L1Cache::parseRequest(char ref, unsigned long long int address, unsigned int bytes)
{
	unsigned long long int tag = (address & tag_mask) >> (bo_size + index_size);
	unsigned long long int index = (address & index_mask) >> bo_size;
	unsigned long long int bo = address & bo_mask;
	std::cout << "tag: " << tag;
	std::cout << " index: " << index;
	std::cout << " bo: " << bo << std::endl;
	bool hit = false;
	bool write = false;
	if (ref == 'W')
		write = true;
	if (ref == 'I')
	{
		std::cout << "I" << std::endl;
		hit = i_cache->check_addr(index, tag, write);
		return hit;
		//check i cache
	}
	else
	{
		hit = cache->check_addr(index, tag, write);
		return hit;
		//check d cache
	}
}

L2Cache::L2Cache(int cs, int bs, int assoc, int ht, int mt, int tt, int bw) :Cache(cs, bs, assoc, ht, mt)
{
	transfertime = tt;
	buswidth = bw;
}
int L2Cache::getTransferTime()
{
	return transfertime;
};
int L2Cache::getBusWidth()
{
	return buswidth;
};

bool L2Cache::parseRequest(unsigned long long int address, unsigned int bytes)
{
	unsigned long long int tag = (address & tag_mask) >> (bo_size + index_size);
	unsigned long long int index = (address & index_mask) >> bo_size;
	unsigned long long int bo = address & bo_mask;
	bool hit = false;
	bool write = false;
	hit = cache->check_addr(index, tag, write);
	return hit;
	//check L2 cache
}
