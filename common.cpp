#include "common.h"

int split(const string& s, char c, vector<string>& v){
    string::size_type i = 0;
    string::size_type j = s.find(c);
    if(j != string::npos){   
        while (j != string::npos){
            v.push_back(s.substr(i, j - i));
            i = ++j;
            j = s.find(c, j);
            if (j == string::npos)
                v.push_back(s.substr(i, s.length()));
        }
    }
    else
        v.push_back(s);
    return 0;
}

bool cmp(const pair<int, float>& p1, const pair<int, float>& p2){
    return p1.first < p2.first;
}

float dot_product(const sparse_vector& v1, const sparse_vector& v2){
    float dot = 0.0;
    int p1, p2, a1, a2;
    p1 = p2 = 0;
    while(p1 < v1.size() && p2 < v2.size()){
        a1 = v1[p1].first;
        a2 = v2[p2].first;
        if(a1 == a2){
            dot += v1[p1].second * v2[p2].second;
            p1++;
            p2++;
        }
        else if(a1 > a2) p2++;
        else p1++;
    }
    return dot;
}


void print_sparse_vector(const sparse_vector& v){
    for(int i = 0; i < v.size(); i++)
        cerr << v[i].first << ':' << v[i].second << endl;
}

sparse_vector operator*(const sparse_vector& v, float f){
    sparse_vector p;
    for(int i = 0; i < v.size(); i++)
        p.push_back(pair<int, float>(v[i].first, v[i].second * f));
    return p;
}

sparse_vector operator*(float f, const sparse_vector& v){
    return v * f;
}

sparse_vector operator+(const sparse_vector& v1, const sparse_vector& v2){
    sparse_vector s;
    int p1, p2, a1, a2;
    p1 = p2 = 0;
    while(p1 < v1.size() && p2 < v2.size()){
        a1 = v1[p1].first;
        a2 = v2[p2].first;
        if(a1 == a2){
            pair<int, float> p(a1, v1[p1].second + v2[p2].second);
            s.push_back(p);
            p1++;
            p2++;
        }
        else if(a1 > a2){
            s.push_back(v2[p2]);
            p2++;
        }
        else{
            s.push_back(v1[p1]);
            p1++;
        }
    }
    for(; p1 < v1.size(); p1++)
        s.push_back(v1[p1]);
    for(; p2 < v2.size(); p2++)
        s.push_back(v2[p2]);
    return s;
}

int batch_read_sample(ifstream& is, vector<sparse_vector>& X, vector<float>& Y, int& n){
    string s;
    sparse_vector x;
    float y;
    n = 0;
    while(getline(is, s, '\n')){
        read_sample(s, x, y);
        X.push_back(x);
        Y.push_back(y);
        n += 1;
    }
    return 0;
}

int batch_write_sample(ofstream& os, vector<sparse_vector>& X, vector<float>& Y, int& n){
    string s;
    n = 0;
    for(int i = 0; i < X.size(); i++){
        write_sample(s, X[i], Y[i]);
        os << s << endl;
        n += 1;
    }
    return 0;
}


int read_sample(string& s, sparse_vector& x, float& y){
    int key;
    float val;
    vector<string> s_arr;
    split(s, ' ', s_arr);
    
    y = atof(s_arr[0].c_str());
    x.clear();
    for(int i = 1; i < s_arr.size(); i++){
        vector<string> kv;
        split(s_arr[i], ':', kv);
        key = atoi(kv[0].c_str());
        val = atof(kv[1].c_str());
        pair<int, float> p(key, val);
        x.push_back(p);
    }
    sort(x.begin(), x.end(), cmp);
    return 0;
}

int write_sample(string& s, sparse_vector& x, float& y){
    ostringstream oss;
    oss << y;
    for(int i = 0; i < x.size(); i++)
        oss << ' ' << (x[i].first + 1) << ':' << x[i].second;
    s = oss.str();
    return 0;
}

