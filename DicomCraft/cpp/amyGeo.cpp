//#include"amyGeo.h"
//amyGeoElement::amyGeoElement(bool issolid)
//{
//	this->m_IsSolid=issolid;
//}
//
//bool amyGeoElement::IsHit(int x,int y)
//{
//	return 1;
//}
//
//amyGeoRect::amyGeoRect(int x,int y,int width,int height,bool issolid):amyGeoElement(issolid),m_Rect(x,y,width,height)
//{
//
//}
//
//bool amyGeoRect::IsHit(int x,int y)
//{
//	if(!IsSolid())
//	{
//		if(x==m_Rect.x||x==m_Rect.x+m_Rect.width)
//		{
//			if(y>=m_Rect.y&&y<=m_Rect.y)
//			{
//				return 1;
//			}
//		}
//		if(y==m_Rect.y||y==m_Rect.y+m_Rect.height)
//		{
//			if(x>=m_Rect.x&&y<=m_Rect.width+m_Rect.x)
//			{
//				return 1;
//			}
//		}
//	}
//	return 0;
//}
//
////amyGeoLine::amyGeoLine(int x1,int y1,int x2,int y2,bool issolid):m_P1(x1,y1),m_P2(x2,y2),amyGeoElement(issolid)
////{
////	
////}
////
////bool amyGeoLine::IsHit(int x,int y)
////{
////	return 1;
////}
//
