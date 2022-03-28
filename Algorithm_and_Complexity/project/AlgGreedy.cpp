#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <math.h>
using namespace std;



struct task
{
    int job_id;
    int task_id;
    int dc_id;
    double execution_time;
    bool available;//available后，需先去dc ++各种demand
    bool finished;
    bool executed;
    double great_need;

    vector<struct task*> prev;
    vector<struct task*> next;
    vector<struct demand*> demand_list;
    vector<struct demand*> demand_list_1;
    vector<struct demand*> demand_list_2;
};

struct job
{
    vector<struct task*> task_list;
    double execution_time;
    double start_time;
    bool started;
    bool finished;

};

struct demand
{
    double total_need;
    double current_need;
    double allocated_bandwidth;
    struct task* asker;
    int pre_task;
    int source;// satisfied后需返回dc --
    bool satisfied;


};

struct dataCenter
{
    int slot_num;
    int hold;

};


double current_time;
double shortest_time;
double average_time;
double interval_time;
map<double, int> interrupt_time;//从小到大

int job_num;
int dataCenter_num;
int task_count;

vector<struct job*> job_list;
vector<struct task*> task_list;
vector<struct task*> tmp_task_list;
vector<struct demand*> demand_list;
vector<struct demand*> demand_list_1;
vector<struct demand*> demand_list_2;
vector<struct dataCenter*> dataCenter_list;


vector<vector<double> > bandwidth;
vector<vector<int> > slot_selection;
vector<vector<struct task*> > task_arrangement;
map<string, int> resource_table;




void importData();
double calculate_time();
void biggest_demand_first();
bool compareTask(const task* a, const task* b);
bool hasFinished();
void add_available_demand();
bool compareDemand1(const demand* p, const demand* q);
bool compareDemand2(const demand * a, const demand * b);
bool compareTime(const pair<double, int> bb, const pair<double, int> ee);
void update();
void max_min_fairness();
double get_average_time();
void output();



int main()
{
    importData();
    shortest_time = 10000000.0;
    biggest_demand_first();

    current_time = 0.0;
    while(hasFinished()!=true)
    {
        add_available_demand();
        max_min_fairness();
        update();
    }

    shortest_time = get_average_time();
    cout << "Shortest average time = " << shortest_time << endl;
    output();
    system("pause");
    return 0;

}



bool compareTask(const task* a, const task* b)
{
    return a->great_need > b->great_need;
}



void biggest_demand_first()
{
    sort(tmp_task_list.begin(), tmp_task_list.end(), compareTask);
    vector<struct task*>::iterator b = tmp_task_list.begin();

    while(b!=tmp_task_list.end())
    {
        double fetch_time = 1000000;
        int dc_id = 0;
        for(int i=0; i<dataCenter_num; i++)
        {
            if(dataCenter_list[i]->hold == dataCenter_list[i]->slot_num)
                continue;
            
            double tmp_time = 0;;
            for(int j=0; j<(*b)->demand_list_1.size(); j++)
            {
                double t = (*b)->demand_list_1[j]->total_need/bandwidth[(*b)->demand_list_1[j]->source][i];
                tmp_time = (tmp_time>t)? tmp_time:t;
            }

            if(tmp_time<fetch_time)
            {
                dc_id = i;
                fetch_time = tmp_time;
            }
        }

        dataCenter_list[dc_id]->hold ++;
        (*b)->dc_id = dc_id;
        b++;
    }


    for(int i=0; i<demand_list_2.size(); i++)
    {
        demand_list_2[i]->source = task_list[demand_list_2[i]->pre_task]->dc_id;
        demand_list_2[i]->asker->demand_list.push_back(demand_list_2[i]);
    }
}






double calculate_time()
{
    double time = 0;
    for(int i=0; i<job_num; i++)
    {
        for(int j=0; j<job_list[i]->task_list.size(); j++)
        {
            struct task* t = job_list[i]->task_list[j];
            int dc_id = t->dc_id;
            cout << "Task" << j << " of Job " << i << " is at DC " << dc_id <<endl;
            double max_time = 0;
            double tmp;
            for(int k=0; k<t->demand_list_1.size(); k++)
            {
                double bd = bandwidth[t->demand_list_1[k]->source][dc_id];
                if(bd == 0)
                {
                    cout << "bandwidth = 0 " << endl;
                    return 100000;
                }
                tmp = t->demand_list_1[k]->total_need/bd;
                max_time = (tmp>max_time)? tmp:max_time;
            }

            for(int k=0; k<t->demand_list_2.size(); k++)
            {
                tmp = t->demand_list_2[k]->total_need/bandwidth[task_list[t->demand_list_2[k]->pre_task]->dc_id][dc_id];
                max_time = (tmp>max_time)? tmp:max_time;
            }

            time += (max_time + job_list[i]->task_list[j]->execution_time);
        }
    }

    cout << time << endl;
    return time;
}






