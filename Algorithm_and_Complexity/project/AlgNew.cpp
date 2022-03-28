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

    vector<struct task*> prev;
    vector<struct task*> next;
    vector<struct demand*> demand_list;
    vector<struct demand*> demand_list_1;
    vector<struct demand*> demand_list_2;
    vector<struct demand*> tmp_demand_list;

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
    bool located;

    vector<int> retreat_type;
    bool main_retreat;

};

struct dataCenter
{
    int slot_num;
    int hold;
    vector<struct demand*> serve_demand;
    vector<struct demand*> serve_demand_1;
    vector<struct demand*> serve_demand_2;
    vector<struct edge*> edge_list;

};


struct edge
{
    double capacity;
    double mark;
    int from;
    int to;
};

double current_time;
double shortest_time;
double average_time;
double interval_time;
map<double, int> interrupt_time;//从小到大

int job_num;
int dataCenter_num;
int task_count;
int put;

vector<struct job*> job_list;
vector<struct task*> task_list;
vector<struct demand*> demand_list;
vector<struct demand*> demand_list_1;
vector<struct demand*> demand_list_2;
vector<struct dataCenter*> dataCenter_list;

vector<struct demand*> tmp_demand_list;
vector<struct demand*> recycle_demand_list;
vector<struct edge*> tmp_edge_list;

vector<vector<double> > bandwidth;
vector<vector<edge *> > edges;
vector<vector<int> > slot_selection;
vector<vector<struct task*> > task_arrangement;
map<string, int> resource_table;

int slot_selection_mark;
int task_arrangement_mark;


int* distribution;

void importData();
void linear_program();
void add_to_dc(vector<vector<int> > &x, int task_id);
bool slot_check(vector<vector<int> > &x);
bool bandwidth_check(vector<vector<int> > &x);
double calculate_time(vector<vector<int> > &x);
void record(vector<vector<int> > &x);
void print_out();

int main()
{
    put = 0;
    importData();
    distribution = new int[task_count];
    shortest_time = 10000000.0;
    linear_program();
    print_out();

    system("pause");
    return 0;
}


void print_out()
{
    cout << "shortest time is " << shortest_time << endl;
    for(int i=0; i<task_count; i++)
    {
        struct task* t = task_list[i];
        cout << "Task " << t->task_id << " of Job " << t->job_id << " is located at Data Center " << distribution[i] << endl;
    }
}



void record(vector<vector<int> > &x)
{
    for(int i=0; i<task_count; i++)
    {
        for(int j=0; j<dataCenter_num; j++)
        {
            if(x[i][j] == 1)
                distribution[i] = j;
        }
    }
}



double calculate_time(vector<vector<int> > &x)
{
    double time = 0;
    for(int i=0; i<job_num; i++)
    {
        for(int j=0; j<job_list[i]->task_list.size(); j++)
        {
            struct task* t = job_list[i]->task_list[j];
            int dc_id = t->dc_id;
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

            time += (max_time+job_list[i]->task_list[j]->execution_time);
        }
    }

    if(put = 10000)
    {
        cout << time/job_num << endl;
        put = 0;
    }
    put ++;
    return time;
}




bool bandwidth_check(vector<vector<int> > &x)
{
    for(int i=0; i<demand_list_1.size(); i++)
    {
        struct demand* d = demand_list_1[i];
        if(bandwidth[d->source][d->asker->dc_id] == 0)
            return false;
    }

    for(int i=0; i<demand_list_2.size(); i++)
    {
        struct demand* d = demand_list_2[i];
        int from = task_list[d->pre_task]->dc_id;
        if(bandwidth[from][d->asker->dc_id] == 0)
            return false;
    }

    return true;
}


bool slot_check(vector<vector<int> > &x)
{
    for(int i=0; i<dataCenter_num; i++)
    {
        int slot_sum = 0;
        for(int j=0; j<task_count; j++)
            slot_sum += x[j][i];
        
        if(slot_sum > dataCenter_list[i]->slot_num)
            return false;
    }

    return true;
}




void add_to_dc(vector<vector<int> > &x, int task_id)
{
    if(task_id >= task_count)
    {
        double time = calculate_time(x);
            if(time < shortest_time)
            {
                record(x);
                shortest_time = time;
                cout << "record time: " << time/job_num <<endl;
            }

        return;
    }


    for(int i=0; i<dataCenter_num; i++)
    {
        x[task_id][i] = 1;
        dataCenter_list[i]->hold ++;
        if(dataCenter_list[i]->hold <= dataCenter_list[i]->slot_num)
        {
            task_list[task_id]->dc_id = i;
            add_to_dc(x, task_id+1);
        }
        x[task_id][i] = 0;
        dataCenter_list[i]->hold --;
    }
}






void linear_program()
{
    vector<vector<int> > x;
    x.resize(task_count);
    for(int i=0; i<task_count; i++)
    {
        for(int j=0; j<dataCenter_num; j++)
            x[i].push_back(0);
    }

    add_to_dc(x, 0);
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
        edges.resize(dataCenter_num);
        double capacity;
        string number;
        for(int i=0; i<dataCenter_num; i++)
        {
            getline(bd, dustbin, '[');
            bandwidth[i].resize(dataCenter_num);
            edges[i].resize(dataCenter_num);
            for (int j=0; j<dataCenter_num; j++)
            {
                getline(bd, number, '.');
                capacity = atof(number.c_str());
                bandwidth[i][j] = capacity;
                if(capacity > 0)
                {
                    struct edge* ed;
                    ed = new struct edge;
                    ed->capacity = capacity;
                    ed->mark = capacity;
                    ed->from = i;
                    ed->to = j;
                    dataCenter_list[i]->edge_list.push_back(ed);
                    tmp_edge_list.push_back(ed);
                    edges[i][j] = ed;
                }
                else
                {
                    struct edge* ed;
                    ed = new struct edge;
                    ed->capacity = capacity;
                    ed->mark = capacity;
                    ed->from = i;
                    ed->to = j;
                    edges[i][j] = ed;
                }

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
                t->available = false;
                t->finished = false;
                t->executed = false;
                t->job_id = jb_id;
                t->task_id = tsk_id;
                t->dc_id = -1;
                tmp->task_list.push_back(t);
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
                        dd->located = false;
                        dd->main_retreat = false;
                        dd->allocated_bandwidth = 0;
                        dd->source = resource_table[a];
                        dd->pre_task = -1;
                        dd->asker = t;
                        dd->total_need = x;
                        dd->current_need = x;
                        demand_list_1.push_back(dd);
                        tmp_demand_list.push_back(dd);
                        t->demand_list_1.push_back(dd);
                        t->demand_list.push_back(dd);
                        t->tmp_demand_list.push_back(dd);
                        
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
                            dd->located = false;
                            dd->main_retreat = false;
                            dd->allocated_bandwidth = 0;
                            dd->source = -1;
                            dd->pre_task = tsk_id;
                            dd->asker = t;
                            dd->total_need = x;
                            dd->current_need = x;
                            demand_list_2.push_back(dd);
                            tmp_demand_list.push_back(dd);
                            t->demand_list_2.push_back(dd);
                        }

                    

                        else
                        {
                            getline(tk, n, ' ');
                            getline(tk, dustbin, '\n');
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