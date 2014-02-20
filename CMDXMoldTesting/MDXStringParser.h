#pragma once

class CMDXStringParser
{
public:
    CMDXStringParser(void);
    virtual ~CMDXStringParser(void);

public:
    //
    bool IsRealParse(const char* lpszText);
    bool SimpleFloatParse(const char* lpszText, double &dValue);
	CString GetTableString(UINT iStringID);
	void ShowWarningMessage(CDataExchange *pDX, UINT nEditID, CString strMsg);
};
