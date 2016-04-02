#include "stdafx.h"


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

Cache::Cache(int cs, int bs, int assoc, int ht, int mt)
{
	cachesize = cs;
	blocksize = bs;
	associativity = assoc;
	hittime = ht;
	misstime = mt;
}

int L2Cache::getTransferTime()
{
	return transfertime;
};
int L2Cache::getBusWidth()
{
	return buswidth;
};

L2Cache::L2Cache(int cs, int bs, int assoc, int ht, int mt, int tt, int bw) :Cache(cs, bs, assoc, ht, mt)
{
	transfertime = tt;
	buswidth = bw;
}