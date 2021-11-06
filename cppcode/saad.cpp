#include <iostream>
#include<string>
#include<fstream>
using namespace std;
ofstream outputfile;
ifstream inputfile;
bool is_Letter(char ch);
bool is_Digit(char ch);
bool is_Delimeter(char ch);
void Lexical(string str);

int main()
{
	inputfile.open("input.txt",ios::in);
	string number;
	string input;
	while(!inputfile.eof())
	{
		inputfile>>number;
		input=input+number;
		input+=" ";
	}
	Lexical(input);
}

bool is_Letter(char ch)
{
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || ch == '_')
		return true;
	else
		return false;
}
bool is_Digit(char ch)
{
	if ((ch >= '0' && ch <= '9'))
		return true;
	else
		return false;
}
bool is_Delimeter(char ch)
{
	if (ch == ' ' || ch == '\t' || ch == '\n')
		return true;
	else
		return false;
}


void Lexical(string str)
{
	outputfile.open("output.txt",ios::out);
	int state = 0;
	int i = 0;
	string lexeme = "";
	int flag = 1;
	char c = '\0';

	while (str[i] != '\0')
	{
		c = str[i];
		flag = 1;
		switch (state)
		{
		case 0:
			if (is_Letter(c))
			{
				if (str[i + 1] == '\0')
				{
					lexeme = lexeme + c;
					outputfile << "Tokken < " << " ID , " << lexeme << " > " << endl;
				}
				else
				{
					state = 1;
				}
			}
			else if (is_Digit(c))
			{
				if (str[i + 1] == '\0')
				{
					lexeme = lexeme + c;
					outputfile << "Tokken < " << " IL , " << lexeme << " > " << endl;
				}
				else
				{
					state = 2;
				}
			}
			else if (c == '=')
			{
				if (str[i + 1] == '\0')
				{
					lexeme = lexeme + c;
					outputfile << "Tokken < " << " AS , " << lexeme << " > " << endl;
				}
				else
				{
					state = 5;
				}
			}
			else if (c == '+')
			{

				if (str[i + 1] == '\0')
				{
					lexeme = lexeme + c;
				    outputfile << "Tokken < " << " PLUS , " << lexeme << " > " << endl;
				}
				else
				{
					state = 4;
				}
			}
			else if (c == ';')
			{
				state = 0;
				lexeme = c;
				outputfile<< "Tokken < " << " SC , " << lexeme << " > " << endl;
				lexeme = "";
				flag = 0;
			}
			else if (c == '/')
			{
				if (str[i + 1] == '/')
				{
					state = 7;
				}
				else if (str[i + 1] == '*')
				{
					state = 8;
				}
				else
				{
					state = 0;
					lexeme = c;
					outputfile << "Tokken < " << " DIV , " << lexeme << " > " << endl;
					lexeme = "";
					flag = 0;
				}
			}
			else if (c == '!')
			{
				state = 0;
				lexeme = c;
				outputfile << "Tokken < " << " NOT , " << lexeme << " > " << endl;
				lexeme = "";
				flag = 0;
			}
			else if (c == '&')
			{
				state = 0;
				lexeme = c;
				outputfile<< "Tokken < " << " AND , " << lexeme << " > " << endl;
				lexeme = "";
				flag = 0;
			}
			else if (c == '*')
			{
					state = 0;
					lexeme = c;
					outputfile<< "Tokken < " << " MUL , " << lexeme << " > " << endl;
					lexeme = "";
					flag = 0;
			}
			else if (c == '<')
			{
				if (str[i + 1] == '\0')
				{
					lexeme = lexeme + c;
					outputfile<< "Tokken < " << " LT , " << lexeme << " > " << endl;
				}
				else
				{
					state = 3;
				}
			}
			else if (c == '>')
			{
				state = 0;
				lexeme = c;
				outputfile<< "Tokken < " << " GT , " << lexeme << " > " << endl;
				lexeme = "";
				flag = 0;
			}
			else if (c == '"')
			{
			    state = 0;
			}
			else if (c == '-')
			{
				if (str[i + 1] == '\0')
				{
					lexeme = lexeme + c;
					outputfile<< "Tokken < " << " MINUS , " << lexeme << " > " << endl;
				}
				else
				{
					state = 6;
				}
			}
			else if (c == '{' || c == '(' || c == '[')
			{
				state = 0;
				lexeme = c;
				outputfile<< "Tokken < " << " OP , " << lexeme << " > " << endl;
				lexeme = "";
				flag = 0;
			}
			else if (c == '}' || c == ')' || c == ']')
			{
				state = 0;
				lexeme = c;
				outputfile<< "Tokken < " << " CP , " << lexeme << " > " << endl;
				lexeme = "";
				flag = 0;
			}
			else if (is_Delimeter(c))
			{
				flag = 0;
			}
			else
			{
				outputfile<< " Invalid Tokken " << endl;
				break;
			}

			break;
		case 1:
			if (c == '"')
			{
				state = 0;
				lexeme = lexeme + c;
				outputfile<< "Tokken < " << " SL , " << lexeme << " > " << endl;
				lexeme = "";
				continue;
			}
			if (!(is_Letter(c) || is_Digit(c)))
			{

				state = 0;
				if (lexeme == "int" || lexeme == "main" || lexeme == "float" || lexeme == "double" || lexeme == "char" || lexeme == "if" || lexeme == "while" || lexeme == "for" || lexeme == "break" || lexeme == "switch" || lexeme == "case")
				{
					outputfile<< "Tokken < " << " KW , " << lexeme << " > " << endl;
				}
				else
				{
					outputfile<< "Tokken < " << " ID , " << lexeme << " > " << endl;
				}
				lexeme = "";
				continue;
			}
			break;

		case 2:
			if (!is_Digit(c))
			{
				state = 0;
				outputfile<< "Tokken < " << " IL , " << lexeme << " > " << endl;
				lexeme = "";
				continue;
			}
			break;

		case 3:
			if (c == '=')
			{
				state = 0;
				lexeme = lexeme + c;
				outputfile<< "Tokken < " << " LE , " << lexeme << " > " << endl;
				lexeme = "";
				flag = 0;
			}
			else
			{
				state = 0;
				outputfile<< "Tokken < " << " LT , " << lexeme << " > " << endl;
				lexeme = "";
				i++;
				continue;
			}
			break;

		case 4:
			if (c == '+')
			{
				state = 0;
				lexeme = lexeme + c;
				outputfile<< "Tokken < " << " INC , " << lexeme << " > " << endl;
				lexeme = "";
				flag = 0;
			}
			else
			{
				state = 0;
				outputfile<< "Tokken < " << " Plus , " << lexeme << " > " << endl;
				lexeme = "";
				continue;
			}
			break;
		case 5:
			if (c == '=')
			{
				state = 0;
				lexeme = lexeme + c;
				outputfile<< "Tokken < " << " COM , " << lexeme << " > " << endl;
				lexeme = "";
			}
			else
			{
				state = 0;
				outputfile<< "Tokken < " << " AS , " << lexeme << " > " << endl;
				lexeme = "";
				continue;
			}
			break;
		case 6:
			if (c == '-')
			{
				state = 0;
				lexeme = lexeme + c;
				outputfile << "Tokken < " << " DEC , " << lexeme << " > " << endl;
				lexeme = "";


			}
			else
			{
				state = 0;
				outputfile<< "Tokken < " << " MINUS , " << lexeme << " > " << endl;
				lexeme = "";
				continue;
			}
			break;
		case 7:
			if (str[i+1]=='\0')
			{
				state = 0;
				lexeme = lexeme + c;
				outputfile<< "Tokken < " << " SLC , " << lexeme << " > " << endl;
				lexeme = "";
				flag = 0;
			}
			break;
		case 8:
			if (!(is_Letter(c) || is_Digit(c)))
			{
				if (c == '*')
				{
					lexeme = lexeme + c;
					if (str[i + 1] == '/')
					{
						c = str[i + 1];
						state = 0;
						lexeme = lexeme + c;
						outputfile<< "Tokken < " << " MLC , " << lexeme << " > " << endl;
						i++;
						lexeme = "";
						flag = 0;
					}
				}
			}
			break;
		}
		if (flag)
			lexeme = lexeme + c;

		i++;
	}
	outputfile.close();
}

