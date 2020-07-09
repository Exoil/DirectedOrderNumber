#include <algorithm>

enum DivideType {
	LesserThanZero,
	HaveZero,
	GreaterThanZero
};


class DirectedOrderNumber {

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

	DirectedOrderNumber(DirectedOrderNumber* orderNumber)
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

	DirectedOrderNumber operator+( DirectedOrderNumber toAdd)
	{
		DirectedOrderNumber result((this->infimum + toAdd.infimum), (this->supremum + toAdd.supremum));

		return result;
	}
	DirectedOrderNumber operator-(DirectedOrderNumber toSubstract)
	{
		DirectedOrderNumber result((this->infimum - toSubstract.infimum), (this->supremum - toSubstract.supremum));

		return result;
	}
	DirectedOrderNumber operator*(DirectedOrderNumber toMultiple)
	{
		double* multipleResult;
		multipleResult = new double[4];

		multipleResult[0] = (this->infimum * toMultiple.infimum);
		multipleResult[1] = (this->infimum * toMultiple.supremum);
		multipleResult[2] = (this->supremum * toMultiple.supremum);
		multipleResult[3] = (this->supremum * toMultiple.infimum);
		std::sort(multipleResult, multipleResult + 4);

		DirectedOrderNumber result(multipleResult[0], multipleResult[3]);

		return result;
	}
	DirectedOrderNumber operator/(DirectedOrderNumber toDidive)
	{
		DirectedOrderNumber result(0.0, 0.0);

		if (this->GetDivideType() == GreaterThanZero && toDidive.GetDivideType() == GreaterThanZero)
		{
			result.infimum = this->infimum / toDidive.infimum;
			result.supremum = this->supremum / toDidive.supremum;
		}

		else if (this->GetDivideType() == LesserThanZero && toDidive.GetDivideType() == LesserThanZero)
		{
			result.supremum = this->infimum / toDidive.infimum;
			result.infimum = this->supremum / toDidive.supremum;
		}
		else if (this->GetDivideType() == GreaterThanZero && toDidive.GetDivideType() == LesserThanZero)
		{
			result.infimum = this->supremum / toDidive.infimum;
			result.supremum = this->infimum / toDidive.supremum;
		}
		else if (this->GetDivideType() == LesserThanZero && toDidive.GetDivideType() == GreaterThanZero)
		{
			result.infimum = this->infimum / toDidive.supremum;
			result.supremum = this->supremum / toDidive.infimum;
		}

		else if (this->GetDivideType() == HaveZero && toDidive.GetDivideType() == GreaterThanZero)
		{
			result.infimum = this->infimum / toDidive.supremum;
			result.supremum = this->supremum / toDidive.supremum;
		}

		else if (this->GetDivideType() == HaveZero && toDidive.GetDivideType() == LesserThanZero)
		{
				result.infimum = this->supremum / toDidive.infimum;
				result.supremum = this->infimum / toDidive.infimum;
		}
		else if (toDidive.GetDivideType() == HaveZero)
		{
			DirectedOrderNumber tmp(1.0,1.0);
			
			result = *this / tmp;
			
		}
		return result;
	}
};
	


