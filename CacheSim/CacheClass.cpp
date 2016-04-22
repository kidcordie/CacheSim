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
	cache = new LRU(cs, associativity, index_size, bo_size);
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
	buswidth = 4;
	i_cache = new LRU(cs, associativity, index_size, bo_size);
}

L1Cache::~L1Cache()
{
	std::cout << "Memory Level: L1i" << std::endl;
	delete(i_cache);
	std::cout << "Memory Level: L1d" << std::endl;
	delete(cache);
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
	/*std::cout << "tag: " << std::hex << tag << " index: " << std::hex << index <<
		" Byte offset: " << bo << std::endl;*/
	bool hit = false;
	bool write = false;
	bool inst = false;
	if (ref == 'W') {
		write_refs++;
		write = true;
	}
	if (ref == 'I')
	{
	    inst = true;
		//check i cache
		inst_refs++;
		hit = i_cache->check_addr(index, tag, write, bo);
		if (hit) {
			i_hitCnt += realign(address, bo, bytes);
			inst_cnt += realign(address, bo, bytes);
		}
		else {
			if (i_cache->vc_hit) {
				i_cache->vc_hit = false;
				vc_hit = true;
				inst_cnt++;
			}
			i_hitCnt += realign(address, bo, bytes) - 1;
			inst_cnt += realign(address, bo, bytes) - 1;

			i_missCnt++;
			inst_cnt++;
		}
	}
	else
	{
		//check d cache
		if (!write)
			read_refs++;

		hit = cache->check_addr(index, tag, write, bo);

		if (hit){
			d_hitCnt += realign(address, bo, bytes);
			if (write)
            {
                wrt_cnt += realign(address, bo, bytes);
            }
			else
                read_cnt += realign(address, bo, bytes);
		}
		else { //miss
			if (cache->vc_hit) {
				cache->vc_hit = false;
				vc_hit = true;
				if (inst)
                    inst_cnt++;
                else if (write)
                    wrt_cnt++;
                else
                    read_cnt++;
				//time_count++;
			}
			d_hitCnt += realign(address, bo, bytes) - 1;
			if (inst)
                inst_cnt += realign(address, bo, bytes) - 1;
            else if (write)
                wrt_cnt += realign(address, bo, bytes) - 1;
            else
                read_cnt += realign(address, bo, bytes) - 1;
			//time_count += realign(address, bo, bytes) - 1;
			d_missCnt++;
			if (inst)
                inst_cnt++;
            else if (write)
                wrt_cnt++;
            else
                read_cnt++;
			//time_count++;
		}
		if (write && address_overflow)
			extra_writes++;
		if (cache->dirtyKickout == true) {
			d_dirty_kickCnt++;
			dirtyKickout = true;
			dirtyAddress = cache->dirtyAddress;
			cache->dirtyKickout = false;
		}
	}
	return hit;
}

int L1Cache::realign(unsigned long long int address, unsigned int bo, unsigned int bytes)
{
	//distance in bytes from start of current word
	int start = bo % 4;
	//amount of bytes to include after last byte
	int new_bytes = bytes - (4 - start);
	int transfers = 1;
	//stuck here
	if (bo + bytes > 32) {
		int new_byte_request = (bo + bytes) - 32;
		int ebytes = bytes - new_byte_request;
		address_overflow = true;
		new_bytes = new_bytes - new_byte_request;
		next_address = address + ebytes;
		next_bytes = new_byte_request;
	}
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

L2Cache::~L2Cache()
{
	std::cout << "Memory Level: L2" << std::endl;
	delete(cache);
}

int L2Cache::getTransferTime()
{
	return transfertime;
};

int L2Cache::getBusWidth()
{
	return buswidth;
};

bool L2Cache::parseRequest(char ref, unsigned long long int address, unsigned int bytes)
{
	unsigned long long int tag = (address & tag_mask) >> (bo_size + index_size);
	unsigned long long int index = (address & index_mask) >> bo_size;
	unsigned long long int bo = address & bo_mask;
	bool hit = false;
	bool write = false;

	hit = cache->check_addr(index, tag, write, bo);
    //add transfer time between L1 and L2 plus L1 replay time
    if (ref == 'I')
        inst_cnt = inst_cnt + 21;
    else if (ref == 'W')
        wrt_cnt = wrt_cnt + 21;
    else
        read_cnt = read_cnt + 21;
	//time_count = time_count + 21;
	if (hit) {
		hitCnt++;
		if (ref == 'I')
            inst_cnt = inst_cnt + 8;
        else if (ref == 'W')
            wrt_cnt = wrt_cnt + 8;
        else
            read_cnt = read_cnt + 8;
		//time_count = time_count + 8;
	}
	else {
		if (cache->vc_hit)
        {
            cache->vc_hit = false;
            vc_hit = true;
            //add replay time
            //time_count = time_count + 8;
            if (ref == 'I')
                inst_cnt = inst_cnt + 8;
            else if (ref == 'W')
                wrt_cnt = wrt_cnt + 8;
            else
                read_cnt = read_cnt + 8;
        }
        else
        {
            //no VC hit or L2 hit, add mem access time and L2 and L1 hit replay time
            //time_count = time_count + 188;
            if (ref == 'I')
                inst_cnt = inst_cnt + 188;
            else if (ref == 'W')
                wrt_cnt = wrt_cnt + 188;
            else
                read_cnt = read_cnt + 188;
        }
        //time_count = time_count + 10;
        if (ref == 'I')
            inst_cnt = inst_cnt + 10;
        else if (ref == 'W')
            wrt_cnt = wrt_cnt + 10;
        else
            read_cnt = read_cnt + 10;
		missCnt++;
	}
	if(cache->dirtyKickout == true)
    {
        dirty_kickCnt++;
        cache->dirtyKickout = false;
    }
	return hit;
}

void L2Cache::dirtyWrite(unsigned long long int address) {
	unsigned long long int tag = (address & tag_mask) >> (bo_size + index_size);
	unsigned long long int index = (address & index_mask) >> bo_size;
	bool hit = false;
	unsigned long long int bo = address & bo_mask;

	bool write = true;
	hit = cache->check_addr(index, tag, write, bo);
	//add transfer time between L1 and L2 plus L1 replay time
	//time_count = time_count + 21;
	wrt_cnt = wrt_cnt + 21;
	if (hit)
    {
        hitCnt++;
        //add L2 hit time
        //time_count = time_count + 8;
        wrt_cnt = wrt_cnt + 8;
    }
    else
    {
        if (cache->vc_hit)
        {
            cache->vc_hit = false;
            vc_hit = true;
            //add replay time
            //time_count = time_count + 8;
            wrt_cnt = wrt_cnt + 8;
        }
        else
        {
            //no VC hit or L2 hit, add mem access time and L2 and L1 hit replay time
            //time_count = time_count + 188;
            wrt_cnt = wrt_cnt + 188;
        }
        missCnt++;
        //add miss time
        //time_count = time_count + 10;
        wrt_cnt = wrt_cnt + 10;
    }

	if(cache->dirtyKickout == true)
    {
        wrt_cnt = wrt_cnt + 188 + 21;
        //time_count = time_count + 180;
        dirty_kickCnt++;
        cache->dirtyKickout = false;
    }
	return;
}
