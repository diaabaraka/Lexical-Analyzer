#ifndef DFAMINIMIZER_H
#define DFAMINIMIZER_H


class DfaMinimizer
{
    public:
        DfaMinimizer(vector <State*> allStates);
        minimize(vector <State*> allStates);
        int [] setTheMappingArr(working_set,int n);
        virtual ~DfaMinimizer();
    protected:
    private:
};

#endif // DFAMINIMIZER_H
