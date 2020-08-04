#ifndef SEARCHALGORITHMS_TREESEARCH_H
#define SEARCHALGORITHMS_TREESEARCH_H


#include "SearchProblem.h"
#include "Nodes.h"
#include <array>


template<class State>
class TreeSearch {
private:
    bool foundSolution = false;
    Node<State> *currentNode = nullptr;
    Node<State> *solutionNode = nullptr;
    SearchProblem<State> *problem = nullptr;
    bool testOnExpansion = false;


protected:
    virtual bool addNextGeneration(State) = 0;

    virtual Node<State> createNode(State state) = 0;

    virtual bool nextCurrentNode() = 0;

    virtual bool evaluate(Node<State> *subjectNode) {
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

    virtual Node<State> *getCurrentNode() {
        return currentNode;
    }

    virtual void setCurrentNode(Node<State> *newCurrentNode) {
        currentNode = newCurrentNode;
    }

    virtual Node<State> *getSolutionNode() {
        return solutionNode;
    }

    virtual void setSolutionNode(Node<State> *newSolutionNode) {
        solutionNode = newSolutionNode;
    }

    virtual SearchProblem<State> *getProblem() {
        return problem;
    }

    virtual bool getTestOnExpansion(){ return testOnExpansion;}

public:
    TreeSearch(SearchProblem<State> *_problem, bool _testOnExpansion) {
        problem = _problem;
        setCurrentNode(createNode(getProblem()->getInitialState()));
        testOnExpansion = _testOnExpansion;
    }

    virtual bool runAlgorithm() {
        while (true) {
            if (addNextGeneration()) {
                return (foundSolution = true);
            }
            if (!nextCurrentNode()) return (foundSolution = false);
            if (testOnExpansion) {
                if (evaluate(getCurrentNode().getState())) {
                    setSolutionNode(getCurrentNode());
                    return (foundSolution = true);
                }
            }
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
