MedicalTile
===========

Description
----------------
MedicalTile is an open source software for 2D and 3D medical image visualization and processing. 
It's base on Qt, ITK and DCMTK. It can only work on WIN32 platform for now.<br>
![Qt](https://github.com/chrisjin/MedicalTile_Resources/blob/master/Qt.png)
![ITK](https://github.com/chrisjin/MedicalTile_Resources/blob/master/ITK.png)
![DCMTK](https://github.com/chrisjin/MedicalTile_Resources/blob/master/dcmtk.png)

Release
--------------
[DOWNLOAD](https://github.com/chrisjin/MedicalTile/releases/download/FirstRelease/Release_10_25_2014.zip)
<p>
You can test the tool by loading the root folder of the data samples below.
<br>
[Dicom sample 1, more than 3D images taken at many sequential time points](https://github.com/chrisjin/MedicalTile/releases/download/FirstRelease/PA3_010-001.zip)
<p>
[More samples](http://www.creatis.insa-lyon.fr/~jpr/PUBLIC/gdcm/gdcmSampleData/Philips_Medical_Images/mr711-mr712/INDEX.htm)


Feature
---------------
* Import CT or MR image folders.
* Display 3D image as slices.
* Image processing algorithms including morphological algorithms, watershed algorithm, registration and etc.
* Data visualization.
* 3D image series or 4D image, time-density curve of a ROI
* Extremely extensible. Any one can add plugins as DLL to it without recompiling the whole project. 

Screeshot
------------------------
####Images of a swine taken by a MRI
3D images of 20 time points or 4D image  
![](https://github.com/chrisjin/MedicalTile_Resources/blob/master/mainframe.PNG)
####Images of brain
MPR view
![](https://github.com/chrisjin/MedicalTile_Resources/blob/master/mainframe2.PNG)
####Image processing panel
You can freely select and manipulate multple 3D images on this panel. <br>
One tile representing a 3D image
![](https://github.com/chrisjin/MedicalTile_Resources/blob/master/algopanel.PNG)
####Data visualization panel
![](https://github.com/chrisjin/MedicalTile_Resources/blob/master/datavis.PNG)

Structure
---------------------
####Main framework
![](https://github.com/chrisjin/MedicalTile_Resources/blob/master/structure.PNG)
####ITK and Qt encapsulation
![](https://github.com/chrisjin/MedicalTile_Resources/blob/master/data.PNG)

How to compile?
---------------
####Step 1, download the 3rd party libraries.
* Download ITK 4.1.0 from [ITK](http://www.itk.org/ITK/resources/legacy_releases.html)
* Download Qt >= 4.8.1 (I use 4.8.1 for this project, and Qt 4.8.5 also works fine) from [Qt](http://download.qt-project.org/archive/qt/4.8/)
* Download DCMTK3.6 from [DCMTK](http://dicom.offis.de/dcmtk.php.en)

####Step 2, add 3rd pary libraries and compile. 
* Visual studio 2010 is suggested.<br>
* Install Qt add-in for visual studio. You can find it in the downloaded Qt package.<br>
* Add headers and libraries to visual studio.<br>
* Then, open the sln file in your visual studio and click build!<br>

How to add plugin?
-----------------
####1, DLL plugin, 
###### Step 1, inherit the following algorithm prototype and overwrite its virtual funtion.
```
class ALGOCRAFT_INTERFACE amyAlgorithm
{
public:
	amyAlgorithm();
	virtual bool		  CheckInputArr(std::vector<amyVariable>& arr)=0;
	virtual const char*       GetAlgorithmName()=0;
	virtual void 	          Run()=0;
	
	void                      PostWarning(const char* info);
	void                      PostError(const char* info);

	virtual const char*	  GetCategory(){return "Algorithm";}


	virtual string		  GetAuthor(){return "";}
	virtual string            GetHint(){return "";}
	virtual string            GetDescription(){return "";}

	virtual QFrame*           CreatePanel(QWidget* parent);
	virtual QIcon*            GetIcon(){return 0;}


	amyAlgorithmStack*        GetStack();
};
```
