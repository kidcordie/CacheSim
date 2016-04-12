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
	bo_mask = ~(0xffffffffffff << (bo_size));
	index_mask = (~(0xffffffffffff << (bo_size + index_size))) - bo_mask;
	tag_mask = 0xffffffffffff - bo_mask - index_mask;
	cache = new int[cachesize];
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
	i_cache = new int[cachesize];
}
bool L1Cache::parseRequest(char ref, unsigned long long int address, unsigned int bytes)
{
	unsigned long long int current_tag = (address & tag_mask) >> (bo_size + index_size);
	unsigned long long int current_index = (address & index_mask) >> bo_size;
	unsigned long long int current_bo = address & bo_mask;
	std::cout << "tag: " << current_tag;
	std::cout << " index: " << current_index;
	std::cout << " bo: " << current_bo << std::endl;
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

LRU::LRU(int ind_size, int assoc)
{
    //here is where you make array that is index long of tag pointers that can be referenced by index
    lru_array = new tagNode*[ind_size];
    tagNode* dummy;
    for(int i=0; i<ind_size; i++)
    {
        //make dummy node for all sets
        dummy = lru_array[i];
        for(int j=0; j<assoc; j++)
        {
            add_tagNode(dummy);
            dummy = dummy->next;
        }
    }

    //victim cache
    for(int j=0; j<8; j++)
        {
            add_tagNode(vic_dummy);
            vic_dummy = vic_dummy->next;
        }
}
//append a tagNode to the end of an existing node
void LRU::add_tagNode(tagNode* prev)
{
    //create a new node
    tagNode* tmp = new tagNode;
    prev->next = tmp;
}
//takes current tagNode and puts it at the beginning of the LRU
void LRU::mov_tagNode(tagNode* current, tagNode* dummy)
{
    tagNode* tmp = dummy;
    //traverse
    while(tmp->next != current)
    {
        tmp = tmp->next;
    }
    tmp->next = current->next;
    tmp = dummy->next;
    dummy->next = current;
    current->next = tmp;
}
//takes a given index and traverses through LRU looking for given tag. Returns true for hit and false for miss
//also looks through victim cache
bool LRU::check_addr(unsigned long long int index, unsigned long long int in_tag, bool write)
{
    bool ret_bit = 0;
    tagNode* dummy;
    tagNode* start;

    dummy = lru_array[index];
    start = dummy->next;
    //traverse through LRU at index
    while(start != nullptr)
    {
        if(start->valid == 0)
        {
            //write in tag and set valid = 1. If dirty, dirty = 1
            start->valid = 1;
            start->tag = in_tag;
            if(write == true)
                start->dirty = 1;
            ret_bit = false;
            // WRITE TO L2
            break;
        }
        else
        {
            //check tag
            if(start->tag == in_tag) //hit
            {
                ret_bit = true;
                break;
            }
            else
                start = start->next; //check next tag_node
        }
    }
    if(start == nullptr) //reached the end of the LRU, need to check victim cache
    {
        tagNode* vic_start = vic_dummy->next;
        tagNode* vic_cpy;
        tagNode* cpy;
        while(vic_start != nullptr)
        {
            if(vic_start->valid == 0)  //miss, write in values
            {
                vic_start->valid = 1;
                vic_start->tag = in_tag;
                if(write == true)
                    vic_start->dirty = 1;
            }
            else
            {
                if(vic_start->tag == in_tag)  //hit
                {
                    //SWAP VALUES IN PREV_CACHE LRU
                    //vic_cpy = vic_start;
                    cpy = start;
                    cpy->tag = start->tag;
                    cpy->dirty = start->dirty;
                    start = vic_start;
                    start->tag = vic_start->tag;
                    //dirty bit?
                    vic_start = cpy;
                    vic_start->tag = cpy->tag;
                    vic_start->dirty = cpy->dirty;
                    mov_tagNode(start, dummy);
                    mov_tagNode(vic_start, vic_dummy);
                }
                else
                    vic_start = vic_start->next;
            }
        }
    }

    return ret_bit;
}

