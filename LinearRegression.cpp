#include <bits/stdc++.h>
using namespace std;
typedef long double ld;
#define DIV 10000

vector<ld>x[10000],Feature[10000],Y,w,Ypred,Slop;
map<string,int>mp;
int k=1;

void print(int m,ld Error)
{
    cout << "\n\n\tValues of Feature(Xi):\n\n";
    for (int i=1; i<m; i++)
    {
        cout << "\tX" << i << " = ";
        for (int j=0; j<Feature[1].size(); j++)
            cout << Feature[i][j] << " ";
        cout << endl;
    }
    cout << endl << endl;

    cout << "\n\n\tValues of Y:\n\n";
    for (int i=1; i<Y.size(); i++)
        cout << "\tY" << i << " = " << Y[i] << "\t\tYpred" << i << " = " << Ypred[i] << endl;
    cout << endl << endl;

    cout << "\n\n\tValues of Slop:\n\n" ;
    for (int i=0; i<Slop.size(); i++)
        cout << "\tSlop" << i << " = " << Slop[i] << endl;
    cout << endl << endl;

    cout << "\n\n\tInitial values of W:\n\n" ;
    for (int i=0; i<=Feature[1].size(); i++)
        cout << "\tW" << i << " = " << w[i] << "\n";
    cout << endl << endl;

    cout << "Updated value of W:\n\n";
    for (int i=0; i<=Feature[1].size(); i++)
        cout << "\tW" << i << " = " << w[i] << "\n";
    cout << endl << endl;

    cout << "\tError" << " = " << Error << endl << endl << endl;
}

void init()
{
    system("Color 70");
    cout << "\n\n\tYou have to enter the input file name. Example: filename.csv\n"
         << "\tFile should be in .csv  format.\n"
         << "\tFile should be located in the same directory where this code is located.\n\n"
         << "\tYou can run multiple datasets.\n"
         << "\t20 iteration is set as default.\n"
         << "\tIf you want to see the predicted value and updated value then you have to uncomment the print function call.\n\n"
         << "\tThere is a limitation: if the error is more than 10^77 it will cross the limit.\n\n";
    for (int i=0; i<=10000; i++)
    {
        x[i].clear();
        Feature[i].clear();
    }
    Y.clear();
    w.clear();
    Ypred.clear();
    Slop.clear();
    mp.clear();
}

int read(string NAME)
{
    int m=0,cnt=0;
    ld val;
    string str,Nstr;
    fstream newfile;

    newfile.open(NAME.c_str(),ios::in);
    if(newfile.is_open())
    {
        while(getline(newfile, str))
        {
            m++;
            stringstream check1(str);

            while(getline(check1, Nstr, ','))
            {
                if ((Nstr[0]>=65 && Nstr[0]<=90)||(Nstr[0]>=97 && Nstr[0]<=122))
                {
                    if (mp[Nstr]==0 && m>1)
                        mp[Nstr]=++cnt;
                    val=mp[Nstr];
                }
                else
                    val = atof(Nstr.c_str());
                x[m].push_back(val);
            }
        }
        newfile.close() ;
    }
    return m;
}

int main()
{
    for (int T=1; T<=k; T++)
    {
        init();

        string NAME;
        cout << "\n\n\tPlease enter the file name: ";
        cin >> NAME;
        cout << endl << endl;

        int m = read(NAME);

        Y.push_back(0);
        for (int i=2; i<=m; i++)
        {
            for (int j=0; j<x[i].size(); j++)
            {
                if (j<(x[i].size()-1))
                    Feature[i-1].push_back(x[i][j]);
                else
                    Y.push_back(x[i][j]);
            }
        }

        ///Initial Random Value of W
        for(int i=0; i<=Feature[1].size(); i++)
        {
            ld r = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
            w.push_back(r);
        }

        cout << "\tDataset\tNo of Iteration\tLearning Rate\tSquared Error\n";

        ///Loop for Iteration
        for (int K=1; K<=20; K++)
        {
            Ypred.clear();
            Slop.clear();

            ///Predict Value of Y
            Ypred.push_back(0);
            for (int i=1; i<m; i++)
            {
                ld calc=0.0;
                for (int j=0; j<Feature[1].size(); j++)
                    calc+=(w[j+1]*Feature[i][j]);
                Ypred.push_back(calc+w[0]);
            }

            ///Slop
            int t=Feature[1].size();
            float Dcalc;
            for (int i=0; i<=t; i++)
            {
                Dcalc=0.0;
                for (int j=1; j<Y.size(); j++)
                {
                    if (i==0)
                        Dcalc+=(Ypred[j]-Y[j]);
                    else
                        Dcalc+=((Ypred[j]-Y[j])*Feature[j][i-1]);
                }
                Slop.push_back(Dcalc);
            }

            ///Error
            ld Error=0.0;
            for (int j=1; j<Y.size(); j++)
                Error+=(((Ypred[j]-Y[j])*(Ypred[j]-Y[j]))*.5);

            ///update
            ld A = static_cast<float>(rand()) / (DIV*static_cast<float>(RAND_MAX));
            for (int i=0; i<=t; i++)
                w[i]=(w[i]-(A*Slop[i]));

///        print(m,Error);

            string fName;
            for (int i=0; i<NAME.size()-4; i++)
                fName+=NAME[i];
            cout << "\t" << fName << "\t\t" << K << "\t" << A << "\t" << Error << endl;
        }
        char c;
        cout << "\n\n\tDo you want to run again? y/n: ";
        cin >> c;
        if(c=='y'|c=='Y')
            k++;
    }
}
