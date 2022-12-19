#include "PopulationPyramidViewerWidget.h"
#include "PointData.h"
#include "ClusterData.h"
#include "util/FileUtil.h"
#include <fstream>
#include <string>
#include <iostream>
#include <QVBoxLayout>
#include <chrono>
#include <cassert>

PopulationPyramidViewerCommunicationObject::PopulationPyramidViewerCommunicationObject(PopulationPyramidViewerWidget* parent)
	:
	_parent(parent)
{

}



void PopulationPyramidViewerCommunicationObject::js_passSelectionSpecies1ToQt(QString data)
{
	//qDebug() << "\nReceived from Javascript to QT\n";
	_parent->js_passSelectionSpecies1ToQt(data.toStdString());
}


void PopulationPyramidViewerCommunicationObject::js_passSelectionSpecies2ToQt(QString data)
{
	//qDebug() << "\nReceived from Javascript to QT\n";
	_parent->js_passSelectionSpecies2ToQt(data.toStdString());
}

void PopulationPyramidViewerCommunicationObject::js_crossspeciesclusterSelection(QString data)
{
	//qDebug() << "\nReceived from Javascript to QT\n";
	_parent->js_crossspeciesclusterSelection(data.toStdString());
}

PopulationPyramidViewerWidget::PopulationPyramidViewerWidget() :
	loaded(false)
{
	Q_INIT_RESOURCE(PopulationPyramid_viewer_resources);
	_communicationObject = new PopulationPyramidViewerCommunicationObject(this);
	init(_communicationObject);
}

PopulationPyramidViewerWidget::~PopulationPyramidViewerWidget()
{

}

void PopulationPyramidViewerWidget::setData(std::string visDataContent)
{

	emit _communicationObject->qt_setData(QString((visDataContent).c_str()));
}

void PopulationPyramidViewerWidget::setSelectedCrossspeciescluster(QString visDataContent)
{

	emit _communicationObject->qt_setSelectedCrossspeciescluster(visDataContent);
}
//void PopulationPyramidViewerWidget::setBarhighlight(QString Cluster)
//{
//
//	emit _communicationObject->qt_setBarhighlight(Cluster);
//}

void PopulationPyramidViewerWidget::js_passSelectionSpecies1ToQt(std::string selectedIDs)
{
	emit passSelectionSpecies1ToQt(selectedIDs);
}

void PopulationPyramidViewerWidget::js_passSelectionSpecies2ToQt(std::string selectedIDs)
{
	emit passSelectionSpecies2ToQt(selectedIDs);
}

void PopulationPyramidViewerWidget::js_crossspeciesclusterSelection(std::string selectedIDs)
{
	emit crossspeciesclusterSelection(selectedIDs);
}

void PopulationPyramidViewerWidget::initWebPage()
{
	loaded = true;

	for (QString option : dataOptionBuffer) {
		emit _communicationObject->qt_addAvailableData(option);
	}
	dataOptionBuffer.clear();
}

void PopulationPyramidViewerWidget::addDataOption(const QString option)
{
	if (loaded)
		emit _communicationObject->qt_addAvailableData(option);
	else
		dataOptionBuffer.append(option);
}



