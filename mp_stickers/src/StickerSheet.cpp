
  /**
   * Add any constructors/destructors you may need based on your
   * class design for StickerSheet.
   */
#include "Image.h"
#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "StickerSheet.h"
#include <climits>
#include <cstdlib>
using namespace cs225;
using namespace std;


  /**
   * Initializes this StickerSheet with a deep copy of the base picture.
   *
   * @param picture The base picture to use in the StickerSheet
   */

StickerSheet::StickerSheet(const Image& picture){
    Base = Image(picture.width(),picture.height());
    for(unsigned int w = 0; w < Base.width(); w++){
        for(unsigned int h = 0; h <  Base.height(); h++){
            HSLAPixel& basePixel = Base.getPixel(w,h);
            const HSLAPixel& copyPixel = picture.getPixel(w,h);
            basePixel.a = copyPixel.a;
            basePixel.h = copyPixel.h;
            basePixel.l = copyPixel.l;
            basePixel.s = copyPixel.s;            
        }
    }
}


  /**
   * Adds a `sticker` to the StickerSheet, so that the top-left of the sticker's
   * `Image` is at `(x, y)` on the StickerSheet.
   *
   * The sticker must be added to the lowest possible layer available.
   *
   * If all available layers have been filled, a new layer must be added above
   * all existing layers.
   *
   * @param sticker The Image of the sticker.
   * @param x The x location of the sticker on the StickerSheet
   * @param y The y location of the sticker on the StickerSheet
   *
   * @return The zero-based layer index the sticker was added to.
   */
  int StickerSheet::addSticker(Image& sticker, int x, int y){
    unsigned int i = 0;
     while (i < stickers.size()){
        if(stickers[i] == nullptr){
            
            stickers[i] =(&sticker); 
            xPositions[i] = x;
            yPositions[i] = y; 
            return i; 
        }
        i++;
    }

    if (i == stickers.size()) {
        stickers.push_back(&sticker); 
        xPositions.push_back(x); 
        yPositions.push_back(y); 
        return i; 
    }
    return i;
  }

  
  /**
   * Adds a `sticker` to the StickerSheet at layer `layer`, so that the top-left
   * of the sticker's `Image` is at `(x, y)` on the StickerSheet. If there is already
   * a sticker at `layer` it should be replaced and if `layer` is beyond the top of the
   * existing layers, add a new layer on top.
   *
   * @param sticker The Image of the sticker.
   * @param layer The layer where the sticker is to be placed.
   * @param x The x location of the sticker on the StickerSheet
   * @param y The y location of the sticker on the StickerSheet
   *
   * @return The zero-based layer index the sticker was added to.
   */
