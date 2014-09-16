#include "common.h"
#include "smo.h"

svm_option::svm_option(){
    C = 1.0;
    tol = 0.0001;
    eps = 0.001;
    sigma = 4.0;
    is_linear_kernel = false;
    train_path = "data/heart_scale.train";
    test_path = "data/heart_scale.test";
    model_path = "data/heart_scale.model";
    output_path = "data/heart_scale.output";
}

SMO::SMO(svm_option *opt){
    this->C = opt->C;
    this->tol = opt->tol;
    this->eps = opt->eps;
    this->sigma = opt->sigma;
    this->is_linear_kernel = opt->is_linear_kernel;
    this->train_path = opt->train_path;
    this->test_path = opt->test_path;
    this->model_path = opt->model_path;
    this->output_path = opt->output_path;

    n = 0;
    n_sv = 0;
    b = 0.0;
    delta_b = 0.0; 
}

float SMO::kernel(int i1, int i2){
    float k = dot_product(X[i1], X[i2]);
    if(!is_linear_kernel){
        k *= -2.0;
        k += D[i1] + D[i2];
        k /= -(2.0 * sigma * sigma);
        k = exp(k);
    }
    return k;
}

float SMO::learned_func(int k){
    float s = 0.0;
    if(is_linear_kernel){
        s = dot_product(w, X[k]);
    }
    else{
        for(int i = 0; i < n; i++){
            if(alpha[i] > 0)
                s += alpha[i] * Y[i] * kernel(i, k);
        }
    }
    s -= b;
    return s;
}

int SMO::predict(){

    X.clear();
    Y.clear();
    w.clear();
    alpha.clear();

    ifstream is_model(model_path);
    load_model(is_model);
     
    ifstream is_test(test_path);
    batch_read_sample(is_test, X, Y, n);

    n += n_sv;
    
    if (!is_linear_kernel){
        D.resize(n);
        for (int i = 0; i < n; i++)
            D[i] = dot_product(X[i], X[i]);
    }

    int n_correct = 0;
    float y_pred;

    ofstream os_output(output_path);
    for (int i = n_sv; i < n; i++){
        float s = 0.0;
        if(is_linear_kernel){
            s = dot_product(w, X[i]);
        }
        else{
            for(int j = 0; j < n_sv; j++)
                s += alpha[j] * Y[j] * kernel(i, j);
        }
        s -= b;
        y_pred = s >= 0.0? 1.0 : -1.0;
        os_output << y_pred << endl;
        if((y_pred > 0 and Y[i] > 0) or (y_pred < 0 and Y[i] < 0))
            n_correct++;
    }

    cerr << setprecision(5) << "Accuracy: " <<  100.0 * n_correct / (n - n_sv) << "% (" << n_correct << "/" << (n - n_sv) << ")" << endl;

    return 0;
}

int SMO::train(){

    X.clear();
    Y.clear();
    w.clear();
    D.clear();

    ifstream is_train(train_path);
    batch_read_sample(is_train, X, Y, n);

    alpha.resize(n, 0.0);
    b = 0.0;
    error_cache.resize(n, 0.0);
 
    if (!is_linear_kernel){
        D.resize(n);
        for (int i = 0; i < n; i++)
            D[i] = dot_product(X[i], X[i]);
    }

    int num_changed = 0, examine_all = 1;
    while(num_changed > 0 || examine_all){
        num_changed = 0;
        if (examine_all){
            for (int k = 0; k < n; k++)
                num_changed += examine_example(k);
        }
        else{
            for (int k = 0; k < n; k++){
                if (alpha[k] != 0 && alpha[k] != C)
                    num_changed += examine_example(k);
            }
        }
        
        if (examine_all == 1)
            examine_all = 0;
        else if (num_changed == 0)
            examine_all = 1;
        
        float s = 0.0, t = 0.0, obj = 0.0;
        for (int i = 0; i < n; i++) s += alpha[i];
        for (int i = 0; i < n; i++) for (int j = 0; j < n; j++){
            t += alpha[i] * alpha[j] * Y[i] * Y[j] * kernel(i, j);
        }

        obj = s - 0.5 * t;
        cerr << setprecision(5) << "Objective func : " << obj << "\t\t\tError rate : " << error_rate() << endl;

        for (int i = 0; i < n; i++){
            if(alpha[i] < 1e-6) alpha[i] = 0.0;
        }
    }

    ofstream os_model(model_path);
    dump_model(os_model);

    return 0;
}

int SMO::dump_model(ofstream& os){
    string s;
    
    os << is_linear_kernel << endl;
    os << b << endl;
    if (is_linear_kernel){
        os << w.size() << endl;
        for(int i = 0; i < w.size(); i++)
            os << w[i].first << ' ' << w[i].second << endl;
    }
    else{
        os << sigma << endl;
        n_sv = 0;
        for(int i = 0; i < n; i++)
            if(alpha[i] > 0) n_sv += 1;
        os << n_sv << endl;

        for(int i = 0; i < n; i++)
            if(alpha[i] > 0) os << alpha[i] << endl;

        for(int i = 0; i < n; i++){
            if(alpha[i] > 0){
                write_sample(s, X[i], Y[i]);
                os << s << endl;
            }
        }
    }
}

int SMO::load_model(ifstream& is){

    int d, m;
    string s;

    is >> is_linear_kernel;
    is >> b;
    if (is_linear_kernel){
        is >> d;
        for (int i = 0; i < d; i++){
            pair<int, float> p;
            is >> p.first >> p.second;
            w.push_back(p);
        }
        sort(w.begin(), w.end(), cmp);
    }
    else{
        is >> sigma;
        is >> n_sv;
        alpha.resize(n_sv, 0.0);
        for (int i = 0; i < n_sv; i++)
            is >> alpha[i];
        getline(is, s, '\n');
        batch_read_sample(is, X, Y, m);

    }
    return 0;
}

