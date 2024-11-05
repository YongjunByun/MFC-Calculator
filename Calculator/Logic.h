
class Logic
{
public:
	static Logic& getInstance() {
		static Logic instance; // 沥利 瘤开 函荐肺 教臂沛 按眉 积己
		return instance;
	}
	void set_work_text(CString text);
	CString get_work_text();
	CString get_square_text(CString text); // 力蚌
	CString get_square_root_text(CString text); // 力蚌辟
	CString get_reciprocal_text(CString text); // 开荐
	CString get_percentage_text(CString text);
	void Calculate();
private:
	
	Logic();
	~Logic();
	void set_work_text(double num);

	CString m_work_text;
};