bool hasFinished()
{
    //check if all the jobs are done
    for(int i=0; i<job_num; i++)
    {
        if(!job_list[i]->finished)
        {
            cout << "job " << i << " hasn't finished" << endl;
            return false;
        }
    }

    return true;
}


void add_available_demand()
{
    for(int task_id=0; task_id<task_count; task_id++)
    {
        if(!task_list[task_id]->executed && task_list[task_id]->available)//在输入以及update的时候set available
        {
            if(!job_list[task_list[task_id]->job_id]->started)
            {
                job_list[task_list[task_id]->job_id]->started = true;
                job_list[task_list[task_id]->job_id]->start_time = current_time;
            }

            for(int demand_id=0; demand_id<task_list[task_id]->demand_list.size(); demand_id++)
                demand_list.push_back(task_list[task_id]->demand_list[demand_id]);
            task_list[task_id]->executed = true;
        }
    }
}

bool compareDemand1(const demand* p, const demand * q)
{
    return (p->current_need/p->allocated_bandwidth) < (q->current_need/q->allocated_bandwidth);
    
}

bool compareTime(const pair<double, int> bb, const pair<double, int> ee)
{
    return bb.first < ee.first;
}


void update()
{
    cout << "update:" << endl;
    sort(demand_list.begin(), demand_list.end(), compareDemand1);
    int k = 0;
    while(k<demand_list.size() && demand_list[k]->satisfied)
        k++;

    if(k < demand_list.size())
        interval_time = demand_list[k]->current_need/demand_list[k]->allocated_bandwidth;

    if(k==demand_list.size() || !interrupt_time.empty()&&(*interrupt_time.begin()).first < current_time+interval_time)
    {
        if(interrupt_time.empty())
            return;
        interval_time = (*interrupt_time.begin()).first-current_time;
        current_time = (*interrupt_time.begin()).first;
        cout << "Now is " << current_time << "s" << endl;
        int task_id = (*interrupt_time.begin()).second;
        
        task_list[task_id]->finished = true;
        cout << "task "<< task_id << " of job " << task_list[task_id]->job_id << " is finished" << endl;

        int jb_id = task_list[task_id]->job_id;
        int tsk_num = job_list[jb_id]->task_list.size();
        bool tmp = true;
        for(int t=0; t<tsk_num; t++)
        {
            if(!job_list[jb_id]->task_list[t]->finished)
            {
                tmp = false;
                break;
            }
        }
                    
        if(tmp)
        {
            job_list[jb_id]->finished = true;
            job_list[jb_id]->execution_time = current_time - job_list[jb_id]->start_time;
            cout << "job " << jb_id << " finished at " << job_list[jb_id]->execution_time <<endl;
            if(hasFinished())
                return;
        }

        int next_num = task_list[task_id]->next.size();
        for(int n=0; n<next_num; n++)
        {
            int prev_num = task_list[task_id]->next[n]->prev.size();
            bool tmp2 = true;
            for(int p=0; p<prev_num; p++)
            {
                if(!task_list[task_id]->next[n]->prev[p]->finished)
                {
                    tmp2 = false;
                    break;
                }
            }

            if(tmp2)    
                task_list[task_id]->next[n]->available = true;
        }
                    
        interrupt_time.erase(interrupt_time.begin());
    }
    else
    {
        current_time += interval_time;
        cout << "Now is " << current_time << "s" << endl;
    }


    for (int i=0; i<demand_list.size();i++)
    {
        if(demand_list[i]->satisfied != true)
        {
            demand_list[i]->current_need -= demand_list[i]->allocated_bandwidth*interval_time;
            if (demand_list[i]->current_need < 0.01)
            {
                cout << "task " << demand_list[i]->asker->task_id << "'s one demand is satisfied"<< endl;
                demand_list[i]->satisfied = true;
                int task_id = demand_list[i]->asker->task_id;

                bool tmp = true;
                for(int d=0; d<task_list[task_id]->demand_list.size(); d++)
                {
                    if(!task_list[task_id]->demand_list[d]->satisfied)
                    {
                        if(task_list[task_id]->demand_list[d]->current_need < 0.01)
                        {
                            cout << "task " << task_id << "'s one demand is satisfied"<< endl;
                            task_list[task_id]->demand_list[d]->satisfied = true;
                            continue;
                        }

                        tmp = false;
                        break;
                    }
                }
                
                if(tmp)
                {
                    interrupt_time.insert(make_pair(current_time + task_list[task_id]->execution_time, task_id));
                    cout << "task " << demand_list[i]->asker->task_id << " is being executed " << endl;
                    cout << "due to finish at " << current_time + task_list[task_id]->execution_time << endl; 
                }
            }
        }
        
     }


    //1. 更新各种时间，demand的current_need，satisfied/finished/available signs，修改dc的demand_num

    //2. 在1的同时添加available的task
}



