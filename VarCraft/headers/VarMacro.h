#pragma once
#ifdef _WINDLL
	#if defined(IMPORT_VARCRAFT)
		#define VAR_INTERFACE _declspec(dllimport)
	#else
		#define VAR_INTERFACE _declspec(dllexport)
	#endif
#else
	#define VAR_INTERFACE _declspec(dllimport)
#endif

#ifdef EXPORT_VARCRAFT_TEMPLATE
	#define VARCRAFT_TEMPLATE_INTERFACE _declspec(dllexport)
#else
	#define VARCRAFT_TEMPLATE_INTERFACE
#endif


///////////////////////////////////WriterMacro

#define NUM2STR(num)    (QString("%1").arg(num, 2, 10, QChar('0')))
#define DATE2STR(date) (QString::number(date.year)+NUM2STR(date.month)+NUM2STR(date.day))
#define TIME2STR(time) (NUM2STR(time.hour)+NUM2STR(time.minute)+NUM2STR(time.second))
#define PLANE2STR(p)    (QString::number(p))


#define DOMTAG(name,content) \
	{\
		QDomElement child= m_Doc.createElement(name);\
		child.appendChild(m_Doc.createTextNode(content));\
		m_Root.appendChild(child);\
	}
#define DOMCTAG(parent,name,content)\
	{\
		QDomElement child= m_Doc.createElement(name);\
		child.appendChild(m_Doc.createTextNode(content));\
		parent.appendChild(child);\
	}
#define DOMATTR(type,name,content)\
	{\
		QDomElement child= m_Doc.createElement("attr");\
		child.setAttribute("type",type);\
		child.setAttribute("name",name);\
		child.appendChild(m_Doc.createTextNode(content));\
		m_Root.appendChild(child);\
	}
#define SAVEDOM(name)\
	{\
		QFile file;\
		file.setFileName(name);\
		if (!file.open(QFile::WriteOnly | QFile::Text))\
		{  \
			return 0;  \
		}  \
		QTextStream out(&file);  \
		m_Doc.save(out,4);  \
		file.close(); \
	}
#define TYPESTR(var)\
	(amyVariableManager::GetInstance()->GetTypeString(var.GetType()).c_str())

#define NATTR(name) DOMCTAG(slice,#name,QString::number(si->name))
#define SATTR(name) DOMCTAG(slice,#name,si->name.c_str())

///////////////////////////////////WriterMacro