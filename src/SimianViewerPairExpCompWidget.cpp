#include "SimianViewerPairExpCompWidget.h"
#include "PointData/PointData.h"
#include "ClusterData/ClusterData.h"
#include "util/FileUtil.h"
#include <fstream>
#include <string>
#include <iostream>
#include <QVBoxLayout>
#include <chrono>
#include <cassert>

SimianViewerPairExpCompCommunicationObject::SimianViewerPairExpCompCommunicationObject(SimianViewerPairExpCompWidget* parent)
	:
	_parent(parent)
{

}



void SimianViewerPairExpCompCommunicationObject::js_passSelectionSpecies1ToQt(QString data)
{
	//qDebug() << "\nReceived from Javascript to QT\n";
	_parent->js_passSelectionSpecies1ToQt(data.toStdString());
}


void SimianViewerPairExpCompCommunicationObject::js_passSelectionSpecies2ToQt(QString data)
{
	//qDebug() << "\nReceived from Javascript to QT\n";
	_parent->js_passSelectionSpecies2ToQt(data.toStdString());
}

void SimianViewerPairExpCompCommunicationObject::js_crossspeciesclusterSelection(QString data)
{
	//qDebug() << "\nReceived from Javascript to QT\n";
	_parent->js_crossspeciesclusterSelection(data.toStdString());
}

SimianViewerPairExpCompWidget::SimianViewerPairExpCompWidget() :
	loaded(false)
{
	Q_INIT_RESOURCE(PopulationPyramid_viewer_resources);
	_communicationObject = new SimianViewerPairExpCompCommunicationObject(this);
	init(_communicationObject);

	setMinimumHeight(160);

}

SimianViewerPairExpCompWidget::~SimianViewerPairExpCompWidget()
{

}

void SimianViewerPairExpCompWidget::setData(std::string visDataContent)
{

	emit _communicationObject->qt_setData(QString((visDataContent).c_str()));
}

void SimianViewerPairExpCompWidget::setSelectedCrossspeciescluster(QString visDataContent)
{

	emit _communicationObject->qt_setSelectedCrossspeciescluster(visDataContent);
}
//void SimianViewerPairExpCompWidget::setBarhighlight(QString Cluster)
//{
//
//	emit _communicationObject->qt_setBarhighlight(Cluster);
//}

void SimianViewerPairExpCompWidget::js_passSelectionSpecies1ToQt(std::string selectedIDs)
{
	emit passSelectionSpecies1ToQt(selectedIDs);
}

void SimianViewerPairExpCompWidget::js_passSelectionSpecies2ToQt(std::string selectedIDs)
{
	emit passSelectionSpecies2ToQt(selectedIDs);
}

void SimianViewerPairExpCompWidget::js_crossspeciesclusterSelection(std::string selectedIDs)
{
	emit crossspeciesclusterSelection(selectedIDs);
}

void SimianViewerPairExpCompWidget::updateSelectionColor(QString visColorContent)
{
	emit _communicationObject->qt_updateSelectionColor(visColorContent);
}

void SimianViewerPairExpCompWidget::initWebPage()
{
	loaded = true;

	for (QString option : dataOptionBuffer) {
		emit _communicationObject->qt_addAvailableData(option);
	}
	dataOptionBuffer.clear();

	emit widgetInitialized();
}

void SimianViewerPairExpCompWidget::addDataOption(const QString option)
{
	if (loaded)
		emit _communicationObject->qt_addAvailableData(option);
	else
		dataOptionBuffer.append(option);
}


