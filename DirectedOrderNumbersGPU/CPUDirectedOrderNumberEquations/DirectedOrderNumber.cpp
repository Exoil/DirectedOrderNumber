#include <string>


enum DivideType
{
	LesserThanZero,
	HaveZero,
	GreaterThanZero
};
class DirectedOrderNumber
{
public:
	double infimum, supremum;
	bool zeroFlag;
	
	DirectedOrderNumber()
	{
		infimum = 0.0;
		supremum = 0.0;
		zeroFlag = false;
	}

	DirectedOrderNumber(const DirectedOrderNumber& that)
	{
		infimum = that.infimum;
		supremum = that.supremum;
		zeroFlag = false;
	}  

	DirectedOrderNumber(double newInfimum, double newSupremum)
	{
		infimum = double(newInfimum);
		supremum = double(newSupremum);
		zeroFlag = false;
	}

	DirectedOrderNumber(DirectedOrderNumber *orderNumber)
	{
		infimum = orderNumber->infimum;
		supremum = orderNumber->supremum;
		zeroFlag = orderNumber->zeroFlag;
	}

	void SetValues(double newInf, double newSup)
	{
		infimum = newInf;
		supremum = newSup;
		zeroFlag = false;
	}

	double GetRealNumber()
	{
		return (infimum + supremum) / 2.0;
	}

	double GetAbsoulteRealNumber()
	{
		double result = (infimum + supremum) / 2.0;

		if (result < 0)
			return -1 * result;

		else
			return result;
	}


	std::string ToString()
	{
		std::string outPut = "("+std::to_string(infimum)+","+std::to_string(supremum)+")";
		return outPut;
	}


	DivideType GetDivideType()
	{
		if (infimum > 0.0 && supremum > 0.0)
		{
			return GreaterThanZero;
		}

		else if (infimum < 0.0 && supremum < 0.0)
		{
			return LesserThanZero;
		}
		else
		{
			return HaveZero;
		}
	}

	DirectedOrderNumber operator+(DirectedOrderNumber &second)
	{
		this->infimum += second.infimum;
		this->supremum += second.supremum;

		return this;
	}

};
