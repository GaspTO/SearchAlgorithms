//
// Created by nizzel on 04/08/20.
//

#ifndef SEARCHALGORITHMS_DFS_H
#define SEARCHALGORITHMS_DFS_H

#include "Z_PathFinding.h"

template <class State, class HeapHandle>
class DFS: public Z_PathFinding<State, HeapHandle>{

protected:
    virtual void set_F_cost(TreeNode<State> _node) {
        _node.setCost(_node.getParent()->getCost()+1);
    }

public:
    DFS(SearchProblem<State> *_problem, State _initialState,
            Map<State,TreeNode<State>>* _tree, Priority_queue<TreeNode<State>,HeapHandle>* _open)
                      :Z_PathFinding<State,HeapHandle>(_problem,true,_initialState,_tree,_open){}
};



#endif //SEARCHALGORITHMS_DFS_H