float SMO::error_rate(){
    int n_error = 0;
    for (int i = 0; i < n; i++){
        if((learned_func(i) >= 0 && Y[i] < 0) || (learned_func(i) < 0 && Y[i] > 0))
            n_error++;
    }
    return 1.0 * n_error / n;
}

int SMO::examine_example(int i1) {
    float y1 ,alpha1, E1, r1;
    y1 = Y[i1];
    alpha1 = alpha[i1];
    if (alpha1 > 0 && alpha1 < C)
        E1 = error_cache[i1];
    else
        E1 = learned_func(i1) - y1;
 
    r1 = y1 * E1;
    if ((r1 < -tol && alpha1 < C) || (r1 > tol && alpha1 > 0)) {
        int k0, k, i2;
        float tmax;
        for (i2 = -1, tmax = 0, k = 0; k < n; k++) {
            if (alpha[k] > 0 && alpha[k] < C){
                float E2, temp;
                E2 = error_cache[k];
                temp = fabs(E1 - E2);
                if (temp > tmax) {
                    tmax = temp;
                    i2 = k;
                }
            }
            if (i2 >= 0) {
                if (take_step(i1, i2)) return 1;
            }
        }
        for (k0 = (int)(drand48() * n), k = k0; k < n + k0; k++) {
            i2 = k % n;
            if (alpha[i2] > 0 && alpha[i2] < C) {
                if (take_step(i1, i2)) return 1;
            }
        }
        for (k0 = (int)(drand48() * n), k = k0; k < n + k0; k++){
            i2 = k % n;
            if (take_step(i1, i2)) return 1;
        }
    }
    return 0;
}

int SMO::take_step(int i1, int i2){
    int y1, y2, s;
    float alpha1, alpha2;
    float a1, a2;
    float E1, E2, L, H, k11, k22, k12, eta, Lobj, Hobj;
    if (i1 == i2) return 0;

    alpha1 = alpha[i1];
    alpha2 = alpha[i2];
    y1 = Y[i1];
    y2 = Y[i2];

    if (alpha1 > 0 && alpha1 < C)
        E1 = error_cache[i1];
    else
        E1 = learned_func(i1) - y1;
    
    if (alpha2 > 0 && alpha2 < C)
        E2 = error_cache[i2];
    else
        E2 = learned_func(i2) - y2;
    
    s = y1 * y2;
    if (y1 == y2) {
        float gamma = alpha1 + alpha2;
        if (gamma > C) {
            L = gamma - C;
            H = C;
        }
        else {
            L = 0;
            H = gamma;
        }
    }
    else{
        float gamma = alpha1 - alpha2;
        if (gamma > 0){
            L = 0;
            H = C - gamma;
        }
        else{
            L = -gamma;
            H = C;
        }
    }
    
    if (L == H) return 0;
    
    k11 = kernel(i1, i1);
    k12 = kernel(i1, i2);
    k22 = kernel(i2, i2);
    eta = 2 * k12 - k11 - k22;
    
    if (eta < 0) {
        a2 = alpha2 + y2 * (E2 - E1) / eta;
        if (a2 < L) a2 = L;
        else if (a2 > H) a2 = H;
    }
    else {
        float c1 = eta / 2.0;
        float c2 = y2 * (E1 - E2) - eta * alpha2;
        Lobj = c1 * L * L + c2 * L;
        Hobj = c1 * H * H + c2 * H;
        if (Lobj > Hobj + eps) a2 = L;
        else if (Lobj < Hobj - eps) a2 = H;
        else a2 = alpha2;
    }
    
    if (fabs(a2 - alpha2) < eps * (a2 + alpha2 + eps)) return 0;
    a1 = alpha1 - s * (a2 - alpha2);
    if (a1 < 0) {
        a2 += s * a1;
        a1 = 0;
    }
    else if (a1 > C){
        float t = a1 - C;
        a2 += s * t;
        a1 = C;
    }
    
    float b1, b2, bnew;
    if (a1 > 0 && a1 < C){
        bnew = b + E1 + y1 * (a1 - alpha1) * k11 + y2 * (a2 - alpha2) * k12;
    }
    else if (a2 > 0 && a2 < C){
        bnew = b + E2 + y1 * (a1 - alpha1) * k12 + y2 * (a2 - alpha2) * k22;
    }
    else{
        b1 = b + E1 + y1 * (a1 - alpha1) * k11 + y2 * (a2 - alpha2) * k12;
        b2 = b + E2 + y1 * (a1 - alpha1) * k12 + y2 * (a2 - alpha2) * k22;
        bnew = (b1 + b2) / 2.0;
    }
    
    delta_b = bnew - b;
    b = bnew;
   
    float t1 = y1 * (a1 - alpha1);
    float t2 = y2 * (a2 - alpha2);
 
    if (is_linear_kernel){
        w = w + t1 * X[i1] + t2 * X[i2];
    }
    
    for (int i = 0; i < n; i++){
        if (alpha[i] > 0 && alpha[i] < C)
            error_cache[i] += t1 * kernel(i1, i) + t2 * kernel(i2, i) - delta_b;
    }
    
    error_cache[i1] = 0.0;
    error_cache[i2] = 0.0;

    alpha[i1] = a1;
    alpha[i2] = a2;
    return 1;
}

