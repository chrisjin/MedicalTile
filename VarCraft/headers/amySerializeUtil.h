//#pragma once
//#include<QDomElement>
//#include<QDomDocument>
//#include<string>
//#include"amyDICOM.h"
//using namespace std;
//#define DOMELE(parent,name,content)\
//		{\
//		QDomElement child= doc.createElement(name);\
//		child.appendChild(doc.createTextNode(content));\
//		parent.appendChild(child);\
//		return child;\
//		}
//
//#define DOMSTRUCT(parent,name)\
//		QDomElement name= doc.createElement(#name);\
//		parent.appendChild(name);
//
////#define ATTR(name) 
//		
//template<typename T>
//QDomElement Attr2Dom(QDomDocument doc,QDomElement parent,QString name,T a)
//{
//
//}
//
//template<>
//QDomElement Attr2Dom<int>(QDomDocument doc,QDomElement parent,QString name,int a)
//{
//	DOMELE(name,parent,QString::number(a));
//}
//
//template<>
//QDomElement Attr2Dom<unsigned int>(QDomDocument doc,QDomElement parent,QString name,unsigned int a)
//{
//	DOMELE(name,parent,QString::number(a));
//}
//
//template<>
//QDomElement Attr2Dom<float>(QDomDocument doc,QDomElement parent,QString name,float a)
//{
//	DOMELE(name,parent,QString::number(a));
//}
//
//template<>
//QDomElement Attr2Dom<string>(QDomDocument doc,QDomElement parent,QString name,string a)
//{
//	DOMELE(name,parent,a.c_str());
//}
