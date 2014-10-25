#pragma once
#include<QObject>
#include<QPoint>
class amyVariableArea;
class amyVariableView;
class amyAlgorithm;
class amyAlgorithmThread;
class amyAlgorithmRunner:public QObject
{
	Q_OBJECT
public:
	amyAlgorithmRunner(amyVariableView* a);
	void SetAlgorithm(amyAlgorithm* a){m_Algo=a;}
	void RunAlgorithm();
	bool ProcessInput();
private:
	QPoint				m_PosForOutput;
	amyAlgorithm*		m_Algo;
	amyVariableView*	m_VariableArea;
	amyAlgorithmThread* m_Thread;
public slots:
	
	void ProcessOutput();

signals:

	void s_invalid_inputtype();
	void s_invalid_inputnum();
	void s_invalid_outputtype();
	void s_invalid_outputnum();
	void s_run_begin();
	void s_run_end();


};