#include "Cache.h"
#include<iostream>
int32_t   HIT_LATENCY=2;//
int32_t   MISS_LATENCY=20;//
Cache::Cache(int size, int associativity, int lineSize) {
    // Implement cache initialization logic based on size and associativity
    this->associativity = associativity;
    this->size = size;
    this->lineSize = lineSize;
    
    this->lookups = 0;
    this->hits = 0;
    this->offset_bits = (int)log2(this->lineSize);
   
    
    this->linesPerSet = this->size / (this->lineSize * this->associativity);
    this->index_bits = (int)log2(this->linesPerSet);
    this->tag_bits = 16 - this->index_bits - this->offset_bits;
    for(int i = 0; i < this->associativity; i++)
    {
        Cache_set *set1 = new Cache_set(this->linesPerSet);
        this->sets.push_back(set1);
    }
    
}

bool Cache::readData(Addr address, int& data) const {
    // Implement cache read logic
    return false; // Placeholder value
}

void Cache::writeData(Addr address, int data) {
    // Implement cache write logic
}
void Cache::printStats()
{
    printf("Cache hits %d\n",this->hits);
    printf("Cache lookups %d\n",this->lookups);
    printf("Cache miss rate %f\n",(float)((this->lookups-this->hits)*(100))/this->lookups);

}
void Cache::printCache()
{
    for(int i = 0;i < this->associativity; i++)
    {
        for(int j = 0; j < this->linesPerSet; j++)
        {
            std::cout << "Set " << i << " Line " << j << " Tag " << this->sets[i]->line[j].tag << " Valid " << this->sets[i]->line[j].valid << " Dirty " << this->sets[i]->line[j].dirty << " Last Access Time " << this->sets[i]->line[j].last_access_time << " Frequency " << this->sets[i]->line[j].frequency << " Core ID " << this->sets[i]->line[j].core_id << std::endl;
        }
    }

}
int Cache::cache_lookup(Addr address,int write)
{
    this->lookups++;
    Addr tag_look = address>>(this->index_bits+this->offset_bits);
    Addr idx = (address>>this->offset_bits) & ((1<<this->index_bits)-1);

    printf("Tag: %d Index: %d\n",tag_look,idx);
    if (this->index_bits == 0)
    {

        for (int i = 0; i < this->associativity; i++)
        {
            for (int j = 0; j < this->linesPerSet; j++)
            {
                if (this->sets[i]->line[j].tag == tag_look && this->sets[i]->line[j].valid == true)
                {
                    this->hits++;
                    return HIT_LATENCY;
                }
            }
        }
    }
    else
    {
        for (int i = 0; i < this->associativity; i++)
        {
            if (this->sets[i]->line[idx].tag == tag_look && this->sets[i]->line[idx].valid == true)
            {
                printf("HIT\n");
                this->hits++;
                return HIT_LATENCY;
            }
        }
    } 
    this->cache_insert(address);
    return MISS_LATENCY;

}
void Cache::cache_insert(Addr addr)
{

    Addr tag = addr>>(this->index_bits+this->offset_bits);
    Addr index = (addr>>this->offset_bits) & ((1<<this->index_bits)-1);
    if(this->index_bits==0)
    {

        for (int i = 0; i < this->associativity; i++)
        {
            for (int j = 0; j < this->linesPerSet; j++)
            {
                if (this->sets[i]->line[j].valid == false)
                {
                    this->sets[i]->line[j].valid = true;
                    this->sets[i]->line[j].tag = tag;
                    this->sets[i]->line[j].last_access_time = 0;
                    this->sets[i]->line[j].frequency = 0;
                    this->sets[i]->line[j].core_id = 0;
                    return;
                }
            }
        }
    }
    else
    {
        for (int i = 0; i < this->associativity; i++)
        {
            if (this->sets[i]->line[index].valid == false)
            {
                this->sets[i]->line[index].valid = true;
                this->sets[i]->line[index].tag = tag;
                this->sets[i]->line[index].last_access_time = 0;
                this->sets[i]->line[index].frequency = 0;
                this->sets[i]->line[index].core_id = 0;
                return;
            }
            
        }
        

            this->sets[0]->line[index].valid = true;
            this->sets[0]->line[index].tag = tag;
            this->sets[0]->line[index].last_access_time = 0;
            this->sets[0]->line[index].frequency = 0;
            this->sets[0]->line[index].core_id = 0;
            return;
        
    }
    //this->cache_remove_lru(addr);
  //  this->cache_insert(addr);
}
void Cache::cache_remove_lru(Addr address)
{
    int min = 0;
    for(int i=0;i<this->associativity;i++)
    {
        for(int j=0;j<this->linesPerSet;j++)
        {
            if(this->sets[i]->line[j].last_access_time < this->sets[min]->line[j].last_access_time)
            {
                min = i;
            }
        }
    }
    this->sets[min]->line[0].valid = false;
    this->sets[min]->line[0].dirty = false;
    this->sets[min]->line[0].tag = 0;
    this->sets[min]->line[0].last_access_time = 0;
    this->sets[min]->line[0].frequency = 0;
    this->sets[min]->line[0].core_id = 0;
}
void Cache::updateLRU() {

}
   
