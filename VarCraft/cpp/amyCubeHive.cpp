#include"amyCubeHive.h"
#include"amyCube.h"
#include"amyDICOM.h"
#include<QColor>
#include"itkImageSeriesWriter.h"
#include"itkGDCMImageIO.h"
#include<QDomDocument>
amyVariableIO* amyCubeHive::CreateIO()
{
	return new amyCubeIO;
}
QImage amyCubeHive::GetIcon(amyVariable& var)
{
	amyCube::Keeper cube=var.Get<amyCube>();
	typedef amyCube::tCube tInput;
	tInput::RegionType inputRegion =
		cube->obj->GetLargestPossibleRegion();
	tInput::SizeType size = inputRegion.GetSize();


	int imgwidth=size[0];
	int imgheight=size[1];
	int imgdepth=size[2];
	int m_WindowCenter=!cube->series.IsNull()?cube->series->slicearr[0]->info->windowcenter:cube->windowcenter;
	int m_WindowWidth=!cube->series.IsNull()?cube->series->slicearr[0]->info->windowwidth:cube->windowwidth;
	int min = (2*m_WindowCenter - m_WindowWidth)/2.0 + 0.5;
	int max = (2*m_WindowCenter + m_WindowWidth)/2.0 + 0.5;

	QImage m_Image=QImage(imgwidth,imgheight,QImage::Format_Indexed8);
	for (unsigned int i=0;i<256;i++)
	{
		QColor* rgb =new QColor(i,i,i);
		m_Image.setColor(i,rgb->rgb());
	}
	for (unsigned int i=0;i<imgwidth;i++)
	{
		for (unsigned int j=0;j<imgheight;j++)
		{
			amyCube::tCube::IndexType index;
			index[0]=i;
			index[1]=j;
			index[2]=imgdepth/2;
			short v=cube->obj->GetPixel(index);
			int   postv=(v - min)*255.0/(double)(max - min);
			unsigned char tv;
			if(postv<0) tv=0;
			else if(postv>255) tv=255;
			else tv=postv;
			m_Image.setPixel(i,j,tv);
		}
	}
	return m_Image;
}

VTYPE  amyCubeHive::GetType()
{
	return VTYPE_CUBE;
}

amyVariable amyCubeHive::Produce(string name)
{
	amyVariable v(GetType(),name,new amyCube);
	return v;
}
const char* amyCubeHive::GetString()
{
	return "CUBE";
}
QDomNode   amyCubeIO::SerializeContent(amyVariable& v)
{
	m_FilePathArr.clear();
	QDomDocument m_Doc=this->GetDoc();
	QDomElement m_Root = m_Doc.createElement("content");
	amyCube::Keeper cube=v.Get<amyCube>();
	
	DOMTAG("windowcenter",QString::number(cube->windowcenter));
	DOMTAG("windowwidth",QString::number(cube->windowwidth));
	amyCube::tCube::RegionType   region     = cube->obj->GetLargestPossibleRegion();
	amyCube::tCube::IndexType    start      = region.GetIndex();
	amyCube::tCube::SizeType     size       = region.GetSize();

	const unsigned int firstSlice = start[2];
	const unsigned int lastSlice  = start[2] + size[2] - 1;

	QString nameformat=(v.GetName()+"_"+this->GetHive()->GetString()+"%03d").c_str();
	QString str;
	QString con="";
	for(int i=firstSlice;i<=lastSlice;i++)
	{
		str.sprintf(nameformat.toLocal8Bit().data(),i);
		con+=str+"|";
		m_FilePathArr.push_back(GetWorkingPath()+"/"+str);
	}
	DOMTAG("files",con);
	return m_Root;
}
int   amyCubeIO::DeserializeContent(QDomNode node,amyVariable var)
{
	QDomElement windowcenter=node.firstChildElement("windowcenter");
	if(windowcenter.isNull())
	{
		return 0;
	}
	var.Get<amyCube>()->windowcenter=windowcenter.text().toInt();
	QDomElement windowwidth=node.firstChildElement("windowwidth");
	if(windowwidth.isNull())
	{
		return 0;
	}
	var.Get<amyCube>()->windowwidth=windowwidth.text().toInt();

	QDomElement files=node.firstChildElement("files");
	QString con=files.text();
	QStringList slist=con.split('|');
	vector<string> path;
	string dir=this->GetWorkingPath().toLocal8Bit().data();
	for(int i=0;i<slist.count();i++)
	{
		if(slist.at(i).size()!=0)
			path.push_back((dir+"/"+slist.at(i).toLocal8Bit().data()));
	}
	var.Get<amyCube>()->Open(path);
	return 1;
}

int   amyCubeIO::WriteAttachment(QString dir,amyVariable& v)
{
	amyCube::Keeper cube=v.Get<amyCube>();
	vector<string> names;
	for(int i=0;i<PathArr().size();i++)
	{
		names.push_back(PathArr()[i].toLocal8Bit().data());
	}
	typedef itk::Image<short,2> OutputImageType;
	typedef itk::ImageSeriesWriter<amyCube::tCube,OutputImageType> WriterType;
	WriterType::Pointer writer = WriterType::New();
	typedef itk::GDCMImageIO                        ImageIOType;
	writer->SetImageIO(ImageIOType::New());
	writer->SetInput( cube->obj );
	itk::GDCMImageIO::Pointer io=itk::GDCMImageIO::New();
	
	//writer->SetMetaDataDictionaryArray
	writer->SetMetaDataDictionary(cube->obj->GetMetaDataDictionary());
	writer->SetFileNames(names);
	try
	{
		writer->Update();
	}
	catch( itk::ExceptionObject & excp )
	{
		return 0;
	}
	return 1;
}