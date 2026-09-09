#ifndef eDSpread_h__
#define eDSpread_h__

// Doxygen code user manual //
/*!
\page eDSpread eDSpread 
\brief <STRONG> Модуль ... </STRONG>

<BLOCKQUOTE>
\brief \b Функционал \b модуля. 
Модуль реализует ...

</BLOCKQUOTE>

<BLOCKQUOTE>
\par Параметры
- \b ValFilePath - Путь к файлу значений (формат файла: 31;txt1;12.2;txt2;70:0.1:71).
- \b Multiplier - Множитель числового выходного значения (дробн.).
- \b Addition - Аддитивная добавка числового выходного значения (дробн.).
- \b FlagCycledValues - Флаг зацикливания вектора значений.
- \b Values - Описание списка значений, используется при работе без файла (формат: 31;txt1;12.2;txt2;70:0.1:71).
- \b FlagGetValue - Флаг генерации нового выходного значения в сообщении NewValue.
- \b Value - Базовое значение, используется при работе через установку параметра (сообщение NewValue выдается на следующем цикле).
</BLOCKQUOTE>

<BLOCKQUOTE>
\par Сообщения
- \b NewValue - Новое значение.
- \b AllValues - Все значения отправлены.
- \b InitValues - Новые значения инициализированы (количество значений).
</BLOCKQUOTE>
\n
*/

#include "../../include/e_base_defs.h"
#include "../../include/boost/boost_base_defs.h"
#include "../../include/api/BFileDevice.h"
#include "../../include/e_types_plus.h"
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>

// Минимальный размер буфера входного интерфейса
#define IN_BUF_0_MIN_LEN 1
// Минимальный размер буфера выходного интерфейса
#define OUT_BUF_0_MIN_LEN 1
// Коэффициент отношения размеров входа и выхода
#define IN_OUT_0_K 1.0

const unsigned char InputByte[256] = {
	0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
	0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f,
	0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f,
	0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x3e, 0x3f,
	0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f,
	0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5a, 0x5b, 0x5c, 0x5d, 0x5e, 0x5f,
	0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e, 0x6f,
	0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7a, 0x7b, 0x7c, 0x7d, 0x7e, 0x7f,
	0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f,
	0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9a, 0x9b, 0x9c, 0x9d, 0x9e, 0x9f,
	0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf,
	0xb0, 0xb1, 0xb2, 0xb3, 0xb4, 0xb5, 0xb6, 0xb7, 0xb8, 0xb9, 0xba, 0xbb, 0xbc, 0xbd, 0xbe, 0xbf,
	0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf,
	0xd0, 0xd1, 0xd2, 0xd3, 0xd4, 0xd5, 0xd6, 0xd7, 0xd8, 0xd9, 0xda, 0xdb, 0xdc, 0xdd, 0xde, 0xdf,
	0xe0, 0xe1, 0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7, 0xe8, 0xe9, 0xea, 0xeb, 0xec, 0xed, 0xee, 0xef,
	0xf0, 0xf1, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7, 0xf8, 0xf9, 0xfa, 0xfb, 0xfc, 0xfd, 0xfe, 0xff,
};


uchar *CodedByte[256];

static TModuleDescr g_description(
	STR("eDSpread"),
	STR("Модуль ...\n"
		"Формат ...\n"
		"..."),
	STR("ES Group"), 
	STR("0.0.0.1")
	// Версия модуля X.Y.Z.W (для файла конфигурации тракта значимыми являются только первые две цифры - X.Y)
	// X - концептуальные изменения, изменение интерфейсов модуля 
	// Y - функциональные изменения, изменение параметров
	// Z - исправление ошибок, доработка алгоритмов работы
	// W - номер сборки
);

class CeDSpread
{
private:
	TModuleContext m_info;
	struct TParam
	{
		enum Param
		{
			m_strCodeSequence,
			Preambl
		};
	};

	int	m_iSequenceLen;
	string_type m_strValues, m_strValue;
	bool m_flagGetValue, m_flagCycledValues, m_flagInitValues, m_flagAllValues;
	string_type m_strSequenceFilePath;

	string_type m_sPreambl;
	int	m_iPreamblLen;
	std::vector<std::vector<uchar>> m_vvucPreambul1;// преамбула для 1
	std::vector<std::vector<uchar>> m_vvucPreambul0;// преамбула для 0
	std::vector<uchar> m_vucPmb1;
	std::vector<uchar> m_vucPmb0;
	std::vector<std::vector<uchar>> m_vucPmbMask;

	std::string m_out0, m_out1;

	std::vector<bool> m_vflagValsIsTxt;
	std::vector<double> m_vdVals;
	std::vector<string_type> m_vstrValsTxt;
	size_t m_nValInd;
	float m_dValue;
	int m_ihextoDec(std::string& hex);

public:
	CeDSpread()
	{
		m_sPreambl = string_type(STR("aa"));
		m_iPreamblLen = 0;

		m_info.AddParam(TParam::Preambl, STR("Preambl"), STR("Преамбулы HEX(преамбулы перечисляются через запятую(пример 11111,aaaaaa)), байт ** - любой байт."), m_sPreambl);
		m_info.descr = g_description;

        // Инициализируем матрицу коммутации - (вход)x(выход)
        m_info.matrix.SetInOutCount(1, 1);
        m_info.matrix.SetCell(0, 0, IN_OUT_0_K);

        // Инициализируем минимальный размер входных-выходных буферов
        m_info.matrix.in_buffers.at(0) = IN_BUF_0_MIN_LEN;

        m_info.matrix.out_buffers.at(0) = OUT_BUF_0_MIN_LEN;
		
	}
	~CeDSpread() {}

	int Init(const TModuleContext* pContext)
	{
		m_sPreambl.clear();
		m_vflagValsIsTxt.clear();
		m_vdVals.clear();
		m_flagAllValues = false;
		m_flagInitValues = false;
		m_nValInd = 0;
		m_dValue = 0.;
		std::locale::global(std::locale(""));
		if (!pContext->parameters.empty())
		{
			m_info.SetModuleContext(pContext);

			if (m_info.CheckParam(TParam::Preambl))
				m_sPreambl = m_info.GetParamData(TParam::Preambl);
		}

		boost::algorithm::replace_all(m_sPreambl, STR(" "), "");
		std::vector<std::string> vsPmb;
		boost::algorithm::split(vsPmb, m_sPreambl, boost::is_any_of(","), boost::token_compress_on);
		m_vvucPreambul1.resize(vsPmb.size());
		m_vucPmbMask.resize(vsPmb.size());

		for (int i = 0; i < (int)vsPmb.size(); i++)
		{
			string_type strPmb = str_utils::aToLocal(vsPmb[i].data());
			HexStringToBytes(strPmb, m_vvucPreambul1[i], m_vucPmbMask[i]);
			if ((int)m_vvucPreambul1[i].size() >= m_iPreamblLen)
			{
				m_iPreamblLen = (int)m_vvucPreambul1[i].size();
			}
		}

		if (m_vvucPreambul1.size() > 1) {// расчет на то, что на вход подастся не больше двух преамбул, например 11111,aaaaaa
			m_vucPmb1 = m_vvucPreambul1[0];
			m_vucPmb0 = m_vvucPreambul1[1];
		}
		else {
			m_vucPmb1.resize(m_vvucPreambul1[0].size());
			m_vucPmb0.resize(m_vvucPreambul1[0].size());
			m_vucPmb1 = m_vvucPreambul1[0];
			for (int i = 0; i < m_vucPmb1.size(); ++i) {
				m_vucPmb0[i] = (0xff - m_vucPmb1[i]);
			}
		}
		size_t sizePout = m_iPreamblLen * 8;
		for (int i = 0x00; i <= 0xFF; i++) {
			uchar* pOut = (unsigned char*)malloc(sizePout * sizeof(unsigned char));
			memset(pOut, 0, sizePout);
			// Обработка каждого бита
			for (int ii = 0; ii < 8; ii++) {
				if (((i >> ii) & 0x01) == 0x00)
				{
					memcpy(pOut + m_iPreamblLen * (7 - ii), m_vucPmb0.data(), m_iPreamblLen);
				}
				else {
					memcpy(pOut + m_iPreamblLen * (7 - ii), m_vucPmb1.data(), m_iPreamblLen);
				}	
			}
			CodedByte[i] = pOut;
		}
		// Инициализируем матрицу коммутации (вход)x(выход) в зависимости от SequenceLen__________________________(SequenceLen не инициализируется, вместо него IN_OUT_0_K)
        m_info.matrix.SetCell(0, 0, IN_OUT_0_K * 8 * m_iPreamblLen);


		


		//алгоритм сюда
		return ModuleError::Ok;
	}

