#include <ql/quantlib.hpp>
#include <iostream>
//#include <boost/test/unit_test.hpp>

using namespace QuantLib;

namespace QuantLib {

    //! %Coupon paying a fixed interest rate
    class OvernightRateCoupon : public Coupon {
      public:
        //! \name constructors
        //@{
        OvernightRateCoupon(const Date& paymentDate,
                            Real nominal,
                            const std::vector<Rate>& interestRates,
                            Real rate_percentage,
                            Spread spread,
                            const Date& accrualStartDate,
                            const Date& accrualEndDate,
                            const Date& refPeriodStart = Date(),
                            const Date& refPeriodEnd = Date(),
                            const Date& exCouponDate = Date()) :
            Coupon(paymentDate, nominal, accrualStartDate, accrualEndDate,
                   refPeriodStart, refPeriodEnd, exCouponDate),
            rates_(interestRates),
            rate_percentage_(rate_percentage),
            spread_(spread)
        {
        }

        Rate rate() const
        {
            return 0.0; //o que retornar aqui??
        }

        Spread spread() const
        {
            return spread_;
        }

        DayCounter dayCounter() const
        {
            return Business252();
        }

        Real accruedAmount(const Date&) const
        {
            return 0.0; //Date::todaysDate();
        }

        Real amount() const {
            auto future_value = nominal();
            auto b_252 = Business252();            

            auto spread = InterestRate(spread_, Business252(), Compounded, Annual).compoundFactor(1/252.);

            for (const auto rate : rates_) {
                auto i = InterestRate(rate * rate_percentage_, Business252(), Compounded, Annual);
                future_value *= i * spread;
            }
        



            //auto brl_calendar = Brazil();
            //auto future_value = nominal();
    
            //for //(auto d = accrualStartDate_; d <= accrualEndDate; d = brl_calendar.advance(d, 1, Days, Following))
           // for (const auto rate : rates_)
           // {
           //     future_value *= ((rate.compoundFactor(1/252.) - 1) * spread_) + 1;
           // }

            return future_value;
        }

      private:
        std::vector<Rate> rates_;
        Real rate_percentage_;
        Spread spread_;
    };
};




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

    std::vector<InterestRate> vec_irates;
    std::transform(rates.begin(), rates.end(), std::back_inserter(vec_irates), InterestRateCDI);
    
    OvernightRateCoupon cdi(today, loan_amount, rates, cdi_percentage, 1.0, today, today, today, today, today);
    std::cout << "my class cdi.amount() is " << std::setprecision(9) << cdi.amount() << std::endl;
    
    std::cout << "future_value = " << std::setprecision(9) << future_value << std::endl;  



}
