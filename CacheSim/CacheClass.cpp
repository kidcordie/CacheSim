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
	bo_mask = ~(0xFFFFFFFF << (bo_size));
	index_mask = (~(0xFFFFFFFF << (bo_size + index_size))) - bo_mask;
	tag_mask = 0xFFFFFFFF - bo_mask - index_mask;
	cache = new int[cachesize];
	VC = new VictimCache(bo_size);
}
Cache::~Cache()
{
	std::cout << "deleting cache" << std::endl;
	delete(cache);
	delete(VC);
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
	i_cache = new int[cachesize];
}
bool L1Cache::parseRequest(char ref, unsigned long long int address, unsigned int bytes)
{
	unsigned long long int current_tag = (address & tag_mask) >> (bo_size + index_size);
	unsigned long long int current_index = (address & index_mask) >> bo_size;
	unsigned long long int current_bo = address & bo_mask;
	bool hit = false;
	if (ref == 'I')
	{
		return hit;
		//check i cache
	}
	else
	{
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
	return hit;
	//check L2 cache
}

VictimCache::VictimCache(int bo) 
{
	bo_size= bo;
	tag_size = 64 - bo_size;
}
