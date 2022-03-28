/*********************************************
 * OPL 12.9.0.0 Model
 * Author: lenovo
 * Creation Date: 2021年4月9日 at 上午8:38:38
 *********************************************/
{string} Prod = ...;
{string} Process = ...;

int NbMonths = ...;
range Months = 1..NbMonths;

float ProfitProd[Prod] = ...;
float ProcessProd[Process][Prod] = ...;
float MarketProd[Months][Prod] = ...;
float HoursMonth = ...;
int   NumProcess[Process] = ...;
int   NumDown[Process] = ...;

float CostHold = ...;
float StartHold = ...;
float EndHold = ...;
float MaxHold = ...;

dvar float+ Make[Prod][Months];
dvar float+ Hold[Prod][0..NbMonths] in 0..MaxHold;
dvar float+ Sell[j in Prod][m in Months] in 0..MarketProd[m][j];
dvar int+   Down[i in Process][m in Months] in 0..NumProcess[i];

dexpr float Profit = 
  sum (j in Prod, m in Months) ProfitProd[j] * Sell[j][m];
dexpr float Cost = 
  sum (j in Prod, m in Months) CostHold * Hold[j][m];
  
maximize Profit - Cost;
    
subject to {
  // Limits on process capacity
  forall(m in Months, i in Process)
    ctCapacity: sum(j in Prod) ProcessProd[i][j] * Make[j][m]
           + HoursMonth * Down[i][m]
           <= NumProcess[i] * HoursMonth;

  // Inventory balance
  forall(j in Prod, m in Months)
    ctInvBal: Hold[j][m-1] + Make[j][m] == Sell[j][m] + Hold[j][m];

  // Starting and ending inventories are fixed
  forall(j in Prod) {
    ctStartInv: Hold[j][0] == StartHold;    
    ctEndInv: Hold[j][NbMonths] == EndHold;
  }
   
  // Maintenance requirement
  forall(i in Process)
    mnt: sum(m in Months) Down[i][m] >= NumDown[i];
}

execute DISPLAY {
   for(var m in Months) 
      for(var i in Process)
         if(Down[i][m] >= 1) 
            writeln("down[",i,"][",m,"] = ",Down[i][m]);
            
   writeln();

   //plan[m][j] describes how much to make, sell, and hold of each product j in each month m
   for(m in Months)
      for(var j in Prod)
         writeln("plan[",m,"][",j,"] = <Make:",Make[j][m],", Sell:",Sell[j][m],", Hold:",Hold[j][m],">");
}
 