bool compareDemand2(const demand* a, const demand* b)
{
    return a->current_need > b->current_need; //从da到xiao
}


void max_min_fairness()
{
    vector<vector<vector<demand *> > > tmp;
    tmp.resize(dataCenter_num);
    for(int i=0; i<dataCenter_num; i++)
        tmp[i].resize(dataCenter_num);

    for(int i=0; i<demand_list.size(); i++)
    {
        if(!demand_list[i]->satisfied)
            tmp[demand_list[i]->source][demand_list[i]->asker->dc_id].push_back(demand_list[i]);
    }

    for(int idx=0; idx<dataCenter_num; idx++)
    {
        for(int dc_id=0; dc_id<dataCenter_num; dc_id++)
        {
            if(!tmp[idx][dc_id].empty())
            {
                sort(tmp[idx][dc_id].begin(), tmp[idx][dc_id].end(), compareDemand2);

                double allocated_bandwidth;
                double cost = 0;
                while(!tmp[idx][dc_id].empty())
                {
                    int m = tmp[idx][dc_id].size();
                    allocated_bandwidth = (bandwidth[idx][dc_id]-cost)/double(m);
                    if(tmp[idx][dc_id][m-1]->current_need < allocated_bandwidth && tmp[idx][dc_id].size()>1)
                    {
                        tmp[idx][dc_id][m-1]->allocated_bandwidth = tmp[idx][dc_id][m-1]->current_need;
                        cout << "1 bandwidth: " << tmp[idx][dc_id][m-1]->allocated_bandwidth <<endl;
                        cost += tmp[idx][dc_id][m-1]->allocated_bandwidth;
                        tmp[idx][dc_id].pop_back();
                        continue;
                    }

                    while(m>0)
                    {
                        tmp[idx][dc_id][m-1]->allocated_bandwidth = allocated_bandwidth;
                        cout << "2 bandwidth: " << allocated_bandwidth <<endl;
                        tmp[idx][dc_id].pop_back();
                        m--;
                    }
                }
                
            }
        }
        
    }
    

    //更新available的task的demand的allocated_width
}


double get_average_time()
{
    //return各job的execution_time的平均数
    double tot = 0;
    for (int i=0; i<job_num; i++)
      tot += job_list[i]->execution_time;
    average_time =tot/(double)job_num;
    return average_time;
}




void output()
{
    //输出最短时间和slot分配
    for (int i=0; i<task_count; i++)
        cout << "Task " << i << " of Job " <<task_list[i]->job_id << " is at DC " << task_list[i]->dc_id<<endl;
}






void importData()
{
    string dustbin;
    //读第三个sheet 获得resource_table, dc_num, dataCenter_list
    ifstream slot;
    slot.open("C:\\Users\\10593\\Desktop\\slots.txt");
    if(slot.is_open())
    {
        while(!slot.eof())
        {
            string sss;
            getline(slot, sss, '.');
            if(sss[0] < '0' || sss[0] > '9')
                break;
            int sn;
            sn = atoi(sss.c_str());
            struct dataCenter* dc;
            dc = new struct dataCenter;
            dataCenter_list.push_back(dc);
            dc->slot_num = sn;
            dc->hold = 0;
            getline(slot, dustbin, ' ');
        }

        dataCenter_num = dataCenter_list.size();
    }
    slot.close();

    ifstream resource;
    resource.open("C:\\Users\\10593\\Desktop\\resource.txt");
    if(resource.is_open())
    {
        while (!resource.eof())
        {
            string rs;
            getline(resource, rs, ',');
            if(rs[0]=='\n')
                rs.erase(0, 1);
            int id;
            resource>>id;
            resource_table.insert(pair<string, int> (rs, id-1));
        }       
    }
    resource.close();


    //读第一个sheet 获得bandwidth
    ifstream bd;
    bd.open("C:\\Users\\10593\\Desktop\\bandwidth.txt");
    if(bd.is_open())
    {
        bandwidth.resize(dataCenter_num);
        double capacity;
        string number;
        for(int i=0; i<dataCenter_num; i++)
        {
            getline(bd, dustbin, '[');
            bandwidth[i].resize(dataCenter_num);
            for (int j=0; j<dataCenter_num; j++)
            {
                getline(bd, number, '.');
                capacity = atof(number.c_str());
                bandwidth[i][j] = capacity;

                if(j==dataCenter_num-1)
                    break;
                getline(bd, dustbin, ' ');
            }
        }
    }
    bd.close();  

    for(int i=0; i<dataCenter_num; i++)
    {
        for(int j=0; j<dataCenter_num; j++)
        {
            if(bandwidth[i][j] == 0)
            {
                for(int k=0; k<dataCenter_num; k++)
                {
                    int a=bandwidth[i][k];
                    int b=bandwidth[k][j];
                    if(a>0 && b>0)
                    {
                        double tmp_bd = (a>b)? b:a;
                        bandwidth[i][j] = (tmp_bd >bandwidth[i][j])? tmp_bd:bandwidth[i][j];
                    }
                }
            }
        }
    }

    //读第二个sheet 获得job_list -> job -> task_list -> task (count taskNum) -> demand_list -> demand -> serve_demand(dataCenter)
    ifstream jb, tk;
    jb.open("C:\\Users\\10593\\Desktop\\job.txt");
    tk.open("C:\\Users\\10593\\Desktop\\task.txt");
    int tsk_num;
    int tsk_id=0;
    int jb_id=0;
    if(jb.is_open()&&tk.is_open())
    {       
        while(!jb.eof())
        {   
            string s;
            getline(jb, s, '\n');
            if(s[0]>'9'||s[0]<'0')
                break;
            tsk_num = atoi(s.c_str());
            struct job* tmp;
            tmp = new struct job;
            tmp->finished = false;
            tmp->started = false;
            tmp->execution_time = 0.0;
            for(int i=0; i<tsk_num; i++)
            {
                struct task* t;
                t = new struct task;
                t->great_need = 0;
                t->available = false;
                t->finished = false;
                t->executed = false;
                t->job_id = jb_id;
                t->task_id = tsk_id;
                t->dc_id = -1;
                tmp->task_list.push_back(t);
                tmp_task_list.push_back(t);
                task_list.push_back(t);
                tsk_id ++;
            }

            tsk_id -= tsk_num;

            for(int i=0; i<tsk_num; i++)
            {
                struct task* t = task_list[tsk_id];
                while(true)
                {
                    string a;
                    string n;
                    double x;
                    getline(tk, a, ',');
                    
                    if(a[1] != 'x' && a[0] != 't')
                    {
                        getline(tk, n, ' ');
                        x = atof(n.c_str());
                        if(x==0)
                            break;
                        struct demand* dd;
                        dd = new struct demand;
                        dd->satisfied = false;
                        dd->allocated_bandwidth = 0;
                        dd->source = resource_table[a];
                        dd->pre_task = -1;
                        dd->asker = t;
                        dd->total_need = x;
                        dd->current_need = x;
                        if(x > t->great_need)
                            t->great_need = x;
                        demand_list_1.push_back(dd);
                        t->demand_list_1.push_back(dd);
                        t->demand_list.push_back(dd);
                        
                    }

                    else 
                    {
                        if(a[0] == 't')
                        {
                            getline(tk, n, ' ');
                            x = atof(n.c_str());
                            int num = 0;
                            for(int c=2; c<a.length(); c++)
                                num += (a[c]-'0')*pow(10, a.length()-c-1);
                            num --;
                            t->prev.push_back(tmp->task_list[num]);
                            tmp->task_list[num]->next.push_back(t);
                            struct demand* dd;
                            dd = new struct demand;
                            dd->satisfied = false;
                            dd->allocated_bandwidth = 0;
                            dd->source = -1;
                            dd->pre_task = tsk_id;
                            dd->asker = t;
                            dd->total_need = x;
                            dd->current_need = x;
                            demand_list_2.push_back(dd);
                            t->demand_list_2.push_back(dd);
                        }

                    

                        else
                        {
                            getline(tk, n, ' ');
                            getline(tk, dustbin, '\n');
                            x = 0;
                            x = atof(n.c_str());
                            t->execution_time = x;
                            break;
                        }
                    }
                }
                if(task_list[tsk_id]->prev.size()==0)
                    task_list[tsk_id]->available = true;
                tsk_id ++;
            }
                
            job_list.push_back(tmp);
            jb_id ++;
        }
    }
    job_num = jb_id;
    task_count = tsk_id;
    jb.close();
    tk.close();    
}