#ifndef amyFolderView_H
#define amyFolderView_H
#include"GuiMacro.h"
#include <QTabWidget>
#include <qtableview>
class amyDCMFolder;
#include<vector>
#include"amyKeeper.h"
#include"amyReaver.h"
using namespace std;
class amyPatientTable;
class GUI_INTERFACE amyFolderView : public QTabWidget,public amyReaver
{
	Q_OBJECT

public:
	void SetFolder(amyKeeper<amyDCMFolder> folder);
	amyDCMFolder* GetFolder(){return m_Folder.GetPointer();}
	amyFolderView(QWidget *parent=0);
	~amyFolderView();
	virtual void OnTakeOff(QPoint pos);
	virtual void dropEvent(QDropEvent *event);
	virtual void dragEnterEvent(QDragEnterEvent *event);
private:
	vector<amyPatientTable*> m_PatientViewArr;
	amyKeeper<amyDCMFolder> m_Folder;
};

#endif // amyFolderView_H
