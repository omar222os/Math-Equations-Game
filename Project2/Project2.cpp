#include <iostream>
using namespace std;

enum enQLevel
{
    Easy=1,Mid , Hard , mix
};

enum enQType
{
    Add=1 , Sub , Mul , Div , Mix
};

int ReadNumber()
{
	int num;
	cin >> num;
	return num;
}
int ReadPositiveNumber(string massege)
{
	int n;
	do
	{
		cout << massege ;
		cin >> n;
	} while (n < 0);
	return n;
}

enQLevel ReadQuestionsLevel()
{
	short level;
	do
	{
		cout << "Enter Questions level [1] Easy, [2] Med, [3] Hard, [4] Mix ? ";
		cin >> level;
	} while (level > 4 || level < 1);
	return enQLevel(level);
}

enQType ReadQuestionsType()
{
	short type;
	do
	{
		cout << "Enter Questions Type [1] Add, [2] Sub, [3] Mul, [4] Div, [5] Mix ? ";
		cin >> type;
	} while (type > 5 || type < 1);
	return enQType(type);
}

struct FinalResult
{
	int NumberOfQuestions;
	string Questionslevel;
	string QuestionsType;
	int NumberOfWrongAnswers = 0;
	int NumberOfWrightAnswers = 0;

};

void FillFinalResult(enQLevel level, enQType type, int NumberOfQuestions, FinalResult &result)
{
	string levels[4] = { "Easy", "Mid" ,"Hard","Mix" };
	string Types[5] = { "+","-","*","/","Mix" };
	result.NumberOfQuestions = NumberOfQuestions;
	result.Questionslevel = levels[level-1];
	result.QuestionsType = Types[type-1];
}

int RandomNumber(int From, int To)
{
	int randNum = rand() % (To - From + 1) + From;
	return randNum;
}

void PrintQuestionNumber(short number, short TotalNumber)
{
    cout << "Question [" << number << "/" << TotalNumber << "]\n";
}

void PrintDivider()
{
	cout << "----------------------\n";
}

void PrintLongDivider()
{
	cout << "----------------------------------------------\n\n";
}

int CalcAnswer(int num1, int num2, char op)
{
	switch (op)
	{
	case '+':
		return num1 + num2;
	case '-':
		return num1 - num2;
	case '*':
		return num1 * num2;
	case '/':
		return num1 / num2;
	}
}
int PrintQuestions(enQType, enQLevel);
void PrintMixQuestions(enQType type)
{
	enQLevel  level = enQLevel(RandomNumber(1, 3));
	PrintQuestions(type, level);

}


int GetEquation(enQLevel level, enQType type)
{
	if (type == Mix)
		type = enQType(RandomNumber(1, 4));
	char operations[] = { '+','-','*','/' };
	int num1, num2;
	switch (level)
	{
	case Easy:
		 num1 = RandomNumber(1, 10), num2 = RandomNumber(1, 10);
		cout << num1 << endl << num2 << " " << operations[type - 1] << "\n\n";
		return CalcAnswer(num1,num2,operations[type-1]);

	case Mid:
		 num1 = RandomNumber(10, 50), num2 = RandomNumber(10, 50);
		cout << num1 << endl << num2 << " " << operations[type - 1] << "\n\n";
		return CalcAnswer(num1, num2, operations[type - 1]);
	case Hard:
		 num1 = RandomNumber(50, 100), num2 = RandomNumber(50, 100);
		cout << num1 << endl << num2 << " " << operations[type - 1] << "\n\n";
		return CalcAnswer(num1, num2, operations[type - 1]);
	

	}
}

int PrintQuestions(enQType type , enQLevel level)
{
	int Answer;
	switch (level)
	{
	case Easy:
		Answer =GetEquation(Easy, type);
		PrintDivider();
		return Answer;
	case Mid:
		Answer = GetEquation(Mid, type);
		PrintDivider();
		return Answer;
	case Hard:
		Answer = GetEquation(Hard, type);
		PrintDivider();
		return Answer;
	case mix:
		enQLevel mex = enQLevel(RandomNumber(1, 3));
		int Answer = GetEquation(mex, type);
		PrintDivider();
		return Answer;
	
	}
}

void ColorTheConsole(bool CorrecAnswer)
{
	if (CorrecAnswer)
		system("color 2F");
	else
		system("color 4F");	
}

void PrintWrongAnswer(int writghtAnswer)
{
	cout << "Wrong Answer :-(\n";
	cout << "The Wright answer is " << writghtAnswer << endl;
}


void PrintFinalResult(FinalResult result)
{
	PrintLongDivider();
	if (result.NumberOfWrightAnswers >= result.NumberOfWrongAnswers)
		cout << "  Final Result if PASS :-)\n\n";
	else
		cout <<"\a" << "  Final Result if FAIL :-(\n\n";
	PrintLongDivider();


	cout << "Number of Questions : " << result.NumberOfQuestions << endl;
	cout << "Questions Level     : " << result.Questionslevel << endl;
	cout << "OpType              : " << result.QuestionsType << endl;
	cout << "Number of Wright Answers : " << result.NumberOfWrightAnswers << endl;
	cout << "Number of Wrong Answers  : " << result.NumberOfWrongAnswers << endl;
	PrintLongDivider();
}

void PlayTheGame()
{
	int NumberOfQuestions = ReadPositiveNumber("Enter the number of questions you want? ");
	enQLevel level = ReadQuestionsLevel();
	enQType typeOfQuestions = ReadQuestionsType();
	FinalResult result;
	int ModelAnswer, PlayerAnswer; 
	for (int i = 0; i < NumberOfQuestions; i++)
	{
		PrintQuestionNumber(i + 1, NumberOfQuestions);
		ModelAnswer = PrintQuestions(typeOfQuestions, level);
		PlayerAnswer = ReadNumber();
		if (PlayerAnswer == ModelAnswer)
		{
			cout << "Right Answer :-)\n";
			result.NumberOfWrightAnswers++;
			ColorTheConsole(1);
		}
		else
		{
			PrintWrongAnswer(ModelAnswer);
			result.NumberOfWrongAnswers++;
			ColorTheConsole(0);
		}
		

		cout << endl;

	}
	FillFinalResult(level, typeOfQuestions, NumberOfQuestions,result);
	PrintFinalResult(result);


}

char AskToPlayAgain()
{
	char playAgain;
	cout << "Do you want to play again? Y/N? ";
	cin >> playAgain;
	return tolower(playAgain);
}

void RestartGame()
{
	
	system("cls");
	system("color 0F");	
}

void StartTheGame()
{
	char PlayAgain;
	do
	{
		PlayTheGame();
		PlayAgain = AskToPlayAgain();
		if (PlayAgain == 'y')
			RestartGame();
	} while (PlayAgain == 'y');

}

int main()
{
	srand((unsigned)time(NULL));
	StartTheGame();

    return 0;
}

