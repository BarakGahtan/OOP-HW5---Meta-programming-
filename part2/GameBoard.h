//
// Created by Barak Gahtan on 31/08/2019.
//

#ifndef HW_5_NOA_BARAK_GAMEBOARD_H
#define HW_5_NOA_BARAK_GAMEBOARD_H

#include "BoardCell.h"
#include "List.h"

template <typename>
struct GameBoard;

template <typename Board>
struct GameBoard{
	typedef Board gameBoard;
    constexpr static int length= Board::size;
	constexpr static int width= Board::head::size;
};

template <typename GB,int row,int col, typename type>
struct setCell{
	typedef typename GetAtIndex<row, typename GB::gameBoard>::value cellRow;  // get the specific "vector"
	typedef typename SetAtIndex<col,type,cellRow>::list changeRow;
	typedef typename SetAtIndex<row, changeRow,typename GB::gameBoard>::list board;
};

template <typename GB,int row,int col>
struct getCell{
	typedef typename GetAtIndex<row, typename GB::gameBoard>::value cellRow; // get the specific "vector"
	typedef typename GetAtIndex<col,cellRow>::value cell; // get the cell
};

#endif //HW_5_NOA_BARAK_GAMEBOARD_H
