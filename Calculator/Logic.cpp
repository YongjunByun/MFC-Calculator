

#include "stdafx.h"
#include "Logic.h"
#include <math.h>
#include <cctype>

void Logic::set_work_text(CString text)
{
	m_work_text = text;
}
// 유한소수인경우 소수점 뒤 '0' 이나 '.' 을 제거시켜줌
void Logic::set_work_text(double num) {
	m_work_text.Format(_T("%f"), num);

	m_work_text.TrimRight('0'); // 끝에 있는 0 제거
	if (m_work_text[m_work_text.GetLength() - 1] == '.') {
		m_work_text.Delete(m_work_text.GetLength() - 1); // 마지막 '.' 제거
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

	// 음수일 경우 제곱근을 계산할 수 없으므로 예외 처리
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
// 후위연산식 고려 안한 문자열 사칙계산
void Logic::Calculate() 
{
	double result = 0.0; 
	double currentNumber = 0.0; 
	char lastOperator = '+';
	bool decimalPoint = false; 
	double decimalFactor = 1.0; // 소수점 위치 조정

	for (int i = 0; i < m_work_text.GetLength(); i++) {
		char ch = m_work_text[i];

		if (std::isdigit(ch)) {
			// 숫자라면 currentNumber에 추가
			if (!decimalPoint) {
				currentNumber = currentNumber * 10 + (ch - '0');
			}
			else {
				decimalFactor *= 10;
				currentNumber += (ch - '0') / decimalFactor;
			}
		}
		else if (ch == '.') {
			// 소수점이 나오면 decimalPoint를 true로 설정
			decimalPoint = true;
		}
		else {
			// 연산자이거나 마지막 문자일 경우 계산 수행
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

			// 현재 연산자를 lastOperator에 저장하고, currentNumber 초기화
			lastOperator = ch;
			currentNumber = 0.0;  // currentNumber 초기화
			decimalPoint = false;  // 소수점 상태 초기화
			decimalFactor = 1.0;   // 소수점 위치 조정 초기화
		}
	}

	// 마지막 숫자 처리
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