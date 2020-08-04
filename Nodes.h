#ifndef SEARCHALGORITHMS_NODES_H
#define SEARCHALGORITHMS_NODES_H

template<class State>
class Node {
private:
    State* state = nullptr;

public:
    Node(State* _state) { state = _state; }

    State* getState() { return state; }


};

template<class State>
class ParentNode : public Node<State> {
private:
    Node<State> **successors = nullptr;

public:
    ParentNode(State _state) : Node<State>(_state) {}

    Node<State> **getSuccessors() {
        return successors;
    }

    void setSuccessors(Node<State> **_successors) {
        successors = _successors;
    }

};

template<class State>
class ValuedNode : public Node<State> {
private:
    double value = 0;

public:
    ValuedNode(State _state) : Node<State>(_state) {}

    Node<State> **getValue() {
        return value;
    }

    void setValues(double _value) {
        value = _value;
    }

};


template<class State>
class TreeNode : public ParentNode<State> {


private:
    TreeNode<State> *parent = nullptr;
    double cost = 0;




public:
    TreeNode(TreeNode<State> *_parent, State _state, double _cost=0) : ParentNode<State>(_state) {
        parent = _parent;
        cost = _cost;
    }

    TreeNode<State> *getParent() {
        return parent;
    }

    void setParent(TreeNode<State> *_parent) {
        parent = _parent;
    }

    double getCost(){ return cost;}

    void setCost(double _cost){ cost = _cost;}

};



template<class State>
class GraphNode : public ParentNode<State> {
private:
    Node<State> **parents = nullptr;

public:
    GraphNode(Node<State> **_parents, State _state) : Node<State>(_state) {
        parents = _parents;
    }

    Node<State> *getParentS() {
        return parents;
    }

    void setParentS(Node<State> **_parents) {
        parents = _parents;
    }
};

#endif