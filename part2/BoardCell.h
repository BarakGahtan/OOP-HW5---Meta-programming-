//
// Created by Barak Gahtan on 31/08/2019.
//

#ifndef HW_5_NOA_BARAK_BOARDCELL_H
#define HW_5_NOA_BARAK_BOARDCELL_H

#include "CellType.h"
#include "Direction.h"

template <CellType cellType,Direction dir,int carLength>
struct BoardCell{
    constexpr static Direction direction = dir;
    constexpr static int length = carLength;
	constexpr static CellType type = cellType;
};
#endif //HW_5_NOA_BARAK_BOARDCELL_H
