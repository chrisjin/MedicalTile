#ifndef AMYPATIENTTABLE_H
#define AMYPATIENTTABLE_H
#include"GuiMacro.h"
#include <QTableView>
#include"amyReaver.h"
class amyPatientModel;
class amyPatient;
class amySeriesThumb;
class GUI_INTERFACE amyPatientTable : public QTableView,public amyReaver
{
	Q_OBJECT

public:
	amyPatientTable(amyPatient* pat,QWidget *parent=0);

	void OnTakeOff(QPoint pos);
	~amyPatientTable();

private:
	amyPatientModel* m_Model;
	amyPatient*   m_Patient;
	amySeriesThumb * m_CurrentData;
};

 

#endif // AMYPATIENTTABLE_H
