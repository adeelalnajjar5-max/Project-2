 #include<iostream>
#include<string>
#include<cstdlib>
#include<ctime>

using namespace std;

enum enQuestionLevel { Easy = 1, Med = 2, Hard = 3, MixLevel = 4 };
enum enOperationType { Add = 1, Sub = 2, Mul = 3, Div = 4, MixOperation = 5 };

struct stQuestioninfo
{
	int Num1;
	int Num2;
	short QuestionNumber;
	enQuestionLevel QuestionLevel;
	enOperationType OperationType;
	string strQuestionLevel;
	string OperationName;
	int RightAnswer;
	short NumberofQuestion;
	short NumRightAnswer;
	short NumWrongAnswer;
};

int ReadNumberinRange(string Message, int From, int To)
{
	int Num;
	do
	{
		cout << Message << endl;
		cin >> Num;
	} while (Num < From || Num > To);

	return Num;
}

int ReadPositiveNumber(string Message)
{
	int Num;
	do
	{
		cout << Message << endl;
		cin >> Num;
	} while (Num <= 0);

	return Num;
}
enQuestionLevel ReadQuestionLevel()
{

	return (enQuestionLevel)ReadNumberinRange("Enter Question Level [1] Easy, [2] Med, [3] Hard, [4] MixLevel ?", 1, 4);
}
enOperationType ReadOperationType()
{

	return (enOperationType)ReadNumberinRange("Enter Operation Type [1] Add, [2] Sub, [3] Mul, [4] Div, [5] MixOperation ?", 1, 5);
}


int RandomNumber(int From, int To)
{
	return rand() % (To - From + 1) + From;
}

char OpreationSympol(enOperationType OperationType)
{
	char OperationSympol[4] = { '+','-','*','/' };
	return OperationSympol[OperationType - 1];
}

string QuestionLevel(enQuestionLevel QuestionLevel)
{
	string strQuestionLevel[4] = { "Easy","Med","Hard","Mix" };
	return strQuestionLevel[QuestionLevel - 1];
}

string OperationName(enOperationType OperationType)
{
	string strOperationName[5] = { "Add","Sub","Mul","Div","Mix" };
	return strOperationName[OperationType - 1];
}

enOperationType MixChoiceinOperationType()
{
	return (enOperationType)RandomNumber(1, 4);
}

enQuestionLevel MixChoiceinQuestionLevel()
{
	return (enQuestionLevel)RandomNumber(1, 3);
}

int Calculate(int Num1, int Num2, enOperationType OperationType)
{
	switch (OperationType)
	{
	case enOperationType::Add:
		return (Num1 + Num2);
	case enOperationType::Sub:
		return (Num1 - Num2);
	case enOperationType::Mul:
		return (Num1 * Num2);
	case enOperationType::Div:
		// حماية قصوى: منع القسمة على صفر لكي لا ينهار البرنامج
		if (Num2 == 0) Num2 = 1;
		return (Num1 / Num2);
	default:
		return (Num1 + Num2);
	}
}

stQuestioninfo FellNum1AndNum2ByChoice(enQuestionLevel QuestionLevel, enOperationType OperationType)
{
	stQuestioninfo question;

	if (QuestionLevel == enQuestionLevel::MixLevel)
	{
		QuestionLevel = MixChoiceinQuestionLevel();
	}
	if (OperationType == enOperationType::MixOperation)
	{
		OperationType = MixChoiceinOperationType();
	}

	question.QuestionLevel = QuestionLevel;
	question.OperationType = OperationType;

	switch (QuestionLevel)
	{
	case enQuestionLevel::Easy:
		question.Num1 = RandomNumber(0, 10);
		question.Num2 = RandomNumber(0, 10);
		break;
	case enQuestionLevel::Med:
		question.Num1 = RandomNumber(10, 50);
		question.Num2 = RandomNumber(10, 50);
		break;
	case enQuestionLevel::Hard:
		question.Num1 = RandomNumber(50, 100);
		question.Num2 = RandomNumber(50, 100);
		break;
	}

	// تأكيد عدم وجود صفر في المقام قبل الحساب والطباعة
	if (question.OperationType == enOperationType::Div && question.Num2 == 0)
	{
		question.Num2 = 1;
	}

	question.RightAnswer = Calculate(question.Num1, question.Num2, question.OperationType);
	return question;
}

void PrintQuestion(stQuestioninfo question)
{
	cout << "\n" << question.Num1 << endl;
	cout << question.Num2 << " ";
	cout << OpreationSympol(question.OperationType) << endl;
	cout << "------------------------------" << endl;
}

void QuestionPrintResult(stQuestioninfo question, int Answer)
{
	if (question.RightAnswer == Answer)
	{
		cout << "Right Answer :)" << endl;
		system("color 2F");
	}
	else
	{
		cout << "False Answer :(" << endl;
		cout << "The Right Answer is: " << question.RightAnswer << endl;
		system("color 4F");
		cout << "\a";
	}
}

stQuestioninfo LoopAndFellData()
{
	stQuestioninfo question;

	question.NumRightAnswer = 0;
	question.NumWrongAnswer = 0;

	question.NumberofQuestion = ReadPositiveNumber("How Many Question Do You Want To Answer?");
	question.OperationType = ReadOperationType();
	question.QuestionLevel = ReadQuestionLevel();
  for (question.QuestionNumber = 1; question.QuestionNumber <= question.NumberofQuestion; question.QuestionNumber++)
	{
		cout << "\nQuestion [" << question.QuestionNumber << "/" << question.NumberofQuestion << "]" << endl;
		stQuestioninfo Currentquestion;

		Currentquestion = FellNum1AndNum2ByChoice(question.QuestionLevel, question.OperationType);
		PrintQuestion(Currentquestion);

		int Answer;
		cin >> Answer; // قراءة الإجابة مباشرة وبأمان

		QuestionPrintResult(Currentquestion, Answer);

		if (Currentquestion.RightAnswer == Answer)
		{
			question.NumRightAnswer++;
		}
		else
		{
			question.NumWrongAnswer++;
		}
	}

	question.strQuestionLevel = QuestionLevel(question.QuestionLevel);
	question.OperationName = OperationName(question.OperationType);

	return question;
}

string FinalResultPassOrFail(stQuestioninfo question)
{
	if (question.NumRightAnswer >= question.NumWrongAnswer)
	{
		return  " Pass :)";
	}
	else
	{
		return "Fail :(";
	}
}

void PrintFinalResult(stQuestioninfo question)
{
	cout << "\n\n-------------------------------------------------------------------\n\n";
	cout << "Final Result is " << FinalResultPassOrFail(question) << "\n\n";
	cout << "-------------------------------------------------------------------\n\n";

	cout << "Number of Question : " << question.NumberofQuestion << endl;
	cout << "Question Level     : " << question.strQuestionLevel << endl;
	cout << "Operation Type     : " << question.OperationName << endl;
	cout << "Number of Right Answers : " << question.NumRightAnswer << endl;
	cout << "Number of Wrong Answers : " << question.NumWrongAnswer << endl;

	cout << "\n-------------------------------------------------------------------\n\n";
}
void Reset()
{

	system("cls");
	system("color 0F");
}

void StartGame()
{
	char PlayAgain = 'Y';
	do
	{
		stQuestioninfo Quiz;

		Quiz = LoopAndFellData();
		PrintFinalResult(Quiz);
		cout << "Do You Want Play Again? (Y/N): ";
		cin >> PlayAgain;
		Reset();

	} while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
	srand((unsigned)time(NULL));
	StartGame();


	return 0;

}