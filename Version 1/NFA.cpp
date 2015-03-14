#include "NFA.h"

NFA::NFA()
{
    //ctor
}

string NFA :: parse(string expression){

// parse the expression to find its type(defintion or expression)
// the first part is always the name

        string name = "" , expression_0 = "";
        bool regularExpression = false , regularDefinition = false;
        for(int i = 0 ; i < expression.size() ; i++){



            if(expression[i] == ':'){
                // regular expression
                regularExpression = true;

            }
            else if(expression[i] == '='){
                // regular definition
                regularDefinition = true;


            }
            else if(!regularDefinition && !regularExpression){

                name += expression[i];

            }
            else{
                expression_0 += expression[i];
            }


        }


       // State start(counter++);
        // we will transforme the expression to postfix expression

        expression_0 = postfix(expression_0);
        // now we have the postfix expression we want to parse it




        return expression_0 ;


}

State NFA:: Eval(string postFix){

    string operand = "";

    stack< pair<State* , State*> > states;
    counter = 0;

    for(int i = 0 ; i < postFix.size() ; i++){

        if(postFix[i] == ' '){

            if(operand.compare(" ") != 0){
                // Not an empty operand then we shouldn't ignore

                if(regular_definition.find(operand) != regular_definition.end()){
                    // this operand is regualr definition
                    // retrive the starting node and create another states and use it
                    // in the new NFA graph



                }

                else{
                    // not a regular definition so we have to parse to get the component
                    // first state
                    State* start = new State(counter++);
                    State* End = start;
                    for(int i = 0 ; i < operand.size() ; i++){

                        State* tmp = new State(counter++);
                        string input = "";
                        input.push_back(operand[i]);
                        End->addTransition(input , tmp);

                        // Not sure so check again this line
                        End = tmp;


                    }
                states.push(make_pair(start , End));

                }



            }
            operand = "";

        }

    }





}



string NFA:: postfix(string expression){

//Order of precedence is *or+or() (highest), then
//concatenation ($), then | (lowest).


    expression = addConcatenation(expression);
    cout<< expression<<endl;
    string operand ="";
    string result = "";

    stack<char>operations;

    for(int i = 0 ; i < expression.size() ; i++){

        if(expression[i] == '|' ||expression[i] == '*' || expression[i] == '+'
           || expression[i] == '(' || expression[i] == ')' || expression[i] == '$'){
            cout<< operand<<endl;

            result.append(operand+" ");
            cout << result << endl;
            operand = "";


            if(expression[i] == ')'){
                cout<< expression[i]<<endl;
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


             //cout<< operations.top()<<endl;


        }

        else if(expression[i] == '\\'){


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


string NFA:: addConcatenation(string expr){

        string result = "";


        for(int i = 0 ; i < expr.size() ; i++){

            if(isOperator(expr[i]) || isChar(expr[i])){

                result.push_back(expr[i]);
            }

            if(expr[i] == ' ' && i - 1 >= 0 && isChar(expr[i-1])){

                result += " ";

                for(int j = i+1 ; j < expr.size() ; j++){

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


        cout<<"here : "<< result<<endl;
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
         (x >= 'A' && x <= 'Z')){

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


State NFA :: compine(){



}

