#pragma once
#include<QThread>
#include<QDialog>
#include"amyPure.h"
class DefaultAlgorithmDialog:public QDialog
{
	DEFINE_SINGLETON(DefaultAlgorithmDialog)
public:
	DefaultAlgorithmDialog();

};


class amyAlgorithm;
class QDialog;
class amyAlgorithmThread:public QThread
{
	Q_OBJECT
public:
	amyAlgorithmThread();
	void SetAlgorithm(amyAlgorithm* a){m_Algo=a;}
	virtual void run();
signals:
	void s_done();
private:
	amyAlgorithm* m_Algo;
};