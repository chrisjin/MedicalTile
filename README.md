MedicalTile
===========

Description
----------------
MedicalTile is an open source software for 2D and 3D medical image visualization and processing. 
It's based on Qt, ITK and DCMTK. It works on WIN32 platform for now.<br>
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
* Image processing algorithms including morphological algorithms, watershed algorithm, registration etc.
* Data visualization.
* 3D image series or 4D image, time-density curve of a ROI
* Extremely extensible. Any one can add plugins as DLL to it without recompiling the whole project. 

Screeshot
------------------------
####Images of a swine taken by a MRI
3D images of 20 time points or 4D image<br>
You can see gradual changes among these images indicating the injection and attenuation of contrast medium.
![](https://github.com/chrisjin/MedicalTile_Resources/blob/master/time-density.PNG)
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

Plugin
-----------------
* DLL plugin. Inherit a base class running your GUI, receiving data from the main application, processing your data and returning the result to the main application. The main application can handle all the rest.
* XML plugin. kind of simple scrypt plugin. A XML plugin organizes existing plugins in a sequential order. When you run a XML plugin, actually you run several different plugins sequentially. <br>
The plugin below combines Subtraction, Gaussian, ROISegmentation, Threshold, Opening, and LargestComponent together.
```
      <Test>
      <version>1</version>
      <name>KidneySeg</name>
      <category>Kidney</category>
      <algo>Subtraction</algo>
      <algo>Gaussian</algo>
      <algo>ROISegmentation</algo>
      <algo>Threshold</algo>
      <algo>Opening</algo>
      <algo>LargestComponent</algo>
      </Test>
```
* Other scrypt plugin. I plan to embed a python interpreter inside my application, but it's not done yet.

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


