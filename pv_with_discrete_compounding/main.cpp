#include <iostream>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <ql/cashflows/cashflows.hpp>
#include <ql/cashflows/simplecashflow.hpp>
#include <ql/time/daycounters/actual365fixed.hpp>
#include <ql/interestrate.hpp>
#include <ql/time/date.hpp>
#include <ql/time/frequency.hpp>

using namespace boost;
using namespace QuantLib;

double presentValueWithDiscreteCompounding()
{  
    // Instead of use the t = 0, 1, 2 ... N as the discrete dates, let's use todays date as reference 
    QuantLib::Date today = QuantLib::Date::todaysDate();

    // The struct below represents the future payments on a certain dates.
    QuantLib::Leg vec_cfs;
    vec_cfs.push_back(shared_ptr<CashFlow>(new SimpleCashFlow(-100, today))); //< payment d0
    vec_cfs.push_back(shared_ptr<CashFlow>(new SimpleCashFlow(75,   today + 1))); //< payment d0 + 1
    vec_cfs.push_back(shared_ptr<CashFlow>(new SimpleCashFlow(75,   today + 2))); //< payment d0 + 2
 
    // the insterest rate is constant for all periods, so it's termed flat term structure.
    double ir_value = 0.1;  
    InterestRate interest_rate(ir_value * 365.0, //< annual percentage rate,
                               QuantLib::Actual365Fixed(), //< according with the annualised interest rate.
                               QuantLib::Compounded, //< http://en.wikipedia.org/wiki/Compound_interest
                               QuantLib::Daily); //< the interest rate is applied every day.    


    double value = CashFlows::npv(vec_cfs,
                                  interest_rate,
                                  true);
    
    //std::cout << "Present value, " << ir * 100 << " percent discretely compounded interest = " << value << std::endl;
    return value;
}

int main(int argc, char **argv)
{
    presentValueWithDiscreteCompounding();

    return 0;
}
