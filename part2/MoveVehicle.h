//
// Created by Barak Gahtan on 31/08/2019.
//

#ifndef HW_5_NOA_BARAK_MOVEVEHICLE_H
#define HW_5_NOA_BARAK_MOVEVEHICLE_H

#include "GameBoard.h"
#include "Utilities.h"
#include "TransposeList.h"

template <CellType C,Direction D,int A>
struct Move{
    static_assert(C!=CellType::EMPTY,"Cell is EMPTY");
    constexpr static CellType type = C;
    constexpr static Direction direction = D;
    constexpr static int amount = A;
};

template <int Row,int Col,CellType CT,typename GB >
struct deltaToCarStart{
    typedef typename getCell<GB, Row, Col>::cell currentCell;
    constexpr static int delta = ConditionalInteger<CT == currentCell::type, 1 + deltaToCarStart<Row, Col - 1, CT, GB>::delta, -1>::value;
};

template <int Row,CellType CT,typename GB >
struct deltaToCarStart<Row, 0, CT, GB>{
    typedef typename getCell<GB, Row, 0>::cell currentCell;
    constexpr static int delta = ConditionalInteger< CT == currentCell::type, 0, -1>::value;
};

template <int Row, int Col, int Amount,typename GB>
struct moveRight {
    static_assert(Row >= 0 && Row < GB::length && Col >= 0 && Col < GB::width,"Row or Col out of bounds");
    typedef typename getCell<GB, Row, Col >::cell currentCell;
    typedef BoardCell<EMPTY,Direction::DOWN,0> newEmptyCell;
    constexpr static int carLength = currentCell::length;
    typedef GameBoard<typename setCell<GB, Row, Col, newEmptyCell>::board> changedBoard;
    typedef typename getCell<changedBoard,Row,Col+carLength>::cell nextCell;
    static_assert(nextCell::type==CellType::EMPTY,"ERROR! way is not clear");

    typedef GameBoard<typename setCell< changedBoard, Row, Col+carLength, currentCell>::board> completeChangeBoard;
    typedef typename moveRight<Row, Col+1, Amount-1,completeChangeBoard>::finalBoard finalBoard;
};

template <int Row, int Col,typename GB>
struct moveRight<Row, Col, 0, GB>{
    typedef GB finalBoard;
};

template <int Row, int Col, int Amount, typename GB>
struct moveLeft{
    static_assert(Row < GB::length, "coordinates invalid");
    static_assert(Col < GB::width, "coordinates invalid");
    static_assert(Row >= 0 && Col >= 0, "coordinates invalid");
    typedef typename getCell<GB, Row, Col>::cell currentCell;
    typedef BoardCell<EMPTY, Direction::DOWN, 0> newEmptyCell;
    constexpr static int carLength = currentCell::length;
    typedef GameBoard<typename setCell<GB, Row, Col, newEmptyCell>::board> changedBoard;
    typedef typename getCell<changedBoard, Row, Col-carLength>::cell nextCell;
    static_assert(nextCell::type==CellType::EMPTY,"ERROR! way is not clear");
    typedef GameBoard<typename setCell< changedBoard, Row, Col-carLength, currentCell>::board> completeChangeBoard;
    typedef typename moveLeft<Row, Col-1, Amount-1,completeChangeBoard>::finalBoard finalBoard;
};

template <int Row, int Col, typename GB>
struct moveLeft<Row, Col, 0, GB>{
    typedef GB finalBoard;
};

template <typename GameBoard,int Row,int Col,Direction D,int Amount>
struct MoveVehicle;

