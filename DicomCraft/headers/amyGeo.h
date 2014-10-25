//#pragma once
//#include<vector>
//#include"amyPure.h"
//using namespace std;
//class amyGeoPoint
//{
//public:
//	amyGeoPoint(int xx,int yy):x(xx),y(yy){}
//	int x;
//	int y;
//};
//
//class amyGeoEdge
//{
//public:
//	amyGeoPoint *p1;
//	amyGeoPoint *p2;
//};
//
//class amyGeoElement
//{
//public:
//	amyGeoElement(bool issolid=0);
//	//void AddPoint(amyGeoPoint* p);
//	//void ClearPoint();
//	virtual bool IsHit(int x,int y);
//	bool IsSolid(){return m_IsSolid;}
//private:
//	bool m_IsSolid;
//	//vector<amyGeoPoint*> m_PointArr;
//};
//
//class amyGeoRect:public amyGeoElement
//{
//public:
//	amyGeoRect(int x,int y,int width,int height,bool issolid=0);
//	bool IsHit(int x,int y);
//	amyRect GetRect(){return m_Rect;}
//private:
//	amyRect m_Rect;
//};
//
////class amyGeoLine:public amyGeoElement
////{
////public:
////	amyGeoLine(int x1,int y1,int x2,int y2,bool issolid=0);
////	bool IsHit(int x,int y);
////private:
////	amyPoint m_P1;
////	amyPoint m_P2;
////};