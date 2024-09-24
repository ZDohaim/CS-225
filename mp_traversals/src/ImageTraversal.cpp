#include <cmath>
#include <iterator>
#include <iostream>

#include "cs225/HSLAPixel.h"
#include "cs225/PNG.h"
#include "Point.h"

#include "ImageTraversal.h"

namespace Traversals {
  /**
  * Calculates a metric for the difference between two pixels, used to
  * calculate if a pixel is within a tolerance.
  *
  * @param p1 First pixel
  * @param p2 Second pixel
  * @return the difference between two HSLAPixels
  */
  double calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
    double h = fabs(p1.h - p2.h);
    double s = p1.s - p2.s;
    double l = p1.l - p2.l;

    // Handle the case where we found the bigger angle between two hues:
    if (h > 180) { h = 360 - h; }
    h /= 360;

    return sqrt((h*h) + (s*s) + (l*l));
  }
  
  /**
  * Adds a Point for the bfs traversal to visit at some point in the future.
  * @param work_list the deque storing a list of points to be processed
  * @param point the point to be added
  */
 //stack 
  void bfs_add(std::deque<Point> & work_list, const Point & point) {
    /** @todo [Part 1] */
    
    work_list.push_back(point);
  }

  /**
  * Adds a Point for the dfs traversal to visit at some point in the future.
  * @param work_list the deque storing a list of points to be processed
  * @param point the point to be added
  */

 //qeueu
  void dfs_add(std::deque<Point> & work_list, const Point & point) {
    /** @todo [Part 1] */

    work_list.push_back(point);
    
  }

  /**
  * Removes the current Point in the bfs traversal
  * @param work_list the deque storing a list of points to be processed
  */
  void bfs_pop(std::deque<Point> & work_list) {
    /** @todo [Part 1] */

    if  (!work_list.empty()){
    work_list.pop_front();
    }

  }

  /**
  * Removes the current Point in the dfs traversal
  * @param work_list the deque storing a list of points to be processed
  */
  void dfs_pop(std::deque<Point> & work_list) {
    /** @todo [Part 1] */

    if  (!work_list.empty()){
    work_list.pop_back();
    }

  }

  /**
   * Returns the current Point in the bfs traversal
   * @param work_list the deque storing a list of points to be processed
   * @return the current Point 
   */
  Point bfs_peek(std::deque<Point> & work_list) {
    /** @todo [Part 1] */
    return work_list.front();
  }

  /**
   * Returns the current Point in the dfs traversal
   * @param work_list the deque storing a list of points to be processed
   * @return the current Point 
   */
  Point dfs_peek(std::deque<Point> & work_list) {
    /** @todo [Part 1] */
    return work_list.back();
  }

  /**
  * Initializes a ImageTraversal on a given `png` image,
  * starting at `start`, and with a given `tolerance`.
  * @param png The image this traversal is going to traverse
  * @param start The start point of this traversal
  * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
  * it will not be included in this traversal
  * @param fns the set of functions describing a traversal's operation
  */
ImageTraversal::ImageTraversal(const PNG & png, const Point & start, double tolerance, TraversalFunctions fns) {  
    /** @todo [Part 1] */
  png_ = png;
  start_ = start;
  tolerance_ = tolerance;
  fns_ = fns;
  

  // visited_.resize(png_.height());
  visited_.resize(png_.width()); //row for each width
  for(unsigned int  i = 0 ; i < png_.width(); i++){
       visited_[i].resize(png_.height());//each col in row
    for(unsigned int  j =0; j < png_.height(); j++){
        visited_[i][j] = false;
      }
    }
// BeginIterator_ = ImageTraversal::Iterator(png_, start_, tolerance_, this);
  }

  /**
  * Returns an iterator for the traversal starting at the first point.
  */
  ImageTraversal::Iterator ImageTraversal::begin() {
    /** @todo [Part 1] */
    
// return  ImageTraversal::Iterator(png_, start_, tolerance_, *this);

  return ImageTraversal::Iterator(png_, start_, tolerance_, this);

  }

  /**
  * Returns an iterator for the traversal one past the end of the traversal.
  */
  ImageTraversal::Iterator ImageTraversal::end() {
    /** @todo [Part 1] */
    return ImageTraversal::Iterator();
  }

  /**
  * Default iterator constructor.
  */
  ImageTraversal::Iterator::Iterator() {
    /** @todo [Part 1] */
   isEnd = true;
  }