template <typename GameBoard,int Row,int Col,int Amount>
struct MoveVehicle<GameBoard, Row, Col,RIGHT,Amount>{
    static_assert(Row < GameBoard::length,"coordinates invalid");
    static_assert(Col < GameBoard::width,"coordinates invalid");
    static_assert(Row >= 0 && Col >= 0,"coordinates invalid");
    typedef typename getCell<GameBoard, Row, Col>::cell givenCell;
    constexpr static int CarLength = givenCell::length;
    constexpr static CellType type = givenCell::type;
    static_assert(type!=EMPTY,"the cell type is empty");
    static_assert(givenCell::direction == Direction::RIGHT || givenCell::direction == Direction::LEFT ,"direction invalid");
    constexpr static int newDelta = deltaToCarStart<Row, Col, type, GameBoard>::delta;
    constexpr static int changedPlace = Col - newDelta;
    typedef typename moveRight<Row, changedPlace, Amount, GameBoard>::finalBoard board;
};

template <typename GameBoard,int Row,int Col,int Amount>
struct MoveVehicle<GameBoard,Row,Col,LEFT,Amount>{
    static_assert(Row < GameBoard::length,"coordinates invalid");
    static_assert(Col < GameBoard::width,"coordinates invalid");
    static_assert(Row >= 0 && Col >= 0,"coordinates invalid");
    typedef typename getCell<GameBoard, Row, Col>::cell givenCell;
    constexpr static int CarLength = givenCell::length;
    constexpr static CellType type = givenCell::type;
    static_assert(type!=EMPTY,"the cell type is empty");
    static_assert(givenCell::direction == Direction::RIGHT || givenCell::direction == Direction::LEFT ,"direction invalid");
    constexpr static int newDelta = deltaToCarStart<Row, Col, type, GameBoard>::delta;
    constexpr static int newPlace= Col+CarLength-newDelta-1;
    typedef typename moveLeft<Row, newPlace, Amount, GameBoard>::finalBoard board;
};

template <typename GB,int Row,int Col,int Amount>
struct MoveVehicle<GB,Row,Col,UP,Amount>{
    static_assert(Row < GB::length,"coordinates invalid");
    static_assert(Col < GB::width,"coordinates invalid");
    static_assert(Row >= 0 && Col >= 0,"coordinates invalid");
    typedef typename getCell<GB, Row, Col>::cell givenCell;
    constexpr static int CarLength = givenCell::length;
    constexpr static CellType type = givenCell::type;
    static_assert(type!=EMPTY,"the cell type is empty");
    static_assert(givenCell::direction == Direction::UP || givenCell::direction == Direction::DOWN ,"direction invalid");

    typedef typename Transpose<typename GB::gameBoard>::matrix transposed;
    typedef GameBoard<transposed> transposedGameBoard;
    constexpr static int delta = deltaToCarStart<Col, Row, type, transposedGameBoard>::delta;
    constexpr static int newPlace= Row-delta+CarLength-1;
    typedef typename moveLeft<Col, newPlace, Amount,transposedGameBoard>::finalBoard transposedResult;
    typedef typename Transpose<typename transposedResult::gameBoard>::matrix alignBoard;
    typedef GameBoard<alignBoard> board;
};

template <typename GB,int Row,int Col,int Amount>
struct MoveVehicle<GB,Row,Col,DOWN,Amount>{
    static_assert(Row < GB::length,"coordinates invalid");
    static_assert(Col < GB::width,"coordinates invalid");
    static_assert(Row >= 0 && Col >= 0,"coordinates invalid");
    typedef typename getCell<GB, Row, Col>::cell givenCell;
    constexpr static int CarLength = givenCell::length;
    constexpr static CellType type = givenCell::type;
    static_assert(type!=EMPTY,"the cell type is empty");
    static_assert(givenCell::direction == Direction::UP || givenCell::direction == Direction::DOWN ,"direction invalid");

    typedef typename Transpose<typename GB::gameBoard>::matrix transposed;
    typedef GameBoard<transposed> transposedGameBoard;
    constexpr static int delta = deltaToCarStart<Col, Row, type, transposedGameBoard>::delta;
    constexpr static int newPlace= Row-delta;
    typedef typename moveRight<Col,newPlace,Amount,transposedGameBoard>::finalBoard transposedResult;
    typedef typename Transpose<typename transposedResult::gameBoard>::matrix alignBoard;
    typedef GameBoard<alignBoard> board;
};
#endif //HW_5_NOA_BARAK_MOVEVEHICLE_H
