/****** Sample output
kuyu@ub16:~/dkuyu/Dropbox/practice/cpp/meyers/item18$ g++ --std=c++14 c.cpp && ./a.out
Investment<T>::Investment(T) [with T = unsigned int]: Initial investment: 100
Investment<T>::Investment(T) [with T = unsigned int]: Initial investment: 200
Investment<T>::Investment(T) [with T = unsigned int]: Initial investment: 300
int main(): pStock: 0x135cc20
int main(): pBond: 0x135d050
int main(): pRealEstate: 0x135d070
makeInvestment(T1, T2)::<lambda(auto:2*)> [with auto:2 = Investment<unsigned int>; T1 = eInvestmentType; T2 = unsigned int]
void makeLogEntry(auto:1*) [with auto:1 = Investment<unsigned int>]: 0x135d070
RealEstate<T>::~RealEstate() [with T = unsigned int]
Investment<T>::~Investment() [with T = unsigned int]
makeInvestment(T1, T2)::<lambda(auto:2*)> [with auto:2 = Investment<unsigned int>; T1 = eInvestmentType; T2 = unsigned int]
void makeLogEntry(auto:1*) [with auto:1 = Investment<unsigned int>]: 0x135d050
Bond<T>::~Bond() [with T = unsigned int]
Investment<T>::~Investment() [with T = unsigned int]
makeInvestment(T1, T2)::<lambda(auto:2*)> [with auto:2 = Investment<unsigned int>; T1 = eInvestmentType; T2 = unsigned int]
void makeLogEntry(auto:1*) [with auto:1 = Investment<unsigned int>]: 0x135cc20
Stock<T>::~Stock() [with T = unsigned int]
Investment<T>::~Investment() [with T = unsigned int]
******/

#include <iostream>
#include <memory>
#include <utility>

enum eInvestmentType
{
	  STOCK       = 1
	, BOND        = 2
	, REAL_ESTATE = 3
};

template <typename T>
class Investment
{
public:
	Investment(T val): initialInvestment(val)
	{
		std::cout << __PRETTY_FUNCTION__ << ": Initial investment: " << initialInvestment << std::endl;
	};

	virtual ~Investment()
	{
		std::cout << __PRETTY_FUNCTION__ << std::endl;
	}

private:
	T initialInvestment = 0;
};

template <typename T>
class Stock : public Investment<T>
{
public:
	Stock(T val): Investment<T>(val) {};

	virtual ~Stock()
	{
		std::cout << __PRETTY_FUNCTION__ << std::endl;
	}
};

template <typename T>
class Bond : public Investment<T>
{
public:
	Bond(T val): Investment<T>(val) {};

	virtual ~Bond()
	{
		std::cout << __PRETTY_FUNCTION__ << std::endl;
	}
};

template <typename T>
class RealEstate : public Investment<T>
{
public:
	RealEstate(T val): Investment<T>(val) {};

	virtual ~RealEstate()
	{
		std::cout << __PRETTY_FUNCTION__ << std::endl;
	}
};

void makeLogEntry(auto* pInv)
{
	std::cout << __PRETTY_FUNCTION__ << ": " << pInv << std::endl;
}

template <typename T1, typename T2>
auto makeInvestment(T1 investmentCode, T2 initialInvestment)
{
	auto delInv =
		[](auto* pInvestment)
		{
			std::cout << __PRETTY_FUNCTION__ << std::endl;
			makeLogEntry(pInvestment);
			delete pInvestment;
		};

	std::unique_ptr<Investment<T2>, decltype(delInv)> pInv(nullptr, delInv);

	if (investmentCode == STOCK)
	{
		pInv.reset(new Stock<T2>(std::forward<T2>(initialInvestment)));
	}
	else if (investmentCode == BOND)
	{
		pInv.reset(new Bond<T2>(std::forward<T2>(initialInvestment)));
	}
	else if (investmentCode == REAL_ESTATE)
	{
		pInv.reset(new RealEstate<T2>(std::forward<T2>(initialInvestment)));
	}
	else
	{
		std::cout << "ERROR: Unrecognized investment type: " << investmentCode << std::endl;
	}

	return pInv;
}

int main()
{
	auto pStock      = makeInvestment(STOCK,       static_cast<unsigned int>(100));
	auto pBond       = makeInvestment(BOND,        static_cast<unsigned int>(200));
	auto pRealEstate = makeInvestment(REAL_ESTATE, static_cast<unsigned int>(300));

	std::cout << __PRETTY_FUNCTION__ << ": pStock: "      << pStock.get()      << std::endl;
	std::cout << __PRETTY_FUNCTION__ << ": pBond: "       << pBond.get()       << std::endl;
	std::cout << __PRETTY_FUNCTION__ << ": pRealEstate: " << pRealEstate.get() << std::endl;

	return 0;
}