ImageTraversal::Iterator::Iterator(PNG  png, Point start, double tolerance, ImageTraversal* traversal){
  png_ = png;
  start_ = start;
  tolerance_ = tolerance;
  curr_ = start;
  isEnd = false;
  traversal_ = traversal;
  // visited_.resize(png_.height()*png_.width(),false);
visited_.resize(png_.width()); //row for each width
  for(unsigned int i = 0 ; i < png_.width(); i++){
       visited_[i].resize(png_.height(),false);//each col in row
    // for(int j =0; j < png_.height(); j++){
    //     visited_[i][j] = false;
    //   }
    }

}

// ImageTraversal::Iterator::Iterator(const PNG& png, const Point& start, double tolerance, ImageTraversal* traversal)
//   : png_(png),  tolerance_(tolerance),curr_(start), traversal_(traversal) {}

  /**
  * Iterator increment operator.
  *
  * Advances the traversal of the image.
  */
  ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
    /** @todo [Part 1] */


    // if(work_list_.empty() ){
    //   // isEnd = true;
    //   // curr_ = Point(-1,-1);
    //   // return *this;
    // }

    visited_[curr_.x][curr_.y]=true;
/*The pixel to the right, (x + 1),
  The pixel below, (y + 1), and
  The pixel to the left, (x - 1).
  The pixel above, (y - 1),*/
    

// if(!visited_[curr_.x][curr_.y]){
  
  Point right = Point(curr_.x +1, curr_.y);
  Point below = Point(curr_.x, curr_.y + 1);
  Point left = Point(curr_.x-1,curr_.y);
  Point above = Point(curr_.x, curr_.y-1);
  
  //right
  // if(!visited_[curr_.x +1][ curr_.y] && (curr_.x+1) >=0 && (curr_.x+1) < png_.width() && curr_.y >= 0 && curr_.y < png_.height());

  // traversal_->fns_.pop(work_list_);


//CHECK BOUNDS: 
  if(Check(right)){
  traversal_->fns_.add(work_list_,right);
  }
  if(Check(below)){
  traversal_->fns_.add(work_list_,below);
  }
  if(Check(left)){
  traversal_->fns_.add(work_list_,left);
  }
  if(Check(above)){
  traversal_->fns_.add(work_list_,above);
  }

//  }

//while(!(visited_[curr_.x][curr_.y]) &&  !work_list_.empty()){
//  
//}


//ITERATE THROUGH LIST:
while (!work_list_.empty()){
  Point next = traversal_->fns_.peek(work_list_);
  traversal_->fns_.pop(work_list_);

// curr_.(traversal_->fns_.pop(work_list_));
// }
// if(Check(next)){
//   curr_ = next;
//   return *this;
// }

//CHECK NEXT:
// if (!visited_[next.x][next.y]) {
if (!visited_[next.x][next.y] && calculateDelta(png_.getPixel(start_.x, start_.y), png_.getPixel(next.x, next.y)) < tolerance_){
            curr_ = next; 
            return *this; 
   }

}
//mark as visited
// visited_[curr_.x][curr_.y] = true;
isEnd = true;
return *this;

}

  
  bool ImageTraversal::Iterator::Check(const Point &point){

  //The point has already been visited (a traversal never visits the same point twice)
  //The pixel at the point is greater than or equal to a given tolerance away from the pixel at the starting point. 
  //The function ImageTraversal::calculateDelta is provided for you to calculate the difference between two pixels

  if((point.x) >=0 && (point.x) < png_.width() && point.y >= 0 && point.y < png_.height() && !visited_[point.x ][ point.y] 
  && ((calculateDelta(png_.getPixel(start_.x, start_.y),png_.getPixel(point.x, point.y))) < tolerance_)){
    return true;
  }
  return false;
  }    
  

  /**
  * Iterator accessor operator.
  *
  * Accesses the current Point in the ImageTraversal.
  */
  Point ImageTraversal::Iterator::operator*() {
    /** @todo [Part 1] */
    return curr_;
  }

  /**
  * Iterator inequality operator.
  *
  * Determines if two iterators are not equal.
  */
  bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
    /** @todo [Part 1] */
    
    // if(*this != other){
    //   return true;
    // }
  if (this->isEnd == other.isEnd){
    return false; }
    
    return true; 
   
  }

  /**
   * Iterator size function.
   *
   * @return size_t the size of the iterator work queue.
   */
  size_t ImageTraversal::Iterator::size() const {
    return work_list_.size();
  }

  /**
   * Iterator empty function.
   *
   * @return bool whether the iterator work queue is empty.
   */
  bool ImageTraversal::Iterator::empty() const {
    return work_list_.empty();
  }

} 