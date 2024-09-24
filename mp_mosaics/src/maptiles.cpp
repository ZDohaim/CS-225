/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>

#include "maptiles.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{


MosaicCanvas *mosaic = new MosaicCanvas(theSource.getRows(), theSource.getColumns()); 
   


std::map<Point<3>, TileImage*> colorMap;
vector<Point<3>> points;
for (auto &tile: theTiles){
    LUVAPixel color = tile.getAverageColor();
    Point<3> point = convertToXYZ(color);
    points.push_back(point);

    colorMap[point]=&tile;
}

KDTree<3> Tree(points);

for (int i =0 ; i < theSource.getRows(); i++){
    for (int j=0 ; j < theSource.getColumns(); j++){

         LUVAPixel region = theSource.getRegionColor(i,j);
        Point<3> convertRegion = convertToXYZ(region);
        Point <3> Nearest = Tree.findNearestNeighbor(convertRegion);

        TileImage* NearestNeighbor = colorMap[Nearest];

        mosaic->setTile(i,j,NearestNeighbor);
    }
}

return mosaic;
}

