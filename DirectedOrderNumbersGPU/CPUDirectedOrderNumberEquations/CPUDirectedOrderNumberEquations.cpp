#include "DirectedOrderNumberOperation.cpp"
#include <iostream>


std::string OptionList() {

	std::string result = "1. Generate Equations Sample.\n";
	result += "2. Gauss Elimination.\n";
	result += "3. Gauss with pivot Elemination.\n";
	result += "4. Gauss Jordan Elemination.\n";
	result += "5. Zaladuj uklad rownan z folderu Sample\n";
	return result;
}



int main()
{	
	int rows = 0;
	DirectedOrderNumber** equation;
	equation = NULL;
	DirectedOrderNumber* vector;
	vector = NULL;
	FileHelper* fileHelper;
	DirectedOrderNumberGenerator* generator;
	DirectedEquationMethod* operations;
	generator = new DirectedOrderNumberGenerator(2, 10, 0.00000001);
	fileHelper = new FileHelper(9);
	int chose = 100;
	std::string fileName, folderName;
	operations = new DirectedEquationMethod(0.00000001);

	std::cout << "Domyslne ustawienia:\nGenerator przedzial podloga 2 sufit 10, precyzja 10^-8\nPrecyzja zapisu wartosci zmiennoprzecinkowej 10^-9\n";
	std::cout << "Wybierz opcje\n";
	while (chose != 0)
	{
		std::cout << OptionList();
		std::cin >> chose;
		switch (chose)
		{
		case 1:

			std::cout << "Podaj ilosc rzedu macierzy\n";
			std::cin >> rows;

			equation = generator->GenerateEquationwithoutFreeValues(rows);
			vector = generator->GenerateSampleVector(rows);
			generator->FillEquationWithFreeValues(equation, vector, rows);

			std::cout << "Wpisz nazwe folderu z przykladem\n";
			std::cin >> folderName;
			fileHelper->CreateEquationFolder(folderName);

			std::cout << "Wpisz nazwe pliku dla ukladu\n";
			std::cin >> fileName;
			fileHelper->SaveEquation(equation, rows, fileName, folderName);

			std::cout << "Wpisz nazwe pliku dla wektora rozwiazan\n";
			std::cin >> fileName;
			fileHelper->SaveVectorToFile(vector, fileName, folderName, rows);
			break;

		case 2:

			vector = operations->GaussElemination(equation, rows);
			std::cout << "Eliminacja Gaussa trwa...\n";
			std::cout << "Wpisz nazwe pliku dla ukladu po eliminacji\n";
			std::cin >> fileName;
			fileHelper->SaveEquation(equation, rows, fileName, folderName);
			std::cout << "Wpisz nazwe pliku dla wektora rozwiazania ukladu rownan\n";
			std::cin >> fileName;
			fileHelper->SaveVectorToFile(vector, fileName, folderName, rows);
			break;
		
		case 3:
		

			vector = operations->GaussEleminationWithPivot(equation, rows);
			std::cout << "Eliminacja Gaussa z Pivtoem trwa...\n";
			std::cout << "Wpisz nazwe pliku dla ukladu po eliminacji\n";
			std::cin >> fileName;
			fileHelper->SaveEquation(equation, rows, fileName, folderName);
			std::cout << "Wpisz nazwe pliku dla wektora rozwiazania ukladu rownan\n";
			std::cin >> fileName;
			fileHelper->SaveVectorToFile(vector, fileName, folderName, rows);
			break;
		case 4:


			vector = operations->GaussJordanElemination(equation, rows);
			std::cout << "Eliminac Gaussa-Jordana\n";
			std::cout << "Wpisz nazwe pliku dla ukladu po eliminacji\n";
			std::cin >> fileName;
			fileHelper->SaveEquation(equation, rows, fileName, folderName);
			std::cout << "Wpisz nazwe pliku dla wektora rozwiazania ukladu rownan\n";
			std::cin >> fileName;
			fileHelper->SaveVectorToFile(vector, fileName, folderName, rows);
			break;
		case 5: 
			std::cout << "Wpisz nazwe folderu z przykladem\n";
			std::cin >> folderName;


			std::cout << "Wpisz nazwe plik z układem\n";
			std::cin >> fileName;
			equation = fileHelper->ReadEquation(fileName, folderName, &rows);
			break;
			
		default:
			chose = 0;
			break;
		}

	}
	if(equation !=NULL)
	{ 
	for (int i = 0; i < 2; i++)
	{
		delete[](equation[i]);
	}
	
	delete[] equation;
	}

	if(vector != NULL)
		delete[] vector;

	delete fileHelper;
	delete generator;

	std::cout << "End\n";
	return 0;
	
}

