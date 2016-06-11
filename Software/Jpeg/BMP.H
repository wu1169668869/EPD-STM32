#ifndef __BMP_H__
#define __BMP_H__
#include "sys.h"
#include "fat.h"
//BMP��Ϣͷ
typedef __packed struct
{
    DWORD biSize ;		   //˵��BITMAPINFOHEADER�ṹ����Ҫ��������
    LONG  biWidth ;		   //˵��ͼ��Ŀ��ȣ�������Ϊ��λ 
    LONG  biHeight ;	   //˵��ͼ��ĸ߶ȣ�������Ϊ��λ 
    WORD  biPlanes ;	   //ΪĿ���豸˵��λ��������ֵ�����Ǳ���Ϊ1 
    WORD  biBitCount ;	   //˵��������/���أ���ֵΪ1��4��8��16��24����32
    DWORD biCompression ;  //˵��ͼ������ѹ�������͡���ֵ����������ֵ֮һ��
	//BI_RGB��û��ѹ����
	//BI_RLE8��ÿ������8���ص�RLEѹ�����룬ѹ����ʽ��2�ֽ����(�ظ����ؼ�������ɫ����)��  
    //BI_RLE4��ÿ������4���ص�RLEѹ�����룬ѹ����ʽ��2�ֽ����
  	//BI_BITFIELDS��ÿ�����صı�����ָ�������������
    DWORD biSizeImage ;//˵��ͼ��Ĵ�С�����ֽ�Ϊ��λ������BI_RGB��ʽʱ��������Ϊ0  
    LONG  biXPelsPerMeter ;//˵��ˮƽ�ֱ��ʣ�������/�ױ�ʾ
    LONG  biYPelsPerMeter ;//˵����ֱ�ֱ��ʣ�������/�ױ�ʾ
    DWORD biClrUsed ;	   //˵��λͼʵ��ʹ�õĲ�ɫ���е���ɫ������
    DWORD biClrImportant ; //˵����ͼ����ʾ����ҪӰ�����ɫ��������Ŀ�������0����ʾ����Ҫ�� 
}BITMAPINFOHEADER ;
//BMPͷ�ļ�
typedef __packed struct
{
    WORD  bfType ;     //�ļ���־.ֻ��'BM',����ʶ��BMPλͼ����
    DWORD bfSize ;	   //�ļ���С,ռ�ĸ��ֽ�
    WORD  bfReserved1 ;//����
    WORD  bfReserved2 ;//����
    DWORD bfOffBits ;  //���ļ���ʼ��λͼ����(bitmap data)��ʼ֮��ĵ�ƫ����
}BITMAPFILEHEADER ;
//��ɫ�� 
typedef __packed struct 
{
    BYTE rgbBlue ;    //ָ����ɫǿ��
    BYTE rgbGreen ;	  //ָ����ɫǿ�� 
    BYTE rgbRed ;	  //ָ����ɫǿ�� 
    BYTE rgbReserved ;//����������Ϊ0 
}RGBQUAD ;
//λͼ��Ϣͷ
typedef __packed struct
{ 
	BITMAPFILEHEADER bmfHeader;
	BITMAPINFOHEADER bmiHeader;  
	//RGBQUAD bmiColors[256];  
}BITMAPINFO; 

typedef RGBQUAD * LPRGBQUAD;//��ɫ��  

//ͼ������ѹ��������
#define BI_RGB       0L
#define BI_RLE8      1L
#define BI_RLE4      2L
#define BI_BITFIELDS 3L 

#define M_SOF0  0xc0
#define M_DHT   0xc4
#define M_EOI   0xd9
#define M_SOS   0xda
#define M_DQT   0xdb
#define M_DRI   0xdd
#define M_APP0  0xe0  	  
//��Z���α����
const int Zig_Zag[8][8]={{0,1,5,6,14,15,27,28},
					  	  {2,4,7,13,16,26,29,42},
						  {3,8,12,17,25,30,41,43},
						  {9,11,18,24,31,40,44,53},
						  {10,19,23,32,39,45,52,54},
						  {20,22,33,38,46,51,55,60},
						  {21,34,37,47,50,56,59,61},
						  {35,36,48,49,57,58,62,63}
						 };
const BYTE And[9]={0,1,3,7,0xf,0x1f,0x3f,0x7f,0xff};

#define W1 2841 /* 2048*sqrt(2)*cos(1*pi/16) */
#define W2 2676 /* 2048*sqrt(2)*cos(2*pi/16) */
#define W3 2408 /* 2048*sqrt(2)*cos(3*pi/16) */
#define W5 1609 /* 2048*sqrt(2)*cos(5*pi/16) */
#define W6 1108 /* 2048*sqrt(2)*cos(6*pi/16) */
#define W7 565  /* 2048*sqrt(2)*cos(7*pi/16) */
												 
	  					    		  
#define MAKEWORD(a, b)      ((WORD)(((BYTE)(a)) | ((WORD)((BYTE)(b))) << 8))
#define MAKELONG(a, b)      ((LONG)(((WORD)(a)) | ((DWORD)((WORD)(b))) << 16))
#define LOWORD(l)           ((WORD)(l))
#define HIWORD(l)           ((WORD)(((DWORD)(l) >> 16) & 0xFFFF))
#define LOBYTE(w)           ((BYTE)(w))
#define HIBYTE(w)           ((BYTE)(((WORD)(w) >> 8) & 0xFF))
	   
//�궨��					   
#define WIDTHBYTES(i)    ((i+31)/32*4)//??????????
#define PI 3.1415926535
//��������ֵ����
#define FUNC_OK 0
#define FUNC_MEMORY_ERROR 1
#define FUNC_FILE_ERROR 2
#define FUNC_FORMAT_ERROR 3
//�õ����ⲿ����
//extern FileInfoStruct F_Info[8];//�ļ��ṹ��
//extern unsigned int POINT_COLOR;//������ɫ				       
//////////////////////////////////////////////////
//BMP���뺯��
BOOL BmpDecode(FileInfoStruct *BmpFileName);
//////////////////////////////////////////////////
//JPEG ���뺯��				 
int  InitTag(void);
void InitTable(void);						   //��ʼ�����ݱ�
int  Decode(void);							   //����
int  DecodeMCUBlock(void);
int  HufBlock(BYTE dchufindex,BYTE achufindex);//����������
int  DecodeElement(void);					   //����һ������
void IQtIZzMCUComponent(short flag);		   //������
void IQtIZzBlock(short  *s ,short * d,short flag);
void GetYUV(short flag);		 //ɫ��ת����ʵ��,�õ�ɫ�ʿռ�����
void StoreBuffer(void);

BYTE ReadByte(void);             //���ļ������ȡһ���ֽڳ���
void Initialize_Fast_IDCT(void); //��ʼ������ɢ����Ҷ�任
void Fast_IDCT(int * block);	 //���ٷ���ɢ����Ҷ�任
void idctrow(int * blk);
void idctcol(int * blk);  
////�Ի��������ݽ����ƶ�����,ʹ����SD���������sramһ��
unsigned int P_Cal(unsigned char*pc);		    
#endif







