#include "stdafx.h"



Cache::Cache(int cs, int bs, int assoc, int ht, int mt)
{
	cachesize = cs;
	blocksize = bs;
	associativity = assoc;
	hittime = ht;
	misstime = mt;
	//subtract 1 because it takes size-1 bits to represent the size
	index_size = int(log2f(cs/(bs*associativity)));
	bo_size = int(log2f(bs));
	bo_mask = ~(0xffffffffffffffff << (bo_size));
	index_mask = (~(0xffffffffffffffff << (bo_size + index_size))) & ~bo_mask;
	tag_mask = 0xffffffffffffffff & ~(bo_mask | index_mask);
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
int L1Cache::getWriteRefs()
{
	return write_refs;
}

int L1Cache::getReadRefs()
{
	return read_refs;
}

int L1Cache::getInstRefs()
{
	return inst_refs;
}

//Returns Boolean value True if Hit False if Miss
bool L1Cache::parseRequest(char ref, unsigned long long int address, unsigned int bytes)
{
	unsigned long long int tag = (address & tag_mask) >> (bo_size + index_size);
	unsigned long long int index = (address & index_mask) >> (bo_size);
	unsigned long long int bo = address & bo_mask;
	std::cout << "tag: " << std::hex << tag << " index: " << std::hex << index <<
		" Byte offset: " << bo << std::endl;
	bool hit = false;
	bool write = false;
	if (ref == 'W') {
		write_refs++;
		write = true;
	}
	if (ref == 'I')
	{
		//check i cache
		inst_refs++;
		hit = i_cache->check_addr(index, tag, write);
		if (hit) {
			i_hitCnt += realign(bo, bytes);
		}
		else {
			i_hitCnt += realign(bo, bytes) - 1;
			i_missCnt++;
		}
	}
	else
	{
		//check d cache
		if (!write)
			read_refs++;

		hit = cache->check_addr(index, tag, write);

		if (hit){
			//d_hitCnt++;
			d_hitCnt += realign(bo, bytes);
		}
		else {
			d_hitCnt += realign(bo, bytes) - 1;
			d_missCnt++;
		}
	}
	return hit;
}

int L1Cache::realign(unsigned int bo, unsigned int bytes)
{
	//distance in bytes from start of current word
	int start = bo % 4;
	//amount of bytes to include after last byte
	int new_bytes = bytes - (4 - start);
	int transfers = 1;
	if (new_bytes > 0) {
		transfers+= (new_bytes / 4) + (new_bytes % 4 != 0);
	}
	return transfers;
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
