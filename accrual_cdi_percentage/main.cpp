#include <ql/quantlib.hpp>
#include <iostream>
//#include <boost/test/unit_test.hpp>

using namespace QuantLib;

int main() {
    auto cdi_percentage = 0.85;

    Real loan_amount = 1000.0;
    std::vector<Rate> rates = {0.1207, 0.1206, 0.1213, 0.1213, 0.1213, 0.1212};
    Date today = Date::todaysDate();
    
    auto InterestRateCDI = [](Real value) { 
        return  InterestRate(value, Business252(), Compounded, Annual);
    };

    auto brl_calendar = Brazil();
    Real future_value = loan_amount;
 
    for (auto t = 0; t < rates.size(); ++t)
    {
        future_value *= ((InterestRateCDI(rates[t]).compoundFactor(1/252.) - 1) * cdi_percentage) + 1;
        
/*
        Date reference_date = brl_calendar.advance(today, t, Days, Following);
        Date payment_date =  brl_calendar.advance(reference_date, 1, Days, Following);
        FixedRateCoupon loan(payment_date, loan_amount, InterestRateCDI(rates[t]), reference_date, payment_date);

        std::cout << std::setprecision(9) << 
            "taxa ao dia = " <<  InterestRateCDI(rates[t]).compoundFactor(1/252.) << "\t" << 
            "fator = " <<  (InterestRateCDI(rates[t]).compoundFactor(1/252.)-1) * (0.85) << "\t" << 
            "result = " << loan.accruedAmount(payment_date) * cdi_percent <<  std::endl;

        future_value += loan.accruedAmount(payment_date) * cdi_percent;
        
//        std::cout << "accrued = " << loan.accruedAmount(payment_date) << std::endl;
//        */
    }
    
    std::cout << "future_value = " << std::setprecision(9) << future_value << std::endl;  



}
