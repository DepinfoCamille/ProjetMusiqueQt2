#pragma once
#include <map>
#include "Partition.h"
#include <tuple>
#include <vector>
#include <windows.h>


#include <yvals.h>
#include <stdlib.h>
#include <math.h>

#pragma pack(push,_CRT_PACKING)
#pragma warning(push,_STL_WARNING_LEVEL)
#pragma warning(disable: _STL_DISABLED_WARNINGS)
#pragma push_macro("new")

static unsigned long changer_instrument(int channel, int numinstrument)  ;
static unsigned long appuyer_touche(int channel, int note, int force) ;
static unsigned long relacher_touche(int channel, int note, int force) ;

class Son
{
    public:
        Son(Partition* p);
        virtual ~Son();
        std::vector<std::tuple<std::string,int>> dicco_son/*(size_t taille = 14)*/ ;
        int note(int n) ;
        void lecturePartition(Partition *p ) ; //joue la partition
        Partition *partition ;


    protected:

    private:


};
