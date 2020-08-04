//
// Created by nizzel on 01/08/20.
//

#ifndef SEARCHALGORITHMS_Z_PATHFINDING_H
#define SEARCHALGORITHMS_Z_PATHFINDING_H


#include "TreeSearch.h"
#include "Map.h"
#include "Nodes.h"
#include "Queue.h"
#include "UnorderedMap.h"

template <class State, class Handle>
class Z_PathFinding: public TreeSearch<State>{


private:
    class Node_wrapper{
    public:
        enum Status {
            open,
            closed,
        };
        TreeNode<State>* treenode;
        Status status;
        Handle* heapHandle; //only valid if it's on OPEN
        Node_wrapper(TreeNode<State>* tn, Status st, Handle* hc = nullptr){
            treenode = tn;
            status = st;
            heapHandle = hc;
        }

    };

    typename Node_wrapper::Status::closed closed_status;
    typename  Node_wrapper::Status::open open_status;

    Map<State,Node_wrapper>* tree = nullptr;
    Priority_queue<TreeNode<State>,Handle>* open = nullptr;



protected:
    virtual TreeNode<State>* createTreeNode(TreeNode<State> *_parent, State _state, double _cost) {
        return new TreeNode<State>(_parent,_state,_cost);
    }

    virtual bool updateNode(TreeNode<State>* node) = 0; //returns whether it changed

    virtual bool addNextGeneration(State) {
        for(State childState: Z_PathFinding::getProblem()->generateSuccessors(Z_PathFinding::getCurrentNode()->getState())) {
            Node_wrapper childWrapper = tree->search(childState);
            if (childWrapper == nullptr) {
                TreeNode<State> *newTreeNodeChild = createTreeNode(Z_PathFinding::getCurrentNode(),childState,estimate(childState));
                Handle *handle = open->insert(newTreeNodeChild);
                Node_wrapper node_wrapper(newTreeNodeChild, open_status, handle);
                tree->insert(childState, handle);
            } else {
                if (childWrapper.treenode->getCost() > estimate(childState)) {
                    TreeNode<State> *newTreeNodeChild = createTreeNode(Z_PathFinding::getCurrentNode(),childState,estimate(childState));
                    childWrapper.treenode = newTreeNodeChild;
                    if (childWrapper.status == open_status) {
                        open->decrease_key(childWrapper.heapHandle, newTreeNodeChild);
                    } else {
                        open->insert(createTreeNode(Z_PathFinding::getCurrentNode(),childState,estimate(childState)));
                        childWrapper.status = open_status;
                    }
                }

            }
        }
    }


public:
    Z_PathFinding(SearchProblem<State> *_problem, bool _testOnExpansion, Map<State,TreeNode<State>>* _tree, Priority_queue<TreeNode<State>,Handle>* _open)
    :TreeSearch<State>(_problem,_testOnExpansion){
        tree = _tree;
        open = _open;

    }





};



#endif //SEARCHALGORITHMS_Z_PATHFINDING_H
