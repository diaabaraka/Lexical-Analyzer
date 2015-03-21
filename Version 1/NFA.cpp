#include "NFA.h"
#include <fstream>
NFA::NFA()
{
    startState = NULL ;
    //ctor
}

string NFA :: parse(string expression){

// parse the expression to find its type(defintion or expression)
// the first part is always the name

        string name = "" , expression_0 = "";
        exprName = "";
        bool regularExpression = false , regularDefinition_0 = false , key_word = false;
        if(expression[0] == '{' || expression[0] == '['){
            // keyWords

            if(expression[0] == '{' ){
                key_word = true;
            }


            for(int i = 1 ; i < expression.size()-1 ; i++){

                if(expression[i] == '\\'){
                    continue;
                }
                else if(expression[i] == ' '){
                    if(expression_0.compare("") != 0){
                        if(key_word){
                            keyWords.insert(expression_0);
                        }
                        else {

                                punctuation.insert(expression_0);
                        }

                        expression_0 = "";


                    }
                }
                else {
                    expression_0.push_back(expression[i]);
                }

            }
             if(key_word){
                keyWords.insert(expression_0);
             }

            else punctuation.insert(expression_0);

            return "";

        }




        for(int i = 0 ; i < expression.size() ; i++){



            if(!regularDefinition_0 && !regularExpression && expression[i] == ':'){
                // regular expression
                regularExpression = true;
                regularDefinition = false;


            }
            else if(!regularDefinition_0 && !regularExpression &&expression[i] == '='){
                // regular definition
                regularDefinition = regularDefinition_0 = true;



            }
            else if(!regularDefinition_0 && !regularExpression && expression[i] != ' '){



                name += expression[i];
                exprName.push_back(expression[i]);

            }
            else{
                expression_0.push_back(expression[i]);
            }


        }


        expression_0 = postfix(expression_0);
        // now we have the postfix expression we want to parse it



        Eval(expression_0);
        return expression_0 ;


}

State* NFA:: Eval(string postFix){


    string operand = "";
    bool dash = false;
    string eps = "-1";
    stack< pair<State* , State*> > states;
    counter = 0;
    for(int i = 0 ; i < postFix.size() ; i++){

        if(postFix[i] == ' '){
            if(operand.compare("") != 0){
                // Not an empty operand then we shouldn't ignore

                if(regular_definition.find(operand) != regular_definition.end()){
                    // this operand is regualr definition
                    // retrive the starting node and create another states and use it
                    // in the new NFA graph
                    State* start = regular_definition[operand];

                    pair<State* , State*> p = cloneGraph(start);

                    states.push(p);




                }

                else{
                    // not a regular definition so we have to parse to get the component
                    // first state

                    if(dash){
                        dash = false;
                        char first = 'f' , sec = 'f';
                        for(int j = 0 ; j < operand.size() ; j++){
                            if(operand[j] == '-'){
                                dash = true;
                            }
                            else if(dash){
                                sec = (operand[j]);
                            }
                            else
                                first = (operand[j]);
                        }
                        dash = false;
                        // here we handle expression like A-Z
                        // we create start and end node with 26 edges between them
                        if(operand.size()==1){
                            first = sec = '-';
                        }
                        State* start = new State(counter++);
                        State* End = new State(counter++);

                        string tmp = "";
                        tmp.push_back(first);
                        start->addTransition(tmp , End);
                        inputSet.insert(tmp);

                        while(tmp[0] != sec){
                            tmp = "";
                            first = (char) first+1;
                            tmp.push_back(first);
                            inputSet.insert(tmp);
                            start->addTransition(tmp , End);


                        }


                     states.push(make_pair(start , End));


                    }

                    else{
                    State* start = new State(counter++);
                    State* End = start;
                    for(int i = 0 ; i < operand.size() ; i++){

                        State* tmp = new State(counter++);
                        string input = "";

                        // push this char in the input set
                        if(operand[i] == '`'){
                            input = "-1";
                        }
                        else{
                          input.push_back(operand[i]);
                          inputSet.insert(input);

                        }
                        End->addTransition(input , tmp);

                        // Not sure so check again this line
                        End = tmp;


                    }
                states.push(make_pair(start , End));
                    }


                }



            }
            operand = "";

        }


        else if(isOperator(postFix[i])){
            // handle the regula expression operation

            switch( postFix[i] ){

            case '*' :{
                pair<State* , State*> first = states.top();
                states.pop();

                first.first->addTransition(eps ,first.second);
                first.second->addTransition(eps ,first.first);
                states.push(first);

            }

                break;

            case '+' :{
                pair<State* , State*> first = states.top();
                states.pop();

                first.second->addTransition(eps ,first.first);
                states.push(first);


            }

                break;

            case '|' :{
                // get two elements from the stack and create new start and end
                // then connect the new start with the two old start and repeat with the new end

                pair<State* , State*> first = states.top();
                states.pop();
                pair<State* , State*> second = states.top();
                states.pop();
                 State* newStart = new State(counter++);
                 State* newEnd = new State(counter++);

                 newStart->addTransition(eps ,first.first);
                 newStart->addTransition(eps , second.first);

                 first.second->addTransition(eps , newEnd);
                 second.second->addTransition(eps , newEnd);

                 states.push(make_pair(newStart , newEnd));




            }

                break;

            case '$':{
                pair<State* , State*> first = states.top();
                states.pop();
                pair<State* , State*> second = states.top();
                states.pop();
                second.second->addTransition(eps ,first.first);
                states.push(make_pair(second.first , first.second));

            }


                break;

            default:
                break;

            }


        }
        else {
            if(postFix[i] == '-'){
                dash = true;
            }
            if(postFix[i] == '`' && special.front() != 'L'){


                operand.push_back(special.front());
                special.pop();
            }
            else
            operand.push_back(postFix[i]);
        }





    }

    pair<State* , State*> st = states.top();
    states.pop();

    st.second->setAccepting();
    BFS(st.first);
    if(regularDefinition){
        regular_definition[exprName] = st.first;
    }
    else{
        st.second->set_Type(exprName);
        regular_expression[exprName] = st.first;
    }
    return st.first;

}

