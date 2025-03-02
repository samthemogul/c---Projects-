#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <complex>

using namespace std;

class Coefficient
{
public:
    int a;
    int b;
    int c;
    Coefficient()
    {
        a = 0;
        b = 0;
        c = 0;
    }
};

class ComplexRoots
{
public:
    complex<double> root1;
    complex<double> root2;
    ComplexRoots()
    {
        root1 = 0;
        root2 = 0;
    }
};

class Quadratic
{
public:
    int a;
    int b;
    int c;

private:
    Quadratic()
    {
        a = 0;
        b = 0;
        c = 0;
    }
    int CalcDeterminant()
    {
        int d = b * b - 4 * a * c;
        if (d > 0)
        {
            return 2;
        }
        else if (d == 0)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }


public:
    Quadratic(int a, int b, int c)
    {
        this->a = a;
        this->b = b;
        this->c = c;
    };

    void SetCoefficients(int a, int b, int c)
    {
        this->a = a;
        this->b = b;
        this->c = c;
    }
    pair<complex<double>, complex<double>> QuadraticRoots() 
    {
        complex<double> root1, root2;
        int d = CalcDeterminant();
        if (d == 2)
        {
            root1 = (-b + sqrt(static_cast<double>(b * b - 4 * a * c))) / (2 * a);
            root2 = (-b - sqrt(static_cast<double>(b * b - 4 * a * c))) / (2 * a);
        }
        else if (d == 1)
        {
            root1 = -b / (2 * a);
            root2 = root1;
        }
        else if (d == 0)
        {
            double realPart = -b / (2.0 * a);
            double imaginaryPart = sqrt(static_cast<double>(4 * a * c - b * b)) / (2.0 * a);
            root1 = complex(realPart, imaginaryPart);
            root2 = complex(realPart, -imaginaryPart);
            
        }
        return make_pair(root1, root2);
    }
    vector<int> GetCoefficients(Coefficient *c)
    {
        vector<int> v;
        v.push_back(c->a);
        v.push_back(c->b);
        v.push_back(c->c);
        return v;
    }
    void WriteRoots(ComplexRoots *r)
    {
        int d = CalcDeterminant();
        if(d == 0){
            cout << "Root 1: " << r->root1.real() << " + " << r->root1.imag() << "i" << endl;
            cout << "Root 2: " << r->root2.real() << " - " << r->root2.imag() << "i" << endl;
        }
        else{
            cout << "Root 1: " << r->root1.real() << endl;
            cout << "Root 2: " << r->root2.real() << endl;
        }
        
    }
};

int main()
{
    Quadratic q(6, 2, 1);
    Coefficient c;
    c.a = 1;
    c.b = 2;
    c.c = 1;
    q.SetCoefficients(c.a, c.b, c.c);
    vector<int> v = q.GetCoefficients(&c);
    cout << "a: " << v[0] << endl;
    cout << "b: " << v[1] << endl;
    cout << "c: " << v[2] << endl;

    ComplexRoots r;
    pair<complex<double>, complex<double>> res = q.QuadraticRoots();
    r.root1 = res.first;
    r.root2 = res.second;
    q.WriteRoots(&r);

    return 0;
}
