#ifndef SEARCHALGORITHMS_TREESEARCH_H
#define SEARCHALGORITHMS_TREESEARCH_H


#include "SearchProblem.h"
#include <array>


template<class State, class Node>
class TreeSearch {
private:
    bool foundSolution = false;
    Node *initialNode = nullptr;
    Node *currentNode = nullptr;
    Node *solutionNode = nullptr;
    SearchProblem<State> *problem = nullptr;
    bool testOnExpansion = false;


protected:
    virtual bool addNextGeneration(State) = 0;

    virtual Node* nextCurrentNode() = 0;

    /*
     *  Returns true if the search is over.
     *  Modifies the solution node
     */
    virtual bool evaluate(Node *subjectNode) {
        //TODO optimization limit?
        if (getProblem().getType() == SearchProblem<State>::type::Satisfaction
            || getProblem().getType() == SearchProblem<State>::type::Hybrid) {
            if ((*getProblem().getSatisfactionFunction())(subjectNode)) {
                setSolutionNode(subjectNode);
                return true;
            }
        }

        if (getProblem().getType() == SearchProblem<State>::type::Optimization
            || getProblem().getType() == SearchProblem<State>::type::Hybrid) {
            if (getSolutionNode() == nullptr) setSolutionNode(subjectNode);
            else if ((*getProblem().getOptimizationFunction())(getSolutionNode(), subjectNode)) {
                setSolutionNode(subjectNode);
            }
        }
        return false;

    }

    virtual Node *getCurrentNode() {
        return currentNode;
    }

    virtual void setCurrentNode(Node *newCurrentNode) {
        currentNode = newCurrentNode;
    }

    virtual Node *getSolutionNode() {
        return solutionNode;
    }

    virtual void setSolutionNode(Node *newSolutionNode) {
        solutionNode = newSolutionNode;
    }

    virtual SearchProblem<State> *getProblem() {
        return problem;
    }

    virtual bool getTestOnExpansion(){
        return testOnExpansion;
    }

public:
    TreeSearch(SearchProblem<State> *_problem, bool _testOnExpansion, Node* _initialNode) {
        problem = _problem;
        initialNode = _initialNode;
        testOnExpansion = _testOnExpansion;
    }

    virtual bool runAlgorithm() {
        currentNode = nextCurrentNode();
        while (true) {
            if (addNextGeneration()) {
                return (foundSolution = true);
            }
            if (nextCurrentNode()==nullptr) return (foundSolution = false);
            if (testOnExpansion) {
                if (evaluate(getCurrentNode().getState())) {
                    setSolutionNode(getCurrentNode());
                    return (foundSolution = true);
                }
            }
            currentNode = nextCurrentNode();
        }
    }

    State getSolution() {
        if (foundSolution)
            return getSolutionNode()->getState();
        else
            throw "No solution found!";
    }

};


#endif
