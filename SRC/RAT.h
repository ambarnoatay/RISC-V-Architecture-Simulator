#ifndef _RAT_H_
#define _RAT_H_
#include <inttypes.h>
#include <cstdlib>
#define MAX_ARF_REGS 32

class RAT_Entry {
public: 
    RAT_Entry() : valid(false), prf_id(-1) {
    }
    void set_valid(bool v) {
        valid = v;
    }
    void set_prf_id(uint64_t id) {
        prf_id = id;
    }
    int get_prf_id() {
        return prf_id;
    }
    bool is_valid() {
        return valid;
    }
private:

  bool     valid;
  int prf_id;
};

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////

class RAT {
public:
    RAT()
    {
        for(int i=0;i<MAX_ARF_REGS;i++)
        {
            this->RAT_Entries[i] = RAT_Entry();
        }
    }
    void print_state()
    {
        std::cout<<"Printing RAT... \n";
        for(int ii=0;ii<MAX_ARF_REGS;ii++)
        {
            printf("Rat Entry: %d Valid: %d \t\t", ii, this->RAT_Entries[ii].is_valid());
            printf("PRF_ID: %d \n", (int)this->RAT_Entries[ii].get_prf_id());
        }
        printf("\n");
    }
    int  get_remap(int arf_id)
    {
        if(this->RAT_Entries[arf_id].is_valid() && arf_id!=-1)
        {
            return (int)this->RAT_Entries[arf_id].get_prf_id();
        }
        return -1;
    }    
   void set_remap(int arf_id, int prf_id)
    {
        this->RAT_Entries[arf_id].set_prf_id(prf_id);
        this->RAT_Entries[arf_id].set_valid(true);
    }
    void reset_entry(int arf_id)
    {
        this->RAT_Entries[arf_id].set_prf_id(-1);
        this->RAT_Entries[arf_id].set_valid(false);
    }
    void flush()
    {
        for(int i=0;i<MAX_ARF_REGS;i++)
        {
            this->RAT_Entries[i].set_valid(false);

        }
    }

    bool isRATvalid(int prf)
    {
        return this->RAT_Entries[prf].is_valid();
    }
    
private:
  RAT_Entry  RAT_Entries[MAX_ARF_REGS];
};

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////



#endif

