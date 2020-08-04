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

template <class State, class HeapHandle>
class Z_PathFinding: public TreeSearch<State, TreeNode<State>>{


private:
    class Node_wrapper{
    public:
        enum Status {
            open,
            closed,
        };
        TreeNode<State>* treenode;
        Status status;
        HeapHandle* heapHandle; //only valid if it's on OPEN
        Node_wrapper(TreeNode<State>* tn, Status st, HeapHandle* hc = nullptr){
            treenode = tn;
            status = st;
            heapHandle = hc;
        }

    };

    typename Node_wrapper::Status::closed closed_status;
    typename  Node_wrapper::Status::open open_status;

    Map<State,Node_wrapper>* tree = nullptr;
    Priority_queue<TreeNode<State>,HeapHandle>* open = nullptr;



protected:
    virtual TreeNode<State>* createNode(TreeNode<State> *_parent, State _state) {
        TreeNode<State>* node = new TreeNode<State*>(_parent,_state);
        set_F_cost(node);
        return node;
    }

    virtual void set_F_cost(TreeNode<State> _node) = 0;


    TreeNode<State>* nextCurrentNode() override {
        TreeNode<State>* nextToExpand = open->extract_min();
        tree->search(*nextToExpand->getState()).status = closed_status;


    }

    virtual bool addNextGeneration(State) {
        for(State childState: Z_PathFinding::getProblem()->generateSuccessors(Z_PathFinding::getCurrentNode()->getState())) {
            Node_wrapper childWrapper = tree->search(childState);
            if (childWrapper == nullptr) {
                TreeNode<State> *newTreeNodeChild = createTreeNode(Z_PathFinding::getCurrentNode(), childState);
                if(!Z_PathFinding::getTestOnExpansion()){
                    if(Z_PathFinding::evaluate(newTreeNodeChild)){
                        return true;
                    }
                }
                HeapHandle *handle = open->insert(newTreeNodeChild);
                Node_wrapper node_wrapper(newTreeNodeChild, open_status, handle);
                tree->insert(childState, handle);
            } else {
                if (childWrapper.treenode->getCost() > F_cost(childState)) {
                    TreeNode<State> *newTreeNodeChild = createTreeNode(Z_PathFinding::getCurrentNode(), childState);
                    childWrapper.treenode = newTreeNodeChild;
                    if (childWrapper.status == open_status) {
                        open->decrease_key(childWrapper.heapHandle, newTreeNodeChild);
                    } else {
                        open->insert(createTreeNode(Z_PathFinding::getCurrentNode(), childState, F_cost(childState)));
                        childWrapper.status = open_status;
                    }
                }

            }
        }
    }


public:
    Z_PathFinding(SearchProblem<State> *_problem, bool _testOnExpansion,
            State _initialState, Map<State,TreeNode<State>>* _tree, Priority_queue<TreeNode<State>,HeapHandle>* _open)
    :TreeSearch<State,TreeNode<State>>(_problem,_testOnExpansion){
        createNode(nullptr, _initialState, F_cost(_initialState));
        tree = _tree;
        open = _open;

    }





};



#endif //SEARCHALGORITHMS_Z_PATHFINDING_H
