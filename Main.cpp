#include "Logger.h"
#include "BitmapImporter.h"
using namespace LoggerClass;

int main()
{
	BitmapImporter bit;

	bit.CreateImage(100, 150, 260, 20, 00);
	bit.WriteBitmap("BeeS.bmp");


	BitmapImporter bitmap;
	bitmap.ReadBitmap("ankita.bmp");
	
	for (int i = 10; i < 100; i++)
	{
		for (int j = 10; j < 100; j++)
		{
			bitmap.SetPixel(j,i,160,180,155);
		}
	}
	bitmap.WriteBitmap("b.bmp");

		

	
	/*
		bit.ReadBitmap("siz.bmp");
		int poseX=50, poseY=50;

		for (int i = 0; i < 100; i++)
		{
			for (int j = 0; j < 100; j++)
			{
				if (sqrt((i - 50) * (i - 50) + (j - 50) * (j - 50)) < 50)
				{
					bit.SetPixel(j + poseX, i + poseY, 220, 100, 78);
				}

			}
		}*/

	/*LOG() << "Begin: "<<"File Opened"<<endl;
	LOG() << "WARNING: " << "My Warning"<< endl;
	LOG() << "ERROR: " << "My Error" <<endl;
	LOG() << "TRACE: " << "My Trace" <<endl;
	LOG() << "INFO: " << "My Info"<<endl;*/
	
	//LOG() << "End" << endl;
	system("pause");
	return 0;
}