	int Work(BDataList& inDataList, BDataList& outDataList)
	{
		int iLen = inDataList.at(0)->RealLength();
		unsigned char* Indata = inDataList.at(0)->Data();
		unsigned char* OutData = outDataList.at(0)->Data();
		size_t sizePout = m_iPreamblLen * 8; // Добавляем
		for (int ii = 0; ii < iLen; ii++) {
			memcpy(OutData + ii * sizePout, CodedByte[Indata[ii]], sizePout);
		}
		outDataList.at(0)->SetRealLength(iLen * sizePout); // Исправлено
		return ModuleError::NoDataForProcess;
	}



	int Apply(const TModuleParam* pParam)
	{ 
		if (pParam->name == m_info.GetParamName(TParam::Preambl))
			m_sPreambl = pParam->data;

		return ModuleError::Ok;
	}

	int Pause() 
	{ 
		return ModuleError::Ok;
	}

	int Stop()
	{
		     for (int i = 0; i <= 0xFF; i++) {
            free(CodedByte[i]);
        }
		return ModuleError::Ok;
	}

	TModuleContext* Parameters() 
	{
		return &m_info;
	}

	static TModuleDescr* Description()
	{	
		return &g_description; 
	}

	bool HexStringToBytes(string_type& sValue, std::vector<uchar>& vOut, std::vector<uchar>& vOutMask){

		if ((sValue.size() % 2) == 1){ sValue = STR("0") + sValue;
		}

		if ((sValue.size() % 2) == 0){
			std::string sHex = str_utils::aFromLocal(sValue);

			if (sHex[0] == '0' && sHex[1] == 'x')
				sHex = sHex.substr(2, sHex.size() - 2);

			int nOutLen = static_cast<int>(sHex.size()) / 2;

			if (sHex.size() >= 2){
				vOut.resize(nOutLen);
				vOutMask.resize(nOutLen);

				for (unsigned int i = 0, j = 0; i < sHex.size(); i += 2, j++){
					int nByte = 0;
					std::string sByte = sHex.substr(i, 2);
					if (sByte[0] != '*'){
						if (sByte[1] != '*'){
							std::basic_istringstream<char> sis(sByte);
							sis >> std::hex >> nByte;
							vOutMask[j] = 0;
							vOut[j] = static_cast<uchar>(nByte);
						}
						else{
							vOut.resize(vOut.size() - 1);
							vOutMask.resize(vOut.size() - 1);
							j--;
						}

					}
					else{
						if (sByte[1] == '*'){
							vOut[j] = 0;
							vOutMask[j] = 1;
						}
						else{
							vOut.resize(vOut.size() - 1);
							vOutMask.resize(vOut.size() - 1);
							j--;
						}
					}
				}
				return true;
			}
		}

		return false;
	}
};

DECLARE_AS_MODULE(CeDSpread);

#endif // eDSpread_h__