pair<State* , State*> NFA:: cloneGraph(State* start){

    State* newState = new State(counter++);
    int endStateID = -1;
    set<int> found;
    map<int , State*> created;
    queue<State*> q;
    q.push(start);

    created[start->get_Id()] = newState;

    while(!q.empty()){

        State* tmp = q.front();
        q.pop();

        if(found.find(tmp->get_Id())!= found.end()){
            continue;
        }
        found.insert(tmp->get_Id());

        State* newTmp = created[tmp->get_Id()];

        if(tmp->isAccepting()){
            endStateID = tmp->get_Id();
        }

    multimap<string, State*>::iterator st;
    multimap<string,State*>transitions = tmp->getAllTransitions();

    for(st = transitions.begin(); st != transitions.end(); ++st){
      State* tmp1 = (st->second);
       State* newTmp_1 ;
      if(created.find(tmp1->get_Id()) == created.end()){
        // we have to create new state

        newTmp_1 = new State(counter++);
        created[tmp1->get_Id()] = newTmp_1;
      }
      else
        newTmp_1 = created[tmp1->get_Id()];

      string transition = (st->first);

      newTmp->addTransition(transition , newTmp_1);

      q.push(tmp1);

    }



    }







    return make_pair(newState , created[endStateID]);


}



void NFA:: BFS(State* start){

           set<int> found;
 ofstream myfile;
  myfile.open ("Drawing2.txt");

    queue<State*> q;

    q.push(start);


    while(!q.empty()){

        State* tmp = q.front();
        q.pop();

        if(found.find(tmp->get_Id())!= found.end()){
            continue;
        }
        found.insert(tmp->get_Id());
        myfile<<"Node :"<<tmp->get_Id() << endl;

        if(tmp->isAccepting()){
            myfile<<"Aceepting State ";
        }
        myfile<< "connected to :"<<endl;
    multimap<string, State*>::iterator st;
    multimap<string,State*>transitions = tmp->getAllTransitions();

    for(st = transitions.begin(); st != transitions.end(); ++st){
      State* tmp1 = (st->second);
      myfile<< tmp1->get_Id() <<"  ----  "<< st->first <<endl;
      q.push(tmp1);

    }
    myfile<< "<<<<<<<<<<<<<<<<<<<<\n";



    }




myfile.close();

}



string NFA:: postfix(string expression){

//Order of precedence is *or+or() (highest), then
//concatenation ($), then | (lowest).


    expression = addConcatenation(expression);
    string operand ="";
    string result = "";

    stack<char>operations;

    for(int i = 0 ; i < expression.size() ; i++){

        if(expression[i] == '|' ||expression[i] == '*' || expression[i] == '+'
           || expression[i] == '(' || expression[i] == ')' || expression[i] == '$'){

            result.append(operand+" ");
            operand = "";


            if(expression[i] == ')'){
                while(true){

                    if(operations.top() == '('){
                        operations.pop();
                        break;
                    }
                   result.push_back(operations.top());
                   result+=" ";
                    operations.pop();

                }

            }
            else{
                 while(operations.size() > 0 &&high_priority(expression[i] , operations.top())){

                    if(operations.top() == '('){
                        operations.pop();
                        continue;
                    }
                    result.push_back(operations.top());
                    result+=" ";

                    operations.pop();

            }

            operations.push(expression[i]);
            }




        }


        else if(expression[i] == ' '){
            continue;
        }
        else{
            operand += expression[i];
        }





    }


        result.append(operand +" ");
        while(!operations.empty()){
                if(operations.top() != '(' && operations.top() != ')'){
                    result.push_back(operations.top());
                    result += " ";
                }



            operations.pop();
        }

        return result;


}


