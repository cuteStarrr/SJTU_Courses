bool Get_Value(string str, long double & num) {
    for(int i = 0; i < str.size(); ++i) {
        int value = int(str[i]);
        if(!((value >= 48 && value <= 57) || value == 46 || value == 43 || value == 45)) {
            cout << "error";
            return false;
        }
    }
    num = strtold(str.c_str(), NULL);
    return true;
}

string Point_four(long double num) {
    string str = to_string(num);
    size_t n=str.find('.');
    if(n != str.npos) {// 有小数点
        int need_len;
        if(5 + n > str.size()) {
            need_len = 4 - str.size() + n + 1;
        }
        else need_len = 0;
        if(need_len) {
            for(int k = need_len; k > 0 ; --k) {
                str = str + "0";
            }
        }
        else {
            str = str.substr(0,n + 5);
        }
    }
    else {str = str + ".0000";}

    return str;
}

int main()
{
    /********** Begin **********/
    bool exercisel = true;
   	if (exercisel){
    //第一关执行代码 完成 Interpolation.cpp与 Interpolation.h文件
   		long double x;
        map<long double, long double> points;
        string str;
        getline(cin,str);
        if(!(Get_Value(str, x))) return 0;
        cout << x << '\n';
        while(getline(cin,str)) {
            cout << '@' << '\n';
            long double tmp_x, tmp_y;
            string out;
            istringstream s(str);
            s >> out;
            if(!(Get_Value(out, tmp_x))) return 0;
            cout << tmp_x << '\n';
            s >> out;
            if(!(Get_Value(out, tmp_y))) return 0;
            cout << tmp_y << '\n';
            points.insert(pair<long double, long double>(tmp_x, tmp_y));
        }
        
        map<long double, long double> :: iterator front = points.begin();
        map<long double, long double> :: iterator behind = ++ front;
        front = points.begin();
        long double dist = behind -> first - front -> first;
        int flag = 0;
        while(behind != points.end()) {
            long double tmp_dist = behind -> first - front -> first;
            if(abs(tmp_dist - dist) > 0.0001) {
                flag = 1;
                break;
            }
            ++ behind;
            ++ front;
        }
        if(flag) {
            cout << "error";
            return 0;
        }

        long double **y;
        y = new long double * [points.size()];
        map<long double, long double> :: iterator it = points.begin();
        for(int i = 0; i < points.size(); ++i) {
            y[i] = new long double [points.size()];
            y[i][0] = it -> second;
            ++it;
        }
        for(int i = 1; i < points.size(); ++i) {
            for(int j = i; j < points.size(); ++j) {
                y[i][j] = y[i][j - 1] - y[i - 1][j - 1];
            }
        }

        long double ans = 0;
        for(int i = 0; i < points.size(); ++i) {
            long double factorial = 1;
            for(int k = 1; k <= i; ++k) {
                cout << "d " << dist << '\n';
                factorial = factorial * k * dist;
            }
            cout << 'f' << ' ' << factorial << '\n';
            long double tmp = y[i][i] / factorial;
            map<long double, long double> :: iterator it = points.begin();
            for(int j = 0; j < i; ++j) {
                tmp = tmp * (x - it -> first);
                ++it;
            }
            cout << "i:" << i << ' ' << tmp << '\n';
            ans += tmp;
        }
        cout << Point_four(ans);

        for(int i = 0; i < points.size(); ++i) {
            delete [] y[i];
        }
        delete [] y;
    
    
    } else{
   	//第二执行代码 完成 SimpleLinearRegression.cpp与 SimpleLinearRegression.h文件
   
   	
    }
    
	/********** End **********/
  	return 0;
}

