//
// Created by Barak Gahtan on 31/08/2019.
//

#ifndef HW_5_NOA_BARAK_LIST_H
#define HW_5_NOA_BARAK_LIST_H
template<typename ...>
struct List;

template<typename Head, typename... Next>
struct List<Head, Next...> {
	typedef List<Next...> next;
    typedef Head head;
	constexpr static int size = next::size + 1;
};

template<>
struct List<> {
    constexpr static int size = 0;
};

template <typename ,typename >
struct PrependList;

template <typename type,typename... next>
struct PrependList<type,List<next...>>{
	typedef List<type,next...> list;
};

template <int N, typename>
struct GetAtIndex;

template <typename...T>
struct GetAtIndex<0,List<T...>>{
    typedef typename List<T...>::head value;
};

template <int N,typename...T>
struct GetAtIndex<N,List<T...>>{
	//we start from zero
	typedef typename GetAtIndex<N-1,typename List<T...>::next>::value value;
};

template <int N, typename Type, typename>
struct SetAtIndex;

template <int N,typename Type, typename...T>
struct SetAtIndex<N,Type,List<T...>>{
	typedef typename PrependList<typename List<T...>::head,typename SetAtIndex<N-1,Type,typename List<T...>::next>::list>::list list;
};

template <typename Type,typename...T>
struct SetAtIndex<0,Type,List<T...>>{
	typedef typename PrependList<Type,typename List<T...>::next>::list list;
};


#endif //HW_5_NOA_BARAK_LIST_H
