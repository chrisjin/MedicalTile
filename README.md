MedicalTile
===========
[DOWNLOAD is available!](https://github.com/chrisjin/MedicalTile/releases/download/FirstRelease/Release_2014_10_25.zip)
Description
----------------
MedicalTile is an open source software for 2D and 3D medical image visualization and processing. 
It's base on Qt and ITK. It can only work on WIN32 platform for now.


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
![](https://github.com/chrisjin/MedicalTile_Resources/blob/master/mainframe2.PNG)

How to compile?
---------------
####First, download the 3rd party libraries.
* Download ITK 4.1.0 from [ITK](http://www.itk.org/ITK/resources/legacy_releases.html)
* Download Qt >= 4.8.1 (I use 4.8.1 for this project, and Qt 4.8.5 also works fine) from [Qt](http://download.qt-project.org/archive/qt/4.8/)
* Download DCMTK3.6 from [DCMTK](http://dicom.offis.de/dcmtk.php.en)

####Second, add 3rd pary libraries and compile. 
* Visual studio 2010 is suggested.<br>
* Install Qt add-in for visual studio. You can find it in the downloaded Qt package.<br>
* Add headers and libraries to visual studio.<br>
* Then, open the sln file in your visual studio and click build!<br>

