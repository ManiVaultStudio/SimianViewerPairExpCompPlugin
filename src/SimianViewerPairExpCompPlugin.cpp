#include "SimianViewerPairExpCompPlugin.h"

#include "PointData/PointData.h"
#include "event/Event.h"
#include "ColorData/ColorData.h"

#include <actions/PluginTriggerAction.h>

#include <QtCore>
#include <QtDebug>
#include <QWebEngineView>
#include<ios>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

Q_PLUGIN_METADATA(IID "nl.tudelft.SimianViewerPairExpCompPlugin")

using namespace mv;

// =============================================================================
// View
// =============================================================================

SimianViewerPairExpCompPlugin::SimianViewerPairExpCompPlugin(const PluginFactory* factory) :
	ViewPlugin(factory),
	_SimianViewerPairExpComp_viewer(),
	_SimianViewerPairExpCompOptionsAction(*this)
{
	setSerializationName("SimianViewerPairExpComp");

}

SimianViewerPairExpCompPlugin::~SimianViewerPairExpCompPlugin()
{
}

void SimianViewerPairExpCompPlugin::init()
{

	connect(&_SimianViewerPairExpComp_viewer, &SimianViewerPairExpCompWidget::widgetInitialized, &_SimianViewerPairExpCompOptionsAction, &SimianViewerPairExpCompOptionsAction::initLoader);
	_SimianViewerPairExpComp_viewer.setPage(":/SimianViewerPairExpComp_viewer/SimianViewerPairExpComp_viewer.html", "qrc:/SimianViewerPairExpComp_viewer/");
	_SimianViewerPairExpComp_viewer.setContentsMargins(0, 0, 0, 0);
	_SimianViewerPairExpComp_viewer.layout()->setContentsMargins(0, 0, 0, 0);
	//_SimianViewerPairExpCompOptionsAction = new SimianViewerPairExpCompOptionsAction(*this, _core);
	connect(&_SimianViewerPairExpComp_viewer, &SimianViewerPairExpCompWidget::passSelectionSpecies1ToQt, this, &SimianViewerPairExpCompPlugin::publishSelectionSpecies1);

	connect(&_SimianViewerPairExpComp_viewer, &SimianViewerPairExpCompWidget::passSelectionSpecies2ToQt, this, &SimianViewerPairExpCompPlugin::publishSelectionSpecies2);

	connect(&_SimianViewerPairExpComp_viewer, &SimianViewerPairExpCompWidget::crossspeciesclusterSelection, this, &SimianViewerPairExpCompPlugin::clusterSelection);

	_eventListener.addSupportedEventType(static_cast<std::uint32_t>(EventType::DatasetDataSelectionChanged));
	_eventListener.registerDataEventByType(ClusterType, std::bind(&SimianViewerPairExpCompPlugin::onDataEvent, this, std::placeholders::_1));

	auto topToolbarWidget = new QWidget();
	auto topToolbarLayout = new QHBoxLayout();
	topToolbarLayout->setContentsMargins(0, 0, 0, 0);
	topToolbarLayout->setSpacing(0);

	auto ClusterDataset1SelectionWidget = _SimianViewerPairExpCompOptionsAction.getdeStatsDataset1SelectionAction().createCollapsedWidget(&getWidget());
	//ClusterDataset1SelectionWidget->setMaximumWidth(280);
	//topToolbarLayout->addWidget(ClusterDataset1SelectionWidget);


	//auto ClusterDataset2SelectionWidget = _SimianViewerPairExpCompOptionsAction.getdeStatsDataset2SelectionAction().createCollapsedWidget(&getWidget());
	////ClusterDataset2SelectionWidget->setMaximumWidth(280);
	//topToolbarLayout->addWidget(ClusterDataset2SelectionWidget);

	//topToolbarLayout->addWidget(_SimianViewerPairExpCompOptionsAction.getScreenshotAction().createWidget(&getWidget()));
	//topToolbarLayout->addWidget(_SimianViewerPairExpCompOptionsAction.getHelpAction().createWidget(&getWidget()));

	topToolbarLayout->addStretch(0);
	topToolbarWidget->setAutoFillBackground(true);
	topToolbarWidget->setLayout(topToolbarLayout);
	auto layout = new QVBoxLayout();
	layout->setContentsMargins(0, 0, 0, 0);
	layout->setSpacing(0);
	layout->addWidget(topToolbarWidget);
	layout->addWidget(&_SimianViewerPairExpComp_viewer, 1);
	getWidget().setLayout(layout);

	_SimianViewerPairExpCompOptionsAction.initLoader();
}

void SimianViewerPairExpCompPlugin::onDataEvent(mv::DatasetEvent* dataEvent)
{
	if (dataEvent->getType() == mv::EventType::DatasetDataSelectionChanged)
	{


	}
}

void SimianViewerPairExpCompPlugin::publishSelectionSpecies1(std::string clusterName)
{

	//qDebug() << QString::fromStdString(selectedIDs);
	//_SimianViewerPairExpCompOptionsAction.getCrossSpecies1HeatMapCellAction().setCurrentText("");
	//_SimianViewerPairExpCompOptionsAction.getCrossSpecies1HeatMapCellAction().setCurrentText(QString::fromStdString(clusterName));
	auto dataset = _SimianViewerPairExpCompOptionsAction.getdeStatsDataset1SelectAction().getCurrentDataset();
	const auto candidateDataset = _core->requestDataset<Clusters>(dataset.getDatasetId());
	std::vector<std::uint32_t> selectedIndices;
	for (const auto& cluster : candidateDataset->getClusters())
	{
		if (cluster.getName() == QString::fromStdString(clusterName))
		{
			for (const auto& index : cluster.getIndices())
			{
				selectedIndices.push_back(index);
			}
		}

	}

	candidateDataset->getParent()->setSelectionIndices(selectedIndices);


	events().notifyDatasetDataSelectionChanged(candidateDataset->getParent());

}

