//
// Created by Barak Gahtan on 31/08/2019.
//

#ifndef HW_5_NOA_BARAK_UTILITIES_H
#define HW_5_NOA_BARAK_UTILITIES_H

template <bool exp,int True,int False>
struct ConditionalInteger{
    constexpr static int value=True;
};

template <int True,int False>
struct ConditionalInteger<false, True, False>{
    constexpr static int value = False;
};

template <bool exp,typename True,typename False>
struct Conditional{
	typedef True value;
};

template <typename True,typename False>
struct Conditional<false,True,False>{
	typedef False value;
};


#endif //HW_5_NOA_BARAK_UTILITIES_H
