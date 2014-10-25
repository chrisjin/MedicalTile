#include"amyLing.h"
#include<QString>
#include<QObject>
class amyCubeLing;
class GUI_INTERFACE amyAnnotationLing:public QObject,public amyLing
{
	Q_OBJECT
public:
	amyAnnotationLing(amyCubeLing* cubeling,amyCanvas* can);
	void SetCubeLing(amyCubeLing* cubeling);
	void SetPixelValue(int x,int y,int v,bool isshow);
	void Render(QPaintDevice* dev);
	void resizeEvent(QResizeEvent*);
	void UpdateStr();
public slots:
	void SetWindow(int c,int w);
	void SetSlice(int index);
	void SetCubeLingInput();
private:
	QString m_PixelValue;
	QString ImageCount;
	QString ImageNum;
	QString ImageNumInDICOM;
	QString WindowInfo;
	QString SliceThickness;
	QString SliceLocation;
	QString PatientName;
	QString TopLeft;
	QString TopRight;
	QString BottomLeft;
	QString BottomRight;
	QString Right;
	QString Left;
	QString Top;
	QString Bottom;
	QString PlaneType;
	QString VoxelSize;
	int     m_CurrentSlice;
	amyCubeLing* m_CubeLing;
};