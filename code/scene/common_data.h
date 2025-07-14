//===========================================
// 
// シーン間データ保持[common_data.h]
// Auther:UedaKou
// 
//===========================================
#ifndef _COMMON_DATA_H_
#define _COMMON_DATA_H_

namespace Scene {
	class CCommonData
	{
	public:
		CCommonData() {}
		virtual ~CCommonData(){}
		int a = 0;
	private:
	};
}



#endif // !_COMMON_DATA_H_