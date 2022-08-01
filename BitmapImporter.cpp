#include "BitmapImporter.h"
#include "Logger.h"


bool BitmapImporter::CreateImage(int width, int height, BYTE B, BYTE G, BYTE R)
{
	LoggerClass::LOG() <<"BEGIN: "<< "Create a Bitmap Image" << endl;
	
	const int fileheadersize = 14;
	LoggerClass::LOG() <<"File Header Size: " <<fileheadersize << endl;
	const int infoheadersize = 40;
	LoggerClass::LOG() << "Info Header Size: " << infoheadersize << endl;

	BYTE PadingData[] = { 0, 0, 0 };
	int Padding = (4 - (width * sizeof(BGR)) % 4) % 4;
	int RowSize = width * sizeof(BGR) + Padding;
	LoggerClass::LOG() << "RowSize: " << width * sizeof(BGR) + Padding << endl;
	int DataSize = RowSize * height;
	LoggerClass::LOG() << "DataSize: " << RowSize * height << endl;
	if (m_data) {
		Release();
	}

	m_fileheader.bfSize = DataSize + fileheadersize + infoheadersize;
	m_fileheader.bfOffBits = fileheadersize + infoheadersize;
	m_fileheader.bfType = 19778;
	m_fileheader.bfReserved1 = 0;
	m_fileheader.bfReserved1 = 0;

	m_infoheader.biBitCount = 24;
	m_infoheader.biClrImportant = 0;
	m_infoheader.biClrUsed = 0;
	m_infoheader.biCompression = BI_RGB;
	m_infoheader.biHeight = height;
	m_infoheader.biPlanes = 1;
	m_infoheader.biSize = 40;
	m_infoheader.biSizeImage = DataSize + fileheadersize + infoheadersize;
	m_infoheader.biWidth = width;
	m_infoheader.biYPelsPerMeter = 0;
	m_infoheader.biXPelsPerMeter = 0;

	//Allocate Memory :

	m_data = new BGR * [height];
	for (int i = 0; i < height; i++)
	{
		m_data[i] = new BGR[width];
	}

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			m_data[i][j].B = B;
			m_data[i][j].G = G;
			m_data[i][j].R = R;


		}

	}
	return true;



}

bool BitmapImporter::ReadBitmap(const char* filePath)
{

	LoggerClass::LOG() << "Start Loading Bitmap file for read: " << filePath << endl;
	ifstream f;
	f.open(filePath, ios::in | ios::binary);
	if (!f.is_open())
	{
		LoggerClass::LOG() << "ERROR: " << "File could not be opened" << endl;
		return false;
	}
	const int fileheadersize = 14;
	const int infoheadersize = 40;



	f.read(reinterpret_cast<char*>(&m_fileheader), fileheadersize);
	f.read(reinterpret_cast<char*>(&m_infoheader), infoheadersize);

	int _Width = m_infoheader.biWidth;
	int _Height = m_infoheader.biHeight;

	LoggerClass::LOG() << "INFO: " << "Passed the width and height " << endl;
	LoggerClass::LOG() <<  "     _Width = " << m_infoheader.biWidth << endl;
	LoggerClass::LOG() << "     _Heigth = " << m_infoheader.biHeight << endl;
	BYTE PadingData[] = { 0, 0, 0 };
	int Padding = (4 - (_Width * sizeof(BGR)) % 4) % 4;
	int RowSize = _Width * sizeof(BGR) + Padding;
	int DataSize = RowSize * _Height;
	BYTE* tmpData = new BYTE[DataSize];
	f.seekg(m_fileheader.bfOffBits, ios::beg);
	LoggerClass::LOG() << "File read operation performed" << endl;
	f.read(reinterpret_cast<char*>(tmpData), DataSize);
	LoggerClass::LOG() << "File Closed" << " " << filePath << endl;
	f.close();
	
	m_data = new BGR * [_Height];
	for (int i = 0; i < _Height; i++)
	{
		m_data[i] = new BGR[_Width];
	}
	int pixelctr = 0;
	for (int i = 0; i < _Height; i++)
	{
		for (int j = 0; j < _Width; j++)
		{
			m_data[i][j].B = tmpData[pixelctr + 0];
			m_data[i][j].G = tmpData[pixelctr + 1];
			m_data[i][j].R = tmpData[pixelctr + 2];
			pixelctr += 3;
		}
		pixelctr += Padding;
	}
	delete[] tmpData;

	return true;
}

bool BitmapImporter::WriteBitmap(const char* filePath)
{
	LoggerClass::LOG() << "Start Loading Bitmap file for write: " << filePath << endl;
	ofstream of;
	LoggerClass::LOG() << "INFO: " << "File opened "<<" " << filePath << endl;
	of.open(filePath, ios::out | ios::binary);
	BYTE PadingData[] = { 0, 0, 0 };
	int _Width = m_infoheader.biWidth;
	int _Height = m_infoheader.biHeight;
	
	LoggerClass::LOG() << "     _Width = " << m_infoheader.biWidth << endl;
	LoggerClass::LOG() << "     _Height = " << m_infoheader.biHeight << endl;

	int Padding = (4 - (_Width * sizeof(BGR)) % 4) % 4;
	LoggerClass::LOG() << "     RowSize = " << _Width * sizeof(BGR) + Padding << endl;
	int RowSize = _Width * sizeof(BGR) + Padding;
	LoggerClass::LOG() << "     DataSize = " << RowSize * _Height << endl;
	int DataSize = RowSize * _Height;


	const int fileheadersize = 14;
	const int infoheadersize = 40;
	LoggerClass::LOG() << "File Write operation performed" << endl;
	
	of.write(reinterpret_cast<char*>(&m_fileheader), fileheadersize);
	of.write(reinterpret_cast<char*>(&m_infoheader), infoheadersize);

	for (int i = 0; i < _Height; i++)
	{
		for (int j = 0; j < _Width; j++)
		{
			of.write(reinterpret_cast<char*>(&m_data[i][j]), sizeof(BGR));
		}
		of.write(reinterpret_cast<char*>(PadingData), Padding);
	}
	LoggerClass::LOG() << "File Closed " << " " << filePath << endl;
	LoggerClass::LOG() << "END " << endl;
	of.close();
	return true;
	
}




BitmapImporter::BGR BitmapImporter::GetPixel(int x, int y)
{
	return m_data[y][x];
}



void BitmapImporter::SetPixel(int x, int y, BYTE R, BYTE G, BYTE B)
{
	//LoggerClass::LOG() << "Set the pixel data" << endl;
	m_data[y][x].B = B;
	m_data[y][x].G = G;
	m_data[y][x].R = R;
}

void BitmapImporter::Release()
{

	int height = m_infoheader.biHeight;
	for (int i = 0; i < height; i++)
	{                                        //To delete the inner arrays
		delete[] m_data[i];
	}
	delete[] m_data;              //To delete the outer array

}
