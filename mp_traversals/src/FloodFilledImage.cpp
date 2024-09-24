#include "cs225/PNG.h"
#include <list>
#include <iostream>

#include "colorPicker/ColorPicker.h"
#include "ImageTraversal.h"

#include "Point.h"
#include "Animation.h"
#include "FloodFilledImage.h"

using namespace cs225;

/**
 * Constructs a new instance of a FloodFilledImage with a image `png`.
 * 
 * @param png The starting image of a FloodFilledImage
 */
FloodFilledImage::FloodFilledImage(const PNG & png) {
    
  /** @todo [Part 2] */
png_ = png;
}

/**
 * Adds a FloodFill operation to the FloodFillImage.  This function must store the operation,
 * which will be used by `animate`.
 * 
 * @param traversal ImageTraversal used for this FloodFill operation.
 * @param colorPicker ColorPicker used for this FloodFill operation.
 */
void FloodFilledImage::addFloodFill(Traversals::ImageTraversal & traversal, ColorPicker & colorPicker) {
  /** @todo [Part 2] */

  // traversal_ =  traversal;
  // ColorPicker_ = colorPicker;

  traversal_.push_back(&traversal);
  ColorPicker_.push_back(&colorPicker);
}

/**
 * Creates an Animation of frames from the FloodFill operations added to this object.
 * 
 * Each FloodFill operation added by `addFloodFill` is executed based on the order
 * the operation was added.  This is done by:
 * 1. Visiting pixels within the image based on the order provided by the ImageTraversal iterator and
 * 2. Updating each pixel to a new color based on the ColorPicker
 * 
 * While applying the FloodFill to the image, an Animation is created by saving the image
 * after every `frameInterval` pixels are filled.  To ensure a smooth Animation, the first
 * frame is always the starting image and the final frame is always the finished image.
 * 
 * (For example, if `frameInterval` is `4` the frames are:
 *   - The initial frame
 *   - Then after the 4th pixel has been filled
 *   - Then after the 8th pixel has been filled
 *   - ...
 *   - The final frame, after all pixels have been filed)
 * @param frameInterval how often to save frames of the animation
 */ 
Animation FloodFilledImage::animate(unsigned frameInterval) const {
  /** @todo [Part 2] */
 
//   frameInterval = 1;
//   unsigned pixelFilled = 0;
//   for(auto i=0; i < traversals.size(); i ++){
//     ImageTraversal * traversal = traversal_[i];
//     ColorPicker * ColorPickers = ColorPickers_[i];
//   }
Animation Drawing;
PNG Image = png_;

auto pixelFilled = 0; 
//frame is always the starting image 
Drawing.addFrame(Image);


  for (unsigned i = 0; i < traversal_.size(); i++) {
    for (auto it = (traversal_[i])->begin(); it != (traversal_[i])->end(); ++it) {
      if ((*it).x < Image.width() && (*it).y < Image.height()) {
        
      // from mp_stickers: HSLAPixel &stickerPixel = stickers[i]->getPixel(x, y);
      HSLAPixel &Pixel = Image.getPixel((*it).x, (*it).y);
      Pixel = ColorPicker_[i]->getColor((*it).x, (*it).y);
  //While applying the FloodFill to the image, an Animation is created by saving the image
  //4, 8, 12 ...
      if (++pixelFilled % frameInterval == 0) {
        Drawing.addFrame(Image);
      }
    }
   }
  }
  //and the final frame is always the finished image.
  Drawing.addFrame(Image);
  return Drawing;
}


