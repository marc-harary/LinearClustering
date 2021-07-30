#include <iostream>
#include <cmath>
#include <memory>
#include <list>
#include <unordered_set>
#include <unordered_map>
#include <cstdint>
#include <pair>

#include "point.h"
#include "row.h"
#include "point.cpp"
#include "row.cpp"


std::pair<std::vector<Row>,float>
label(std::vector<Row> rows,
      std::list<Point> points,
      std::unordered_map<Row, float> memo,
      int nCols,
      float maxDist) {
    if (points.empty()) {
        return {rows, cost(rows)};
    }
    auto point = points.back();
    points.pop_back();
    std::vector<Row> bestRows;
    float bestCost, candCost;
    for (Row& row: rows) {
        if (rows.size == nCols || rows.tooFar(point, maxDist)) {
            continue;
        }
        row.add(point);
        auto res = label(rows, points, memo, nCols, maxDist);
        if ((candCost = std::get<1>(res)) < bestCost) {
            bestCost = candCost;
            bestRows = std::get<0>(res);
        }
    }
    return {rows, bestCost};
}


float cost(std::vector<Row> rows, std::unordered_map<Row, float> memo) {
    float res = 0;
    for (Row& row: rows) {
        res += memo.find(row) != memo.end() ? memo[row] : row.cost();
    }
    return res;
}    


// void labelRows(std::vector< std::shared_ptr<Row> >& preRows,
//                std::list< std::shared_ptr<Row> >& points,
//                int nCols,
//                float& preCost) {
//     if (points.empty()) {
//         return;
//     }
//     auto point = points.back();
//     points.pop_back();
//     float curCost, nextCost;
//     nextCost = INFINITY;
//     std::shared_ptr<std::vector<Row>>  nextRows;
//     auto curRows = std::make_shared<std::vector<Row>>(preRows->size());
//     for (int i = 0; i < preRows->size(); i++) {
//         if ((*preRows)[i].size == nCols || (*preRows)[i].tooFar(point, 6)) {
//             continue;
//         }
//         std::copy(curRows->begin(), curRows->end(), preRows->begin());
//         (*curRows)[i].add(point);
//         labelRows(curRows, points, nCols, curCost);
//         if (curCost < nextCost) {
//             curCost = nextCost;
//             nextRows = curRows;
//         }
//     }
//     preRows = nextRows;
//     preCost = nextCost;
// }
// 
// 
// std::vector< std::shared_ptr<Row> >
// labelRows(std::list<Point>& points, int nRows, int nCols) {
//     std::vector< std::shared_ptr<Row> > rows(nRows);
//     float cost = 0;
//     labelRows(rows, points, nCols, cost);
//     return rows;
// }


int main() {
    std::list< std::shared_ptr<Point> > points = {std::make_shared<Point>(-1, 7),
                                                   std::make_shared<Point>( 0, 7),
                                                   std::make_shared<Point>( 1, 7),
                                                   std::make_shared<Point>(-1, 2),
                                                   std::make_shared<Point>( 0, 2),
                                                   std::make_shared<Point>( 1, 2),
                                                   std::make_shared<Point>(-1,-1),
                                                   std::make_shared<Point>( 0,-1),
                                                   std::make_shared<Point>( 1,-1),
                                                   std::make_shared<Point>(-1,-5),
                                                   std::make_shared<Point>( 0,-5),
                                                   std::make_shared<Point>( 1,-5)};
    Row r1, r2; 
    r1.add(std::make_shared<Point>(1,2));
    r1.add(std::make_shared<Point>(3,4));
    r2.add(std::make_shared<Point>(5,6));
    std::unordered_set<Row> rows = {r1, r2};
    for (auto& row: rows) {
        std::cout << row << std::endl;
    }
}