void SimianViewerPairExpCompPlugin::clusterSelection(std::string clusterName)
{
	_SimianViewerPairExpCompOptionsAction.getSelectedCrossspeciesclusterFlag() = false;
	if (clusterName == "")
	{
		QString::fromStdString(clusterName);
		_SimianViewerPairExpCompOptionsAction.getSelectedCrossspeciescluster().setString("");
	}
	else
	{
		//qDebug() << QString::fromStdString(clusterName);
		_SimianViewerPairExpCompOptionsAction.getSelectedCrossspeciescluster().setString(QString::fromStdString(clusterName));
	}


}


void SimianViewerPairExpCompPlugin::publishSelectionSpecies2(std::string clusterName)
{

	//qDebug() << QString::fromStdString(selectedIDs);
	//_SimianViewerPairExpCompOptionsAction.getCrossSpecies2HeatMapCellAction().setCurrentText("");
	//_SimianViewerPairExpCompOptionsAction.getCrossSpecies2HeatMapCellAction().setCurrentText(QString::fromStdString(clusterName));
	auto dataset = _SimianViewerPairExpCompOptionsAction.getdeStatsDataset2SelectAction().getCurrentDataset();
	const auto candidateDataset = _core->requestDataset<Clusters>(dataset.getDatasetId());
	std::vector<std::uint32_t> selectedIndices;
	for (const auto& cluster : candidateDataset->getClusters())
	{
		if (cluster.getName() == QString::fromStdString(clusterName))
		{
			for (const auto& index : cluster.getIndices())
			{
				selectedIndices.push_back(index);
			}
		}

	}

	candidateDataset->getParent()->setSelectionIndices(selectedIndices);


	events().notifyDatasetDataSelectionChanged(candidateDataset->getParent());

}

void SimianViewerPairExpCompPlugin::fromVariantMap(const QVariantMap& variantMap)
{
	ViewPlugin::fromVariantMap(variantMap);

	_SimianViewerPairExpCompOptionsAction.fromParentVariantMap(variantMap);
}

QVariantMap SimianViewerPairExpCompPlugin::toVariantMap() const
{
	QVariantMap variantMap = ViewPlugin::toVariantMap();

	_SimianViewerPairExpCompOptionsAction.insertIntoVariantMap(variantMap);

	return variantMap;
}
//const auto showHelpbox = []() -> void
//{
//	qDebug() << "Population pyramid viewer plugin help requested...";
//	QMessageBox msgBox;
//	msgBox.setTextFormat(Qt::RichText); // this does the magic trick and allows you to click the link
//	msgBox.setText("<div>Population pyramid viewer</div>");
//	//msgBox.setIcon(yourIcon);
//	msgBox.exec();
//};

//SimianViewerPairExpCompPluginFactory::SimianViewerPairExpCompPluginFactory() :
//	ViewPluginFactory()
//{
//	connect(&getTriggerHelpAction(), &TriggerAction::triggered, this, [this]() -> void {
//		// Do your stuff here
//
//		showHelpbox();
//
//		});
//}

// =============================================================================
// Factory
// =============================================================================


QIcon SimianViewerPairExpCompPluginFactory::getIcon(const QColor& color /*= Qt::black*/) const
{
	return Application::getIconFont("FontAwesome").getIcon("chart-bar", color);
}

ViewPlugin* SimianViewerPairExpCompPluginFactory::produce()
{
	return new SimianViewerPairExpCompPlugin(this);
}

mv::DataTypes SimianViewerPairExpCompPluginFactory::supportedDataTypes() const
{
	DataTypes supportedTypes;
	return supportedTypes;
}


mv::gui::PluginTriggerActions SimianViewerPairExpCompPluginFactory::getPluginTriggerActions(const mv::Datasets& datasets) const
{
	PluginTriggerActions pluginTriggerActions;

	const auto getInstance = [this]() -> SimianViewerPairExpCompPlugin* {
		return dynamic_cast<SimianViewerPairExpCompPlugin*>(plugins().requestPlugin(getKind()));
	};

	const auto numberOfDatasets = datasets.count();

	if (PluginFactory::areAllDatasetsOfTheSameType(datasets, PointType)) {
		if (numberOfDatasets >= 1) {
			if (datasets.first()->getDataType() == PointType) {
				auto pluginTriggerAction = new PluginTriggerAction(const_cast<SimianViewerPairExpCompPluginFactory*>(this), this, "SimianViewerPairExpComp viewer", "Load dataset in SimianViewerPairExpComp viewer", getIcon(), [this, getInstance, datasets](PluginTriggerAction& pluginTriggerAction) -> void {
					for (auto dataset : datasets)
						getInstance()->loadData(Datasets({ dataset }));
					});

				pluginTriggerActions << pluginTriggerAction;
			}
		}
	}

	return pluginTriggerActions;
}


//bool SimianViewerPairExpCompPluginFactory::hasHelp()
//{
//	return true;
//}