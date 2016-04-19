#include "stdafx.h"
LRU::LRU(int ind_size, int assoc, int index_bits, int block_offset)
{
	index_size = ind_size;
	index_bit_size = index_bits;
	bo_size = block_offset;
	//here is where you make array that is index long of tag pointers that can be referenced by index
	lru_array = new tagNode*[ind_size];
	tagNode* dummy;
	for (int i = 0; i<ind_size; i++)
	{
		//make dummy node for all sets
		lru_array[i] = new tagNode;
		dummy = lru_array[i];
		for (int j = 0; j<assoc; j++)
		{
			add_tagNode(dummy);
			dummy = dummy->next;
		}
	}
	//make victim cache
	vic_dummy = makeVictim();
}

LRU::~LRU()
{
	tagNode* dummy;
	tagNode* start;
	for (unsigned int i = 0; i < index_size; ++i)
	{
		dummy = lru_array[i];
		start = dummy->next;
		while (start != nullptr) {
			if (start->valid) {
				i = i;
				//std::cout << std::hex << i << ": " << std::hex << start->tag << std::endl;
			}
			start = start->next;
		}
	}
	start = vic_dummy->next;
	std::cout << "VC" << std::endl;
	std::cout << vc_trans << std::endl;
	while (start != nullptr) {
		if (start->valid) {
			//std::cout << std::hex << start->tag << std::endl;
		}
		start = start->next;
	}
}

tagNode* LRU::makeVictim()
{
    //victim cache
    tagNode* vic_node = new tagNode;
    tagNode* vic_dumb = vic_node;

	for (int j=0; j<8; j++)
	{
		add_tagNode(vic_node);
		vic_node = vic_node->next;
	}
	return vic_dumb;
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
	while (tmp->next != current)
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
	tagNode* prev;
	dummy = lru_array[index];
	start = dummy->next;
	//traverse through LRU at index
	while (start != nullptr)
	{
		if (start->valid == 0)
		{
			//write in tag and set valid = 1. If dirty, dirty = 1
			start->valid = 1;
			start->tag = in_tag;
			if (write == true)
				start->dirty = 1;
			ret_bit = false;
			// WRITE TO L2
			return ret_bit;
		}
		else
		{
			//check tag
			if (start->tag == in_tag) //hit
			{
				ret_bit = true;
				return ret_bit;
			}
			else
			{
				prev = start;
				start = start->next; //check next tag_node
			}
		}
	}
	if (start == nullptr) //reached the end of the LRU, need to check victim cache
	{
		tagNode* vic_start;
		tagNode* cpy = new tagNode;
		unsigned long long vic_in_tag = (in_tag << index_bit_size + bo_size) | (index << bo_size);
		vic_start = vic_dummy->next;
		tagNode* vic_prev = vic_dummy;
		//This was loading in the current address instead of the kicked address
		while (vic_start != nullptr)
		{ //ENTERS WHILE LOOP
			//std::cout << std::hex << vic_start->tag << std::endl;
			if (vic_start->valid == 0)  //miss, write in values
			{
				vic_start->valid = 1;
				vic_start->tag = (prev->tag << index_bit_size + bo_size) | (index << bo_size);
				vic_start->dirty = prev->dirty;
				mov_tagNode(vic_start, vic_dummy);
				prev->tag = in_tag;
				prev->dirty = int(write);
				mov_tagNode(prev, dummy);
				return ret_bit;
			}
			else
			{
				if (vic_start->tag == vic_in_tag)  //hit
				{
					vc_hit = true;
					//SWAP VALUES IN PREV_CACHE LRU
					*cpy = *prev;
					cpy->tag = prev->tag;
					cpy->dirty = prev->dirty;
					//set prev info to victim cache info:
					prev->tag = in_tag;
					prev->dirty = vic_start->dirty;
					//set victim cache info to prev info:
					vic_start->tag = (cpy->tag << index_bit_size + bo_size) | (index << bo_size);
					vic_start->dirty = cpy->dirty;

					mov_tagNode(prev, dummy);
					mov_tagNode(vic_start, vic_dummy);
					vc_trans++;
					//delete cpy;
					return ret_bit;
				}
				else
				{
					vic_start = vic_start->next;
					vic_prev = vic_prev->next;
				}
			}
		}
		if(vic_start == nullptr)
		{
			if (vic_prev->dirty == 1) {
				this->dirtyKickout = true;
				this->dirtyAddress = vic_prev->tag << bo_size;
			}
			*cpy = *prev;
			cpy->tag = prev->tag;
			cpy->dirty = prev->dirty;
			//set prev info to victim cache info:
			prev->tag = in_tag;
			prev->dirty = 0;
			//set victim cache info to prev info:
			vic_prev->tag = (cpy->tag << index_bit_size + bo_size) | (index << bo_size);
			vic_prev->dirty = cpy->dirty;

			mov_tagNode(prev, dummy);
			mov_tagNode(vic_prev, vic_dummy);
			this->kickouts++;
			// Not sure if I should be incrementing vc_trans
			//vc_trans++;
		}
		delete cpy;
	}

	cunt++;
	//std::cout<<"hit/miss bool count: "<<cunt<<"\n";
	return ret_bit;
}
