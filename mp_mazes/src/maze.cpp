#include "maze.h"
#include "dsets.h"
#include <cstdlib> 
#include <iostream>
#include <ctime>
#include <queue>
#include <algorithm>
#include <cmath>
#include "maze.h"

SquareMaze::SquareMaze(){
    width_ = 0;
    height_ = 0;
}

/**
     * This uses your representation of the maze to determine whether it is
     * possible to travel in the given direction from the square at
     * coordinates (x,y).
     *
     * For example, after makeMaze(2,2), the possible input coordinates will
     * be (0,0), (0,1), (1,0), and (1,1).
     *
     * - dir = 0 represents a rightward step (+1 to the x coordinate)
     * - dir = 1 represents a downward step (+1 to the y coordinate)
     * - dir = 2 represents a leftward step (-1 to the x coordinate)
     * - dir = 3 represents an upward step (-1 to the y coordinate)
     *
     * You can not step off of the maze or through a wall.
     *
     * This function will be very helpful in solving the maze. It will also
     * be used by the grading program to verify that your maze is a tree that
     * occupies the whole grid, and to verify your maze solution. So make
     * sure that this function works!
     *
     * @param x The x coordinate of the current cell
     * @param y The y coordinate of the current cell
     * @param dir The desired direction to move from the current cell
     * @return whether you can travel in the specified direction
     */
bool SquareMaze::canTravel(int x, int y, int dir) const {
    if (dir == 0) {  
        //0      .(x)     MAX
        //------------|
        if (x < width_ - 1 && !right_[x + y * width_]){return true;}
    } else if (dir == 1) {  
        //|MAX      
        //| . (y)
        //| 0 
        if (y < height_ - 1 && !down_[x + y * width_]){return true;}
    } else if (dir == 2) {  // Check left
        if (x > 0 && !right_[x - 1 + y * width_]){return true;}
    } else if (dir == 3) {  // Check up
        if (y > 0 && !down_[x + (y - 1) * width_]){ return true;}
    }
    return false;
}

    /**
     * Makes a new SquareMaze of the given height and width.
     *
     * If this object already represents a maze it will clear all the
     * existing data before doing so. You will start with a square grid (like
     * graph paper) with the specified height and width. You will select
     * random walls to delete without creating a cycle, until there are no
     * more walls that could be deleted without creating a cycle. Do not
     * delete walls on the perimeter of the grid.
     *
     * Hints: You only need to store 2 bits per square: the "down" and
     * "right" walls. The finished maze is always a tree of corridors.)
     *
     * @param width The width of the SquareMaze (number of cells)
     * @param height The height of the SquareMaze (number of cells)
     */
void SquareMaze::makeMaze(int width, int height) {
    width_ = width;
    height_ = height;
    right_.resize(width * height, true);  
    down_.resize(width * height, true);   
    set_.addelements(width * height);

    // Randomly join cells until all cells are in the same set
    while (set_.size(0) < width * height) {
        int x = rand() % width;
        int y = rand() % height;
        //    int x = i % width;
        //     int y = i / width;
        int index = x + y * width;

        //srand((time(NULL))); //some from POTD: seed random number makes it longer

        if (rand() % 2 == 0) { //this splits it up into 2 'cases' (if you had three then ... )
            //remove the right wall if
            if (x < width - 1 && right_[index] 
            && set_.find(index) != set_.find(index + 1)) {
                set_.setunion(index, index + 1);
                setWall(x, y, 0, false);
            }
        } else {
            //remove the down wall if
            if (y < height - 1 && down_[index]
            && set_.find(index) != set_.find(index + width)) {
                set_.setunion(index, index + width);
                setWall(x, y, 1, false);
            }
        }
    }
}
  /**
     * Sets whether or not the specified wall exists.
     *
     * This function should be fast (constant time). You can assume that in
     * grading we will not make your maze a non-tree and then call one of the
     * other member functions. setWall should not prevent cycles from
     * occurring, but should simply set a wall to be present or not present.
     * Our tests will call setWall to copy a specific maze into your
     * implementation.
     *
     * @param x The x coordinate of the current cell
     * @param y The y coordinate of the current cell
     * @param dir Either 0 (right) or 1 (down), which specifies which wall to
     * set (same as the encoding explained in canTravel). You only need to
     * support setting the bottom and right walls of every square in the grid.
     * @param exists true if setting the wall to exist, false otherwise
     */
void SquareMaze::setWall(int x, int y, int dir, bool exists){
   if (x < 0 || x >= width_ || y < 0 || y >= height_) {
        return;  
    }

    int index = x + y * width_;
    if (dir == 0 && x < width_ - 1) {  
        right_[index] = exists;
    } else if (dir == 1 && y < height_ - 1) {  
        down_[index] = exists;
    }
}



   /**
     * Solves this SquareMaze.
     *
     * For each square on the bottom row (maximum y coordinate), there is a
     * distance from the origin (i.e. the top-left cell), which is defined as
     * the length (measured as a number of steps) of the only path through
     * the maze from the origin to that square.
     *
     * Select the square in the bottom row with the largest distance from the
     * origin as the destination of the maze. solveMaze() returns the
     * winning path from the origin to the destination as a vector of
     * integers, where each integer represents the direction of a step, using
     * the same encoding as in canTravel().
     *
     * If multiple paths of maximum length exist, use the one with the
     * destination cell that has the smallest x value.
     *
     * Hint: this function should run in time linear in the number of cells
     * in the maze.
     *
     * @return a vector of directions taken to solve the maze
     */
std::vector<int> SquareMaze::solveMaze() {
    std::vector<int> visited(width_ * height_, -1);  //all unvisited 
    std::queue<int> traversal;
    int dimensions = width_ * height_;
    std::vector<int> distance(dimensions, 0);

    traversal.push(0);  
    visited[0] = 0;  

//check each cell
    while (!traversal.empty()) {
        int cur = traversal.front(); //gets index
        traversal.pop();
        int x = cur % width_;
        int y = cur / width_;

        // Check four directions (just use canTravel!!!!)
        /* [0] [1] [2]
           [3] [X] [5]
           [6] [7] [8] */
           std::vector<int> directions = {1, width_, -1, -width_};
        for (auto dir = 0; dir < 4; dir++) {
            // int neighborIdx = cur; // Start at current cell index
            int neighborIdx = cur + directions[dir];
            // if (dir == 0 && x < width_ - 1)  // Right
            //    {neighborIdx += 1;}
            // else if (dir == 1 && y < height_ - 1)  // Down
            //    { neighborIdx += width_;}
            // else if (dir == 2 && x > 0)  // Left
            //     {neighborIdx -= 1;}
            // else if (dir == 3 && y > 0)  // Up
            //     {neighborIdx -= width_;

            // if(canTravel(x,y,dir) && visited[neighborIdx] == -1 )
          
            //Check if the neighbor can be visited 
            if (neighborIdx >= 0 && neighborIdx < dimensions && canTravel(x, y, dir) && visited[neighborIdx] == -1) {
                traversal.push(neighborIdx);
                visited[neighborIdx] = cur;  // Record the path from current to neighbor
                distance[neighborIdx] = distance[cur]+1; //new distance 
            }
        }
    }
// Find the path to the furthest cell on the bottom row

 int max_distance = 0, destination = 0;
    for (int i = width_ * (height_ - 1); i <dimensions; i++) {
        if (distance[i] > max_distance) {
            max_distance = distance[i];
            destination = i;
        }
    }



    // Reconstruct the path from destination to start
     std::vector<int> output;
    int current = destination;
    while (current != 0) { // reconstruct until we reach the start
        int prev = visited[current];
        int diff = current - prev;

    /*  * - dir = 0 represents a rightward step (+1 to the x coordinate)
     * - dir = 1 represents a downward step (+1 to the y coordinate)
     * - dir = 2 represents a leftward step (-1 to the x coordinate)
     * - dir = 3 represents an upward step (-1 to the y coordinate)*/
     
        if (diff == 1) output.push_back(0);       // Right
        else if (diff == -1) output.push_back(2); // Left
        else if (diff == width_) output.push_back(1); // Down
        else if (diff == -width_) output.push_back(3); // Up
        current = prev;
    }


    std::vector<int> reversedOutput;
    for (int i = output.size() - 1; i >= 0; i--) {
        reversedOutput.push_back(output[i]);
    }
    return  reversedOutput;
}


    /**
     * Draws the maze without the solution.
     *
     * First, create a new PNG. Set the dimensions of the PNG to
     * (width*10+1,height*10+1). where height and width were the arguments to
     * makeMaze. Blacken the entire topmost row and leftmost column of
     * pixels, except the entrance (1,0) through (9,0).  For each square in
     * the maze, call its maze coordinates (x,y). If the right wall exists,
     * then blacken the pixels with coordinates ((x+1)*10,y*10+k) for k from
     * 0 to 10. If the bottom wall exists, then blacken the pixels with
     * coordinates (x*10+k, (y+1)*10) for k from 0 to 10.
     *
     * The resulting PNG will look like the sample image, except there will
     * be no exit from the maze and the red line will be missing.
     *
     * @return a PNG of the unsolved SquareMaze
     */

