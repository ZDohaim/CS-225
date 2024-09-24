#include <vector>
#include <array>
#include <iostream>
#include <algorithm>

#include <puzzle.h>
#include <queue>
#include <set>
#include <map>
#include <memory>
#include <cmath>
#include <unordered_set>


using namespace std;
  

    /**
    * Default constructor for the puzzle state. This should initialize the
    * puzzle to the solved state.
    */
    PuzzleState::PuzzleState(){
      state_ = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0};
        f=0, g=0, h=0, parent = NULL;
    }

    /**
    * Custom constructor for the puzzle state. Invalid inputs should initialize
    * the puzzle representing all zeros.
    * @param state The starting state of the puzzle. The first entry in the
    * array is the top left tile, then the remaining entries are in row-major
    * order. The following is a depiction of a puzzle where the value of each
    * tile represents its index in the array:
    * 0  1  2  3
    * 4  5  6  7
    * 8  9  10 11
    * 12 13 14 15
    */
    PuzzleState::PuzzleState(const std::array<uint8_t, 16> state){
        
        state_ = state;
    }

    /**
    * Convert the puzzle state to an array.
    * @return an array representing the state of the puzzle in the same format
    * as described in the constructor.
    */
   std::array<uint8_t, 16>  PuzzleState::asArray() const{
        return state_;
    }

    /**
    * Overloaded operator== for the puzzle state. Puzzles are equal when the
    * value of each tile is the same.
    * @param rhs The puzzle state to compare to
    */
    bool PuzzleState::operator==(const PuzzleState &rhs) const{

        return state_ == rhs.state_;

    }

    /**
    * Overloaded operator!= for the puzzle state.
    * @param rhs The puzzle state to compare to
    */
    bool PuzzleState::operator!=(const PuzzleState &rhs) const{

            return state_ != rhs.state_;
    }

    /**
    * Overloaded operator< for the puzzle state. The PuzzleState with the first
    * tile value less than the corresponding tile in the other PuzzleState is
    * considered less.
    * @param rhs The puzzle state to compare to
    */
    bool PuzzleState::operator<(const PuzzleState &rhs) const{
            return state_ < rhs.state_;
    }

    /**
    * Get the neighbor specified by the direction. If the direction refers to an
    * invalid neighbor, return PuzzleState representing all zeros.
    * @param direction The direction to move a tile (e.x. UP means the empty
    * space should move down).
   
   
    *   0  1  2  3
    *   4  5  6  7
    *   8  9  10 11
    *   12 13 14 15
    */ 

   
//   PuzzleState PuzzleState::getNeighbor(Direction direction) const{

//         int zeroIndex = std::find(state_.begin(), state_.end(), 0) - state_.begin(); //find -- returns iterator pointing to first element in range. that's why you subtract 
//         int newIndex = zeroIndex;
//         // int row = zeroIndex / 4; // row major order
//         // int col = zeroIndex % 4; 
        
//     // if(newRow >= 0 && newRow < 4 && newCol >= 0 && newCol < 4){
//     //     PuzzleState neighbor(*this);
//     //     int newIndex = (newRow*4) + newCol; //row major order
//     //     swap(neighbor.state_[zeroIndex], neighbor.state_[newIndex]);
//     //     return neighbor;
//     // } 
// std::array<uint8_t, 16> allZeros{};
// return PuzzleState(allZeros);
       


// }
PuzzleState PuzzleState::getNeighbor(Direction direction) const{
    auto zeroIndex = std::find(state_.begin(), state_.end(), 0) - state_.begin();


    std::array<uint8_t, 16> copy = state_;

    if (direction == Direction::UP && zeroIndex < 12){
        std::swap(copy[zeroIndex], copy[zeroIndex+4]);
    }
    else if (direction == Direction::DOWN && zeroIndex > 3){
        std::swap(copy[zeroIndex], copy[zeroIndex-4]);
    }
    else if (direction == Direction::LEFT && zeroIndex%4 != 3){
        std::swap(copy[zeroIndex], copy[zeroIndex+1]);
    }
    else if (direction == Direction::RIGHT && zeroIndex%4 != 0){
        std::swap(copy[zeroIndex], copy[zeroIndex-1]);
    }
    else{
        return PuzzleState();
    }
    
    return PuzzleState(copy);
}
  


    /**
    * Gets all possible PuzzleStates that result from a single move.
    * @return All possible next PuzzleStates in any order
    */
    std::vector<PuzzleState> PuzzleState::getNeighbors() const{
        int zeroIndex = std::find(state_.begin(), state_.end(), 0) - state_.begin(); //find -- returns iterator pointing to first element in range. that's why you subtract 
        int row = zeroIndex / 4; // row major order
        int col = zeroIndex % 4; 
        std::vector <PuzzleState> neighbors;

        if(row>0){
            addNeighbor(neighbors, zeroIndex, zeroIndex-4); //same as Direction::UP
        } if(row <3){
             addNeighbor(neighbors, zeroIndex, zeroIndex+4); //checks down
        } if(col > 0) {
             addNeighbor(neighbors, zeroIndex, zeroIndex-1); //checks left
        } if(col <3 ){
            addNeighbor(neighbors, zeroIndex, zeroIndex+1); // right
        }

return neighbors;
    } 

//helper function to add neighbors given index
void PuzzleState::addNeighbor(std::vector<PuzzleState>& neighbors, int zeroIndex, int swapIndex ) const{
     PuzzleState neighbor(*this);
        // int newIndex = newRow * 4 + newCol;
        swap(neighbor.state_[zeroIndex], neighbor.state_[swapIndex]);
        neighbors.push_back(neighbor);
}



    /**
    * Calculates the "manhattan distance" between the current state and the goal
    * state. This is the sum of the manhattan distances of each tile's current
    * location to its goal location.
    * @param desiredState The state to calculate the distance to
    * @return The manhattan distance between the current and goal states
    */

int PuzzleState::manhattanDistance(const PuzzleState desiredState) const {
    int manDistance = 0 ; 

    for (auto i = 0 ; i < 16; i++){
        auto tile = state_[i];
        if(tile != 0){

            int currRow = i/4;
            int currCol = i %4;

            int idx = std::find(desiredState.state_.begin(),desiredState.state_.end(), tile) - desiredState.state_.begin();
            int targetRow = idx / 4;
            int targetCol = idx % 4;

            manDistance += std::abs(currRow - targetRow) + std::abs(currCol - targetCol);
        }
    }

    return manDistance;
 }



/**
* Solves the puzzle using A* with manhattan distance as a heuristic.
* @param startState The starting state of the puzzle
* @param desiredState The final goal state of the puzzle after solving
* @param iterations The number of iterations it took to solve the puzzle. An
* iteration is defined as the number of times a state is popped from the data
* structure (NOTE: this should include the start and desired states, but not any
* states that are immediately discarded, if applicable). We will use the value
* stored at this pointer to evaluate efficiency. Ignore if NULL.
* @return The path to the solution. The first element of the vector is the start
* state, and the last element is the desired state. Empty if no solution exists.
*/
struct StateCost {
    int cost;
    PuzzleState* state;
};

//to use in priority queue
struct CompareState {
    bool operator()(const StateCost& lhs, const StateCost& rhs) {
        return lhs.cost > rhs.cost; // Min-heap based on cost
    }
};


std::vector<PuzzleState> solveAstar(const PuzzleState& startState, const PuzzleState& desiredState, size_t *iterations) {
    //1.  Initialize the open list
   std::priority_queue<StateCost, std::vector<StateCost>, CompareState> openList; //priority queue, using comparestate as comparator
    //2.  Initialize the closed list
    std::set<PuzzleState> closedList;
    std::map<PuzzleState, PuzzleState*> stateMap;  // Track all states for memory management

    PuzzleState* start = new PuzzleState(startState);
    start->g = 0;
    start->h = start->manhattanDistance(desiredState);
    start->f = start->g + start->h;
    start->parent = nullptr;

    
    openList.push({start->f, start});
    stateMap[startState] = start;

    size_t tempIter = 1;
    // 3. while the open list is not empty
    while (!openList.empty()) {
           //get top node's cost
        PuzzleState* current = openList.top().state;
        //pop q off the open list
        openList.pop();

        if (*current == desiredState) {
            //same as BFS
            std::vector<PuzzleState> path;
            while (current != nullptr) {
                path.push_back(*current);
                current = current->parent;
            }
            std::reverse(path.begin(), path.end());

                for (auto it = stateMap.begin(); it != stateMap.end(); ++it) {
                PuzzleState* statePointer = it->second;  
                delete statePointer;  
                }
                if(iterations){
            *iterations = tempIter;
                }           
            return path;
        }

        closedList.insert(*current);    

         //for each neighbor  
       
        for (size_t i = 0; i < (current->getNeighbors()).size(); ++i) {
            auto neighbor = (current->getNeighbors())[i];

            //if neighbor is in the goal, stop search
            if (closedList.find(neighbor) != closedList.end()){
                continue;
            } 
            //get cost
            int tempG = (current->g) + 1; 
            bool betterState = false;
            /*else, compute both g and h for neighbor  neighbor.g = q.g + distance between neighbor and q neighbor.h = distance from goal to   neighbor 
        
          neighbor.f = neighbor.g + neighbor.h*/
            PuzzleState* neighborState = nullptr;
            //initial handling
            if (stateMap.count(neighbor) == 0) {

                neighborState = new PuzzleState(neighbor);
                stateMap[neighbor] = neighborState;
                neighborState->h = neighbor.manhattanDistance(desiredState);
                betterState = true;  // New state, better

            } else {
                /*if a node with the same position as 
                neighbor is in the OPEN list which has a 
                lower f than neighbor, skip this neighbor*/
                neighborState = stateMap[neighbor];
                betterState = (tempG < neighborState->g);  // Existing state, check if this new path is better
            }

            /*(if a node with the same position as neighbor  is in the CLOSED list which hasa lower f than neighbor, skip this neighbor
            otherwise, add  the node to the open list  end (for loop))*/

            if (betterState == true) {
                neighborState->parent = current;
                neighborState->g = tempG;
                neighborState->f = neighborState->g + neighborState->h;
                //push q on the closed list
                openList.push({neighborState->f, neighborState});
            }
        }
        //increment iterator
        tempIter++;
    }
    for (auto it = stateMap.begin(); it != stateMap.end(); ++it) {
    PuzzleState* statePointer = it->second;  
    delete statePointer;  
}
    stateMap.clear();

    if(iterations){
    *iterations = tempIter; 
    }
    return {};
}




/**
* Solves the puzzle using BFS.
* @param startState The starting state of the puzzle
* @param desiredState The final goal state of the puzzle after solving
* @param iterations The number of iterations it took to solve the puzzle. An
* iteration is defined as the number of times a state is popped from the data
* structure (NOTE: this should include the start and desired states, but not any
* states that are immediately discarded, if applicable). We will use the value
* stored at this pointer to evaluate efficiency. Ignore if NULL.
* @return The path to the solution. The first element of the vector is the start
* state, and the last element is the desired state. Empty if no solution exists.
*/

std::vector<PuzzleState> solveBFS(const PuzzleState &startState, const PuzzleState &desiredState, size_t *iterations){
std::queue<PuzzleState> q; 
    std::set<PuzzleState> visited;
    // std::vector<PuzzleState>visisted;
std::map<PuzzleState, PuzzleState> predecessor;
PuzzleState currentState;
    if(iterations){
    *iterations = 0;
    }
    q.push(startState);
    visited.insert(startState);
 
     while(!q.empty()){
        if(iterations){
       (*iterations)++; 
        }
         currentState = q.front();
         q.pop();
       

         if(currentState == desiredState){
            // iterations++;
            break;
       }
       
  std::vector<PuzzleState> neighbors = currentState.getNeighbors();
        for (unsigned long i = 0; i < neighbors.size(); i++) {
             PuzzleState position = neighbors[i];
            if (visited.find(position) == visited.end()) {
            visited.insert(position);    
            q.push(position);
            predecessor[position] = currentState;
        }
     }
}

//not needed but leave incase: 
      if(currentState != desiredState ){
        std::vector<PuzzleState> empty;
        return empty;
    }


  if (visited.find(desiredState) == visited.end()) { //if desired not reached
        return {};   //empty
    }

std::vector<PuzzleState> path;
PuzzleState state = desiredState;  

while (state != startState) {  
    path.push_back(state);     
    state = predecessor[state];  //work your way backwards 
}

    path.push_back(startState);
    std::reverse(path.begin(), path.end());
    return path;
}

