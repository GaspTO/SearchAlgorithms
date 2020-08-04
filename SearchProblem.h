#include <vector>



template <class State>
class SearchProblem{
    public:
        enum type {
            Optimization,
            Satisfaction,
            Hybrid     
        };

    private:
        State initialState = nullptr;
        std::vector<State> (*succGenerator)(State) = nullptr;
        type problemType;
        bool (*optimizationFunction)(State,State) = nullptr;
        bool (*satisfactionFunction)(State) = nullptr;

    public:
        
        SearchProblem(State _initialState, std::vector<State> (*_succGenerator)(State), bool (*comp)(State,State) ){
            initialState = _initialState;
            succGenerator = _succGenerator;
            problemType = Optimization;
            optimizationFunction = comp;          
        }

        SearchProblem(State _initialState, std::vector<State> (*_succGenerator)(State), bool (*test)(State) ){
            initialState = _initialState;
            succGenerator = _succGenerator;
            problemType = Satisfaction;
            satisfactionFunction = test;
        }

        SearchProblem(State _initialState, std::vector<State> (*_succGenerator)(State), bool (*comp)(State,State), bool (*test)(State) ){
            initialState = _initialState;
            succGenerator = _succGenerator;
            problemType = Hybrid;
            optimizationFunction = comp; 
            satisfactionFunction = test;
        }


        std::vector<State> generateSuccessors(State state){
            return (*succGenerator)(state);
        }
        
        State getInitialState(){
            return initialState;
        }

        void setInitialState(State _initialState){
            initialState = _initialState;
        }

        type getProblemType(){
            return problemType;
        }

        type getOptimizationFunction(){
            return optimizationFunction;
        }

        type getSatisfactionFunction(){
            return satisfactionFunction;
        }


        //TODO finish getters and setters

        

};

/*


class StopCondition{

};

class TimerStopCondition: public StopCondition {
    private:
        double time;

    public:
        TimerStopCondition(double _time){ 
            //TODO maybe have a method void begin() to set the timer when we want? maybe even
            time = _time;
        }

        bool stop(){
            //TODO
        }

};

class GoalNodeStopCondition<Node>: public StopCondition {
    public:
        GoalNodeStopCondition(){
            
        }

        bool stop(){
            //TODO return NODE == NODE
        }

};

*/