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

double internalRateOfReturn()
{
    QuantLib::Date today = QuantLib::Date::todaysDate();

    QuantLib::Leg vec_cfs;
    vec_cfs.push_back(shared_ptr<CashFlow>(new SimpleCashFlow(-100, today))); //< payment d0
    vec_cfs.push_back(shared_ptr<CashFlow>(new SimpleCashFlow(10,   today + 1))); //< payment d0 + 1
    vec_cfs.push_back(shared_ptr<CashFlow>(new SimpleCashFlow(110,  today + 2))); //< payment d0 + 2

    Rate yield = CashFlows::yield(vec_cfs,
                                  0.0,
                                  QuantLib::Actual365Fixed(),
                                  QuantLib::Compounded,
                                  QuantLib::Daily,
                                  true,
                                  today,
                                  today);

    yield /= 365.0;
    
    return yield; 
}

int main(int argc, char **argv)
{
    internalRateOfReturn();

    return 0;
}
