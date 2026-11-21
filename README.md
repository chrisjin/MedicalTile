# MedicalTile

A Windows C++ framework for 2D, 3D, and 4D medical image visualization and processing. MedicalTile uses Qt for the interface, ITK for image processing, and DCMTK for DICOM integration. Processing operations can be extended through DLL plugins and combined into XML pipelines.

![MedicalTile MPR viewer](https://raw.githubusercontent.com/chrisjin/MedicalTile_Resources/master/mainframe2.PNG)

## Features

- Import CT and MR image folders.
- Browse 3D image slices and multiplanar reconstruction (MPR) views.
- Explore time series of 3D images and plot region-of-interest time-density curves.
- Apply image-processing operations, including morphology, watershed segmentation, and registration.
- Arrange images and other data as tiles in a processing workspace.
- Extend algorithms, data types, editors, and visualization panels.

## Downloads and documentation

- [Releases](https://github.com/chrisjin/MedicalTile/releases)
- [Introduction slides](https://github.com/chrisjin/MedicalTile/releases/download/doc/doc.pptx)
- [Sample DICOM time series](https://github.com/chrisjin/MedicalTile/releases/download/doc/PA3_010-001.zip): more than 20 volumes acquired at sequential time points. Load the root folder of the extracted sample.
- Additional historical sample sources: [OsiriX datasets](http://www.osirix-viewer.com/datasets/) and [GDCM Philips MR samples](http://www.creatis.insa-lyon.fr/~jpr/PUBLIC/gdcm/gdcmSampleData/Philips_Medical_Images/mr711-mr712/INDEX.htm).

## Basic usage

Drag a loaded image into a viewer to display it, or into the processing panel to use it as an algorithm input. Draw a rectangle on the processing panel to select tiles, then choose an algorithm to process the selection.

| Mouse control | Action |
| --- | --- |
| Right button | Move through slices |
| Left button | Adjust window width and center |
| Middle button | Zoom and pan |

Hold **Ctrl** with these controls when the active view uses mouse input for drawing or selection. In other views, Ctrl is optional.

The processing panel supports moving, saving, selecting, deleting, and processing multiple tiles. A tile can contain a 3D image, a numeric array, or another supported data type. Numeric arrays can be plotted in the data-visualization panel, with configurable axis ranges and row assignments.

## Architecture

| Directory | Role |
| --- | --- |
| `BasicCraft/`, `VarCraft/` | Shared types, data abstractions, and variables |
| `DicomCraft/` | DICOM and image-data integration |
| `GUICraft/` | Viewers and interface components |
| `CoreEditor/`, `EditorCraft/` | Data editors and editing infrastructure |
| `AlgoCraft/`, `CoreAlgorithm/` | Algorithm interfaces, execution, and plugin management |
| `Algorithm/` | Processing plugins |
| `3rdPartyAlgLib/` | Bundled ALGLIB numerical library |
| `ProjectProperty/` | Visual Studio property sheets and dependency paths |

### Framework structure

![Framework architecture](https://raw.githubusercontent.com/chrisjin/MedicalTile_Resources/master/structure.PNG)

### ITK and Qt integration

![Image and data abstractions](https://raw.githubusercontent.com/chrisjin/MedicalTile_Resources/master/data.PNG)

## Plugins

### DLL plugins

Implement the algorithm interface to receive application data, run a processing operation, and return results. Plugins can also provide a Qt configuration panel. The application supplies the surrounding data and interface infrastructure.

### XML pipelines

XML plugins compose existing algorithms into a sequence. For example, the following kidney-segmentation pipeline combines subtraction, smoothing, ROI selection, thresholding, opening, and largest-component extraction:

```xml
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

An embedded Python interpreter is a planned extension and is not implemented.

## Building

The solution targets the original Windows/Visual Studio environment. It uses the following dependency versions:

| Dependency | Original configuration |
| --- | --- |
| Visual Studio | 2010 |
| Qt | 4.8.1; the original build notes also report 4.8.5 working |
| ITK | 4.1.0 |
| DCMTK | 3.6 |
| CMake | Used to configure ITK and DCMTK |

1. Obtain [ITK](http://www.itk.org/ITK/resources/legacy_releases.html), [Qt 4.8](http://download.qt-project.org/archive/qt/4.8/), and [DCMTK](http://dicom.offis.de/dcmtk.php.en).
2. Use [CMake](http://www.cmake.org/download/) to generate Visual Studio solutions for ITK and DCMTK. Enable shared libraries and set `CMAKE_INSTALL_PREFIX` for each dependency.
3. Build the libraries and their `INSTALL` targets. Build Qt from source or install compatible Windows binaries, then configure the Qt Visual Studio add-in.
4. Place the ITK/DCMTK headers and libraries under the solution's `Other/` directory, or update `ProjectProperty/Other.props` to point to their installed locations:

```text
Other/
├── itk_dll/
│   ├── include/ITK-4.1/
│   └── lib/
└── dcmtk/
    ├── include/dcmtk/
    └── lib/
```

5. Open `QtDicom_Recon.sln`, check the dependency and Qt paths, and build the solution. Make the required DLLs available to the application at runtime.

These instructions describe the legacy toolchain; the project does not yet provide a CMake build for the application itself.

## Screenshots

### 4D image series

MRI volumes at 20 time points show changes during contrast-medium injection and attenuation.

![MRI time series](https://raw.githubusercontent.com/chrisjin/MedicalTile_Resources/master/time-density.PNG)

### Multiplanar reconstruction

![MPR views in red, green, and blue](https://raw.githubusercontent.com/chrisjin/MedicalTile_Resources/master/MPR2.PNG)

### Image-processing workspace

![Image and data tiles in the processing panel](https://raw.githubusercontent.com/chrisjin/MedicalTile_Resources/master/algopanel.PNG)

### Data visualization

![Numeric data visualization panel](https://raw.githubusercontent.com/chrisjin/MedicalTile_Resources/master/datavis.PNG)

### Kidney segmentation

![Swine kidney segmentation](https://raw.githubusercontent.com/chrisjin/MedicalTile_Resources/master/segmentation.PNG)

### Time-density curve

![Contrast-medium time-density curve in a kidney ROI](https://raw.githubusercontent.com/chrisjin/MedicalTile_Resources/master/tdc.PNG)

## Development notes

MedicalTile was developed in 2013–2014 at Northeastern University (China) and used for academic research at Tianjin Medical University.

Planned work includes a CMake build, a curve-fitting plugin, and translation of the remaining Chinese interface text.

## License and contact

If you want to distribute or modify for any business use, please first contact [ShikaiJin.Job@Gmail.com](mailto:ShikaiJin.Job@Gmail.com).

Qt, ITK, DCMTK, ALGLIB, and other third-party components retain their respective licenses and copyright notices.