cs225::PNG* SquareMaze::drawMaze() const{
  
    cs225::PNG* maze = new cs225::PNG(width_ * 10 + 1, height_ * 10 + 1);

    // Set the entire topmost row and leftmost column to black except the entrance.
    for (int i = 0; i < width_ * 10 + 1; i++) {
        if (i > 9 || i < 1) {
            maze->getPixel(i, 0).l = 0;  // Top row after entrance.
        }
        
    }
        // if (i < height_ * 10 + 1) {
        //     maze->getPixel(0, i).l = 0;  // Entire left column.
       

       for (int i = 0; i < height_ * 10 + 1; i++) {
        maze->getPixel(0, i).l = 0;  //  entire left column.
    }

    // Iterate over each cell in the grid.
    for (int x = 0; x < width_; x++) {
        for (int y = 0; y < height_; y++) {
            int index = x + y * width_;
            // If the right wall exists, then blacken the pixels with coordinates ((x+1)*10,y*10+k)
     if (right_[index]) {
        for (int k = 0; k <= 10; k++) {
        maze->getPixel((x + 1) * 10, y * 10 + k).l = 0;  // Ensure this corresponds exactly to your wall data structure.
            }
        }
        //  drawing of bottom walls
    if (down_[index]) {
         for (int k = 0; k <= 10; k++) {
        maze->getPixel(x * 10 + k, (y + 1) * 10).l = 0;  // Ensure this matches your wall settings.
             }
        }
    }    
}
return maze;    
}
 /**
     * This function calls drawMaze, then solveMaze; it modifies the PNG
     * from drawMaze to show the solution vector and the exit.
     *
     * Start at pixel (5,5). Each direction in the solution vector
     * corresponds to a trail of 11 red pixels in the given direction. If the
     * first step is downward, color pixels (5,5) through (5,15) red. (Red is
     * 0,1,0.5,1 in HSLA). Then if the second step is right, color pixels (5,15)
     * through (15,15) red. Then if the third step is up, color pixels
     * (15,15) through (15,5) red. Continue in this manner until you get to
     * the end of the solution vector, so that your output looks analogous
     * the above picture.
     *
     * Make the exit by undoing the bottom wall of the destination square:
     * call the destination maze coordinates (x,y), and whiten the pixels
     * with coordinates (x*10+k, (y+1)*10) for k from 1 to 9.
     *
     * @return a PNG of the solved SquareMaze
     */
cs225::PNG* SquareMaze::drawMazeWithSolution() {

    cs225::PNG* new_png = drawMaze();
    std::vector<int> solution = solveMaze();

    cs225::HSLAPixel red(0, 1, 0.5, 1);  // Red color for the solution path

    int x = 5, y = 5;  //start pixel

    int mx = 0, my = 0; //maze coordinates

    for (unsigned int i = 0; i < solution.size(); i++) {
        //std::cout << "test x" << x << ", test y=" << y << std::endl;
        int direction = solution[i];
        int dx = 0, dy = 0; //pixel coordinates

        if (direction == 0) {  // Right
            dx = 1;
            mx++;
        } else if (direction == 1) {  // Down
            dy = 1;
            my++;
        } else if (direction == 2) {  // Left
            dx = -1;
            mx--;
        } else if (direction== 3) {  // Up
            dy = -1;
            my--;
        }
        // x += 10 * dx;
        //y += 10 * dy;
        
        // Apply red directions
        for (int j = 0; j <= 10; j++) {
            //std::cout << "test x" << x << ", test y=" << y << i << j <<  std::endl;
            int mazeX = x + j * dx;
            int mazeY = y + j * dy;
            new_png->getPixel(mazeX, mazeY) = red;
        }
        x += 10 * dx;
        y += 10 * dy;
    }

    int baseX = mx * 10;
    int baseY = my * 10 + 10;
    for (int k = 1; k <= 9; k++) {
        new_png->getPixel(baseX + k, baseY).l = 1; // Set to white
    }

    return new_png;
}