int StickerSheet::setStickerAtLayer(Image& sticker, unsigned int layer, int x, int y) {
    Image *baseImage = &sticker;
    if (layer < stickers.size()) {
        stickers[layer] = baseImage;
        xPositions[layer] = x;
        yPositions[layer] = y;
    } else {
        stickers.push_back(baseImage);
        xPositions.push_back(x);
        yPositions.push_back(y);
    }

    unsigned int size = stickers.size() - 1;
    unsigned int minLayer = std::min(layer, size);
    return static_cast<int>(minLayer); // Assuming you need to return an int
}


  /**
   * Changes the x and y coordinates of the Image in the specified layer.
   *
   * If the layer is invalid or does not contain a sticker, this function
   * must return false. Otherwise, this function returns true.
   *
   * @param index Zero-based layer index of the sticker.
   * @param x The new x location of the sticker on the StickerSheet
   * @param y The new y location of the sticker on the StickerSheet
   *
   * @return `true` if the translate was successful; otherwise `false`.
   */
  bool StickerSheet::translate(unsigned index, int x, int y){

    if (index >= 0 && index < stickers.size()){
    xPositions[index]=x;
    yPositions[index]=y;
    return true;
    } else {
        return false;
    }

  }

  /**
   * Removes the sticker at the given zero-based layer index. Make sure that the
   * other stickers don't change order.
   *
   * @param index The layer in which to delete the png
   */
 void StickerSheet::removeSticker(unsigned index){

  //    if (index < stickers.size()) {
    //     // Swap with the last element (if not already the last)
    //     if (index != stickers.size() - 1) {
    //         std::swap(stickers[index], stickers.back());
    //         std::swap(xPositions[index], xPositions.back());
    //         std::swap(yPositions[index], yPositions.back());
    //     }
    //     // Now remove the last element
    //     stickers.pop_back();
    //     xPositions.pop_back();
    //     yPositions.pop_back();
    // }

 if(index < stickers.size()) {
    xPositions.erase(xPositions.begin()+index);
    yPositions.erase(yPositions.begin()+index);
    stickers.erase(stickers.begin()+index);
    }

  
}


  /**
   * Returns a pointer to the sticker at the specified index,
   * not a copy of it. That way, the user can modify the Image.
   *
   * If the index is invalid, return NULL.
   *
   * @param index The layer in which to get the sticker.
   *
   * @return A pointer to a specific Image in the StickerSheet
   */
  Image* StickerSheet::getSticker(unsigned index){
   if (index >= 0 && index < stickers.size()){
        return stickers[index];
    } else{ 
     return nullptr;
  }
  return nullptr;
}
  /**
   * Returns the total number of layers available on the Stickersheet.
   *
   * @return The total number of layers
   */
  int StickerSheet::layers() const{
    int layerCounter = 0;
    for( unsigned int i = 0 ; i < stickers.size(); i++){
        if (stickers[i] != nullptr){
            layerCounter++;
        }
    }
    return layerCounter;
  }

  /**
   * Renders the whole StickerSheet on one Image and returns that Image.
   *
   * The base picture is drawn first and then each sticker is drawn in order
   * starting with layer zero (0), then layer one (1), and so on.
   *
   * If a pixel's alpha channel in a sticker is zero (0), no pixel is drawn
   * for that sticker at that pixel. If the alpha channel is non-zero, a
   * pixel is drawn. (Alpha blending is awesome, but not required.)
   *
   * The returned image always includes the full contents of the picture and
   * all stickers. It should expand in each corresponding direction if
   * stickers go beyond the edge of the picture.
   *
   * @return An Image object representing the drawn scene
   */


 Image StickerSheet::render() const {
    unzsigned int newWidth = Base.width();
    unsigned int newHeight = Base.height();
    int widthDiff = 0; 
    int heightDiff = 0; 

    for (unsigned int i = 0; i < stickers.size(); i++) {
        if (stickers[i] != nullptr) { 
            int x = xPositions[i];
            int y = yPositions[i];
            unsigned int stickerWidth = stickers[i]->width();
            unsigned int stickerHeight = stickers[i]->height();

            widthDiff = std::min(widthDiff, x);
            heightDiff = std::min(heightDiff, y);

            newWidth = std::max(newWidth, static_cast<unsigned int>(std::max(0, x) + stickerWidth));
            newHeight = std::max(newHeight, static_cast<unsigned int>(std::max(0, y) + stickerHeight));
        }
    }

    int WidthOffset = std::abs(widthDiff);  
    int HeightOffset = std::abs(heightDiff);

    newWidth += WidthOffset;
    newHeight += HeightOffset;

    Image resultImage(newWidth, newHeight);

    for (unsigned int x = 0; x < Base.width(); ++x) {
        for (unsigned int y = 0; y < Base.height(); ++y) {
            HSLAPixel &destinationPixel = resultImage.getPixel(x - widthDiff, y - heightDiff);
            const HSLAPixel &sourcePixel = Base.getPixel(x, y);
            destinationPixel = sourcePixel;
        }
    }

    for (unsigned int i = 0; i < stickers.size(); i++) {
        if (stickers[i] == nullptr) continue;

        unsigned int startX = xPositions[i] - widthDiff;
        unsigned int startY = yPositions[i] - heightDiff;

        for (unsigned int x = 0; x < stickers[i]->width(); ++x) {
            for (unsigned int y = 0; y < stickers[i]->height(); ++y) {
                HSLAPixel &stickerPixel = stickers[i]->getPixel(x, y);

                if (stickerPixel.a != 0) {
                    resultImage.getPixel(startX + x, startY + y) = stickerPixel;
                }
            }
        }
    }

    return resultImage;
}





