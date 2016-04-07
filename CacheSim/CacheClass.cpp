#include "stdafx.h"


Cache::Cache(int cs, int bs, int assoc, int ht, int mt)
{
	cachesize = cs;
	blocksize = bs;
	associativity = assoc;
	hittime = ht;
	misstime = mt;
	index_size = int(log2f(cs));
	bo_size = int(log2f(bs));
	std::cout << "index: " << index_size << std::endl;
	std::cout << "block offset: " << bo_size << std::endl;
	tag_size = 64 - bo_size - index_size;
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

VictimCache::VictimCache(int bo) 
{
	block_offset = bo;
	tag_size = 64 - bo_size;
}
