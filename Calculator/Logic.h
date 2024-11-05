
class Logic
{
public:
	static Logic& getInstance() {
		static Logic instance; // ���� ���� ������ �̱��� ��ü ����
		return instance;
	}
	void set_work_text(CString text);
	CString get_work_text();
	CString get_square_text(CString text); // ����
	CString get_square_root_text(CString text); // ������
	CString get_reciprocal_text(CString text); // ����
	CString get_percentage_text(CString text);
	void Calculate();
private:
	
	Logic();
	~Logic();
	void set_work_text(double num);

	CString m_work_text;
};
