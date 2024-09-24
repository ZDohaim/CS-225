/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>
#include <deque>

using namespace std;

template <int Dim>
bool smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim)
{
 
  if (first[curDim] < second[curDim]){
    return true;
  } else if( first[curDim] > second[curDim]){
    return false;
    //using operator <
  }  else if(first < second){
    return true;
  }
return false;
}

template <int Dim>
bool shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential)
{
// int diff1 =0;
// int diff2 =0;
    double diff1 = 0.0;
    double diff2 = 0.0;
  for (int i = 0 ; i < Dim;  i++){
  diff1 += (target[i] - potential[i])*(target[i]- potential[i]);
  diff2 += (target[i] - currentBest[i])*(target[i] - currentBest[i]);
  }


  if (diff1 < diff2){
     return true;
    
  }else if(diff1 > diff2){
  return false;
} else {
  // return false;
   return (potential < currentBest);
}
}


template <int Dim>
KDTree<Dim>::KDTree(const std::vector<Point<Dim>>& newPoints) {
    // cout << newPoints.size() << endl;
    //  std::vector<Point<Dim>> points = newPoints; 
    //  cout << points.size() << endl;
    // if (!newPoints.empty()) {
    //    root = nullptr; 
    //   //  points = newPoints;
    //    KDBuild(root, points, 0, points.size() - 1, 0);    
    //   // KDBuild(root, 0, points.size() - 1, 0);    
    // }

  std::vector<Point<Dim>> points = newPoints; 
    if (points.empty()){


      return;
    }
    root = NULL;

    KDBuild(root, points, 0, points.size() - 1, 0);    
}

template <int Dim>
typename  KDTree<Dim>::KDTreeNode* KDTree<Dim>::KDBuild(KDTreeNode*& node, std::vector<Point<Dim>>& points, int left, int right, int curDim) {
if(left > right){
  return NULL;
}

int median = (left+right)/2;

if (left == right) {
        node = new KDTreeNode(points[median]);
        return node;
    }
    
// captures [something]
auto cmp = [&](const Point<Dim>& first, const Point<Dim>&second){ 
    return smallerDimVal(first, second, curDim);
};

select(points.begin() + left, points.begin() + right + 1, points.begin() + median, cmp);
                     
node = new KDTreeNode(points[median]);

int dimmension = (curDim+1) % Dim;

node->left = KDBuild(node->left, points, left, median-1, dimmension);
node->right = KDBuild(node->right, points, median + 1, right, dimmension);
return node;
}


// this also works, turns out my select was not working
// template <int Dim>
// void KDTree<Dim>::KDBuild(KDTreeNode*& node, int left, int right, int curDim){
// if(left > right){
//   node = NULL;
//   return;
// }

// int median = (left+right)/2;

// // captures [something], lambda functions:
// auto cmp = [&](const Point<Dim>& first, const Point<Dim>& second){
//     return smallerDimVal(first, second, curDim);
// };

// select(points.begin() + left, points.begin() + right + 1, points.begin() + median, cmp);
    
// node = new KDTreeNode(points[median]);
      
// int dimmension = (curDim+1) % Dim;
// KDBuild(node->left, left, median-1, dimmension);
// KDBuild(node->right, median + 1, right, dimmension);


// }

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) { 
//copy constructor,
//can't call constructor from another constructor.


root = NULL;
KDCopy(root, other.root);
}
template <int Dim>
void KDTree<Dim>::KDCopy(KDTreeNode *& original, KDTreeNode *& copy){
  //check if leaf node
  if (original == NULL){
      copy = NULL;
      return;
  }
copy = new KDTreeNode(original->point);
KDCopy(original->left, copy->left);
KDCopy(original->right, copy->right);
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
     if (this != &rhs) { 
        clear(root); 
        root = NULL;
        size = 0;
        copy(root, rhs.root);
    }
    return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
 KDClear(root);
 size = 0;
 points.clear();

}
template <int Dim>
void KDTree<Dim>::KDClear(KDTreeNode *root){
  if (root == NULL){return; }
  else{
    KDClear(root->right);
    KDClear(root->left);
    delete root;
    root = NULL;
  }
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const {
     return KDNeighbor(root, query, 0);
}

template <int Dim>
Point<Dim> KDTree<Dim>::KDNeighbor(KDTreeNode* node, const Point<Dim>& query, int curDim) const {
    if (node == nullptr) {
        return Point<Dim>();
    }
    // if (!node->left && !node->right)
    // return node;

    int dimmension = curDim % Dim;
     
     KDTreeNode* nextNode;
     KDTreeNode* oppositeNode;

    if(smallerDimVal(query, node->point, dimmension)){
       nextNode = node->left;
       oppositeNode = node->right;
    }else{
       nextNode  = node->right;
       oppositeNode = node->left;
    }
    //  if(nextNode!= NULL){
    //    oppositeNode = node->right;
    // }else{
    //    oppositeNode = node->left;
    // }
//  bool left = false;
   Point<Dim> bestNode = node->point;
    if (nextNode != nullptr) {
        Point<Dim> tempBest = KDNeighbor(nextNode, query, curDim + 1);
        if (shouldReplace(query, bestNode, tempBest)) {
          //left = true
            bestNode = tempBest;
        }
    }

    if (shouldReplace(query, bestNode, node->point)) {
        bestNode = node->point;
    }

    double bestDist = 0;
    for (int i = 0; i < Dim; i++) {
        bestDist += (bestNode[i] - query[i]) * (bestNode[i] - query[i]);
    }

    double dimDist = ((node->point[dimmension] - query[dimmension]) * (node->point[dimmension] - query[dimmension]));


    if (dimDist <= bestDist && oppositeNode != nullptr) {
        Point<Dim> potentialBest = KDNeighbor(oppositeNode, query, curDim + 1);
        if (shouldReplace(query, bestNode, potentialBest)) {
            bestNode = potentialBest;
        }
    }

    return bestNode;
}


// void select(RandIter start, RandIter end, RandIter k, Comparator cmp){
// if (start < end){
// RandIter pivot = start;

// //we swap to make it less work
// // swap (*pivot, *(end-1));

// RandIter Curr = start;
// for(RandIter it = start; it != end -1; it++){
//   // for(RandIter Curr = start; Curr != end -1; Curr++){

// if(cmp(*it, *(end-1))){
//   swap(*it, *Curr);
//   Curr++;
// }
// }

// //move back.
// swap(*Curr,*(end-1));

// if(k == Curr){
//   return;
// }else if(Curr > k ){
//   select(start,end-1,k,cmp);
// } else{
//   select(Curr,end,k,cmp);
// }
// }
// }


template <typename RandIter, typename Comparator>
void select(RandIter start, RandIter end, RandIter k, Comparator cmp){
  if (start >= end) {
        return; 
    }

    //CHANGE PIVOT TO END
    RandIter pivot = end - 1;

    RandIter left = start;
    for (RandIter it = start; it != pivot; ++it) {
        if (cmp(*it, *pivot)) {
            std::swap(*it, *left);
          ++left;
        }
    }

    std::swap(*left, *pivot);

    if (k == left) {
        return; 
    } else if (k < left) {
        select(start, left, k, cmp); 
    } else {
        select(left + 1, end, k, cmp); 
    }
}
