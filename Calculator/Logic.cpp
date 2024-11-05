

#include "stdafx.h"
#include "Logic.h"
#include <math.h>
#include <cctype>

void Logic::set_work_text(CString text)
{
	m_work_text = text;
}
// ���ѼҼ��ΰ�� �Ҽ��� �� '0' �̳� '.' �� ���Ž�����
void Logic::set_work_text(double num) {
	m_work_text.Format(_T("%f"), num);

	m_work_text.TrimRight('0'); // ���� �ִ� 0 ����
	if (m_work_text[m_work_text.GetLength() - 1] == '.') {
		m_work_text.Delete(m_work_text.GetLength() - 1); // ������ '.' ����
	}
}
CString Logic::get_work_text()
{
	return m_work_text;
}
CString Logic::get_square_text(CString text)
{
	double currentNumber = 0.0;
	currentNumber = _ttof(text);

	double Root = pow(currentNumber, 2);

	set_work_text(Root);
	return m_work_text;
}
CString Logic::get_square_root_text(CString text)
{
	double currentNumber = 0.0;
	currentNumber = _ttof(text);

	// ������ ��� �������� ����� �� �����Ƿ� ���� ó��
	if (currentNumber < 0) {
		m_work_text.Format(_T("ERROR"));
		return m_work_text;
	}

	double squareRoot = sqrt(currentNumber);

	set_work_text(squareRoot);
	return m_work_text;

}
CString Logic::get_reciprocal_text(CString text)
{
	double currentNumber = 0.0;
	currentNumber = _ttof(text);

	double reciprocal = 1 / currentNumber;

	set_work_text(reciprocal);
	return m_work_text;
}
CString Logic::get_percentage_text(CString text)
{
	double currentNumber = 0.0;
	currentNumber = _ttof(text);

	double percentage = currentNumber / 100.0;

	set_work_text(percentage);
	return m_work_text;
	return CString();
}
// ��������� ��� ���� ���ڿ� ��Ģ���
void Logic::Calculate() 
{
	double result = 0.0; 
	double currentNumber = 0.0; 
	char lastOperator = '+';
	bool decimalPoint = false; 
	double decimalFactor = 1.0; // �Ҽ��� ��ġ ����

	for (int i = 0; i < m_work_text.GetLength(); i++) {
		char ch = m_work_text[i];

		if (std::isdigit(ch)) {
			// ���ڶ�� currentNumber�� �߰�
			if (!decimalPoint) {
				currentNumber = currentNumber * 10 + (ch - '0');
			}
			else {
				decimalFactor *= 10;
				currentNumber += (ch - '0') / decimalFactor;
			}
		}
		else if (ch == '.') {
			// �Ҽ����� ������ decimalPoint�� true�� ����
			decimalPoint = true;
		}
		else {
			// �������̰ų� ������ ������ ��� ��� ����
			if (lastOperator == '+') {
				result += currentNumber;
			}
			else if (lastOperator == '-') {
				result -= currentNumber;
			}
			else if (lastOperator == 'x') {
				result *= currentNumber;
			}
			else if (lastOperator == '/') {
				result /= currentNumber;
			}

			// ���� �����ڸ� lastOperator�� �����ϰ�, currentNumber �ʱ�ȭ
			lastOperator = ch;
			currentNumber = 0.0;  // currentNumber �ʱ�ȭ
			decimalPoint = false;  // �Ҽ��� ���� �ʱ�ȭ
			decimalFactor = 1.0;   // �Ҽ��� ��ġ ���� �ʱ�ȭ
		}
	}

	// ������ ���� ó��
	if (lastOperator == '+') {
		result += currentNumber;
	}
	else if (lastOperator == '-') {
		result -= currentNumber;
	}
	else if (lastOperator == 'x') {
		result *= currentNumber;
	}
	else if (lastOperator == '/') {
		result /= currentNumber;
	}
	set_work_text(result);
}

Logic::Logic()
{
	
}


Logic::~Logic()
{
}