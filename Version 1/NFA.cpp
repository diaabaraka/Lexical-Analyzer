#include "NFA.h"

NFA::NFA()
{
    //ctor
}

void NFA :: parse(string expression){

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


        State start(counter++);
        // we will transforme the expression to postfix expression

        expression_0 = postfix(expression_0);


}


string NFA:: postfix(string expression){

//Order of precedence is *or+or() (highest), then
//concatenation ($), then | (lowest).

    string operand ="";
    string result = "";

    stack<char>operations;


    for(int i = 0 ; i < expression.size() ; i++){

        if(expression[i] == '|'){

            while(operations.size() > 0 &&high_priority(expression[i] , operations.top())){

                    result = result + " " + operations.top();

                    operations.pop();

            }

            operations.push('|');


        }





    }









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


   return topPriority >= firstPriority;

}


State NFA :: compine(){



}