string NFA:: AddEscape(string expr){


    while(!special.empty()){
        special.pop();
    }

    string result = "";
    bool slash = false;
    for(int i = 0 ; i < expr.size() ; i++){
        if(expr[i] == '\\'){
            // found escape char so
            slash = true;
        }
        else if(isChar(expr[i])){
            slash = false;

            if(expr[i] == 'L'){

                result.push_back('`');
                special.push(expr[i]);
            }
            else
            result.push_back(expr[i]);
        }
        else if(expr[i] == ' '){
                result.push_back(' ');
        }
        else if(slash){
            // here we found an operator so we need to replace it with specia char
            special.push(expr[i]);
            result.push_back('`');
            slash = false;
        }
        else{
            result.push_back(expr[i]);
        }




    }





    return result;


}


string NFA:: addConcatenation(string expr){

        string result = "";

        expr = AddEscape(expr);
        for(int i = 0 ; i < expr.size() ; i++){

            if(isOperator(expr[i]) || isChar(expr[i]) || expr[i] == '-'){

                result.push_back(expr[i]);
            }

            if(expr[i] == ' ' && i - 1 >= 0 && isChar(expr[i-1])){

                result += " ";

                for(int j = i+1 ; j < expr.size() ; j++){

                    if(expr[j] == ' '){
                        continue;
                    }

                    if(isOperator(expr[j]) || expr[j] == '-'){
                        i = j - 1;
                        break;
                    }
                    if(isChar(expr[j])){
                        result.push_back('$');
                        i = j - 1;
                        break;
                    }
                    if(expr[j] == '('){
                        result.push_back('$');
                        result.push_back('(');
                        i = j;
                        break;
                    }
                    if(expr[j] == ')'){
                        break;
                    }



                }

            }

            else if(expr[i] == '('){


                    if(i > 0 && isChar(expr[i-1])){
                        result.push_back('$');
                    }

                result.push_back('(');



            }
            else if(expr[i] == ')' || expr[i] == '*' || expr[i] == '+'){

                if(!isOperator(expr[i]))
                result.push_back(expr[i]);

                for(int j = i+1 ; j < expr.size() ; j++ ){

                    if(expr[j] == ' '){
                        continue;
                    }
                    if(isOperator(expr[j])){
                        i = j - 1;
                        break;
                    }
                    if(isChar(expr[j])){

                        result.push_back('$');
                        i = j - 1;
                        break;
                    }
                    if(expr[j] == '('){
                        result.push_back('$');
                        result.push_back('(');
                        i = j ;
                        break;
                    }


                }


            }


        }


        return result;


}


bool NFA:: isOperator(char x){

        if(x == '|' ||x == '*' || x == '+'
           || x == '$'){

           return true;

           }

        return false;

}

bool NFA:: isChar(char x){
        if((x >= 'a' && x <= 'z') ||
         (x >= 'A' && x <= 'Z') || x == '`'||(x >= '0' && x <= '9')||x == '>' ||
           x == '<' || x =='!' || x =='/'|| x == '.'){

            return true;

         }

    return false;
}

bool NFA:: high_priority(char first , char top){

    // * and + and ( priority = 10
    // $ priority = 5;
    // | priority = 1;
    int firstPriority = 0 , topPriority = 0;

   if(first == '*' || first == '+' || first == '(' || first == ')'){
        firstPriority = 10;

   }
   else if(first == '$'){
        firstPriority = 5;
   }
    else firstPriority = 1;


    if(top == '*' || top == '+' || top == '(' || top == ')'){
        topPriority = 10;

   }
   else if(top == '$'){
        topPriority = 5;
   }
    else topPriority = 1;

    if(top == '(' && first != ')'){
        return false;

    }
    if(top == ')' && first == ')'){
        return true;
    }
   return topPriority >= firstPriority;

}


State* NFA :: compine(){

    startState = new State(counter++);
    State* newEnd = new State(counter++);


     map<string, State*>::iterator iter;

        for (iter = regular_expression.begin(); iter != regular_expression.end(); ++iter) {

            startState->addTransition("-1" , iter->second);

        }



    return startState;

}
set<string> NFA:: getInputSet(){

    return inputSet;


}


