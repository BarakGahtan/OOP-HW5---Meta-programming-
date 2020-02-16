//
// Created by Barak Gahtan on 31/08/2019.
//

#ifndef HW_5_NOA_BARAK_RUSHHOUR_H
#define HW_5_NOA_BARAK_RUSHHOUR_H

#include "MoveVehicle.h"

template <CellType,typename>
struct getCarCol;

template <CellType CT,typename T>
struct getCarCol< CT,List<T>>
{
    // last cell in row, if it is not red we cant find the red in this row
    constexpr static int carCol=ConditionalInteger<T::type==CT,0, -999999>::value;
};

template <CellType CT,typename... T>
struct getCarCol< CT,List<T...>>
{
    typedef typename List<T...>::head currCell;
    constexpr static int carCol= ConditionalInteger<currCell::type==CT, 0, 1+getCarCol<CT,typename List<T...>::next>::carCol>::value;
};

template <CellType CT,typename...T>
struct getCarRow;

template <CellType CT,typename T>
struct getCarRow< CT,List<T>>
{
    // last cell in col, if it is not red we cant find the red in current row
    constexpr static int carRow=ConditionalInteger<getCarCol<CT,T>::carCol >=0, 0, -999999>::value;
};

template <CellType CT,typename...T>
struct getCarRow< CT,List<T...>>
{
    constexpr static int carRow= ConditionalInteger<getCarCol<CT,typename List<T...>::head>::carCol>=0,0,1+getCarRow<CT,typename List<T...>::next>::carRow>::value;
};

template <CellType CT,typename... T>
struct findCarStart;

template <CellType CT,typename... T>
struct findCarStart<CT, List<T...>>
{
    static_assert(CT!=CellType::EMPTY,"Fail");
    typedef typename List<T...>::head currCell;
    typedef typename Conditional<CT==currCell::type,
            typename List<T...>::next,
            typename findCarStart<CT,typename List<T...>::next>::firstCell>::value firstCell;
};

template <CellType CT,typename T>
struct findCarStart<CT, List<T>>
{
    static_assert(CT!=CellType::EMPTY,"Fail");
    typedef List<T> firstCell;
};
template < CellType CT,typename... T>
struct isPathEmpty;

template < CellType CT,typename... T>
struct isPathEmpty< CT,List<T...>>
{
    static_assert(CT!=CellType::EMPTY,"CELL TYPE WE PASS IS EMPTY");
    typedef typename List<T...>::head currCell;
    constexpr static bool result= ((currCell::type!=CT) && (currCell::type!=CellType::EMPTY))? false: (isPathEmpty< CT, typename List<T...>::next>::result);
};

template <CellType CT,typename T>
struct isPathEmpty< CT,List<T>>
{
    constexpr static bool result= (T::type==CellType::EMPTY ||T::type==CT);
};

template<typename GB>
struct CheckWin{
    constexpr static int carRow = getCarRow<CellType::X, typename GB::gameBoard>::carRow;
    typedef typename GetAtIndex<carRow, typename GB::gameBoard>::value pathRow;
    typedef typename findCarStart<CellType::X,pathRow>::firstCell cell;
    constexpr static bool result= isPathEmpty<CellType::X,cell>::result;
};

template<typename GB, typename...Move>
struct CheckSolution;

template<typename GB, typename...Move>
struct CheckSolution<GB, List<Move...>>
{
    typedef typename List<Move...>::head nextMove;
    constexpr static int carRow = getCarRow<nextMove::type,typename GB::gameBoard>::carRow;
    typedef typename GetAtIndex<carRow, typename GB::gameBoard>::value pathRow;
    constexpr static int carCol = getCarCol<nextMove::type,pathRow>::carCol;
    typedef typename MoveVehicle<GB,carRow, carCol, nextMove::direction, nextMove::amount>::board nextBoardState;
    constexpr static bool result=CheckSolution<nextBoardState ,typename List<Move...>::next>::result;
};

template<typename GB, typename Move>
struct CheckSolution<GB, List<Move>>
{
    constexpr static int carRow = getCarRow<Move::type,typename GB::gameBoard>::carRow;
    typedef typename GetAtIndex<carRow, typename GB::gameBoard>::value pathRow;
    constexpr static int carCol = getCarCol<Move::type,pathRow>::carCol;
    typedef typename MoveVehicle<GB,carRow, carCol, Move::direction, Move::amount>::board nextBoardState;
    constexpr static bool result= CheckWin<nextBoardState>::result;
};

#endif //HW_5_NOA_BARAK_RUSHHOUR_H