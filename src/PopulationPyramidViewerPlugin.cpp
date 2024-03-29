#include "PopulationPyramidViewerPlugin.h"

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

Q_PLUGIN_METADATA(IID "nl.tudelft.PopulationPyramidViewerPlugin")

using namespace mv;

// =============================================================================
// View
// =============================================================================

PopulationPyramidViewerPlugin::PopulationPyramidViewerPlugin(const PluginFactory* factory) :
	ViewPlugin(factory),
	_PopulationPyramid_viewer(),
	_PopulationPyramidOptionsAction(*this)
{
	setSerializationName("PopulationPyramidViewer");

}

PopulationPyramidViewerPlugin::~PopulationPyramidViewerPlugin()
{
}

void PopulationPyramidViewerPlugin::init()
{

	connect(&_PopulationPyramid_viewer, &PopulationPyramidViewerWidget::widgetInitialized, &_PopulationPyramidOptionsAction, &PopulationPyramidOptionsAction::initLoader);
	_PopulationPyramid_viewer.setPage(":/PopulationPyramid_viewer/PopulationPyramid_viewer.html", "qrc:/PopulationPyramid_viewer/");
	_PopulationPyramid_viewer.setContentsMargins(0, 0, 0, 0);
	_PopulationPyramid_viewer.layout()->setContentsMargins(0, 0, 0, 0);
	//_PopulationPyramidOptionsAction = new PopulationPyramidOptionsAction(*this, _core);
	connect(&_PopulationPyramid_viewer, &PopulationPyramidViewerWidget::passSelectionSpecies1ToQt, this, &PopulationPyramidViewerPlugin::publishSelectionSpecies1);

	connect(&_PopulationPyramid_viewer, &PopulationPyramidViewerWidget::passSelectionSpecies2ToQt, this, &PopulationPyramidViewerPlugin::publishSelectionSpecies2);

	connect(&_PopulationPyramid_viewer, &PopulationPyramidViewerWidget::crossspeciesclusterSelection, this, &PopulationPyramidViewerPlugin::clusterSelection);

	_eventListener.addSupportedEventType(static_cast<std::uint32_t>(EventType::DatasetDataSelectionChanged));
	_eventListener.registerDataEventByType(ClusterType, std::bind(&PopulationPyramidViewerPlugin::onDataEvent, this, std::placeholders::_1));

	auto topToolbarWidget = new QWidget();
	auto topToolbarLayout = new QHBoxLayout();
	topToolbarLayout->setContentsMargins(0, 0, 0, 0);
	topToolbarLayout->setSpacing(0);

	auto ClusterDataset1SelectionWidget = _PopulationPyramidOptionsAction.getdeStatsDataset1SelectionAction().createCollapsedWidget(&getWidget());
	//ClusterDataset1SelectionWidget->setMaximumWidth(280);
	//topToolbarLayout->addWidget(ClusterDataset1SelectionWidget);


	//auto ClusterDataset2SelectionWidget = _PopulationPyramidOptionsAction.getdeStatsDataset2SelectionAction().createCollapsedWidget(&getWidget());
	////ClusterDataset2SelectionWidget->setMaximumWidth(280);
	//topToolbarLayout->addWidget(ClusterDataset2SelectionWidget);

	//topToolbarLayout->addWidget(_PopulationPyramidOptionsAction.getScreenshotAction().createWidget(&getWidget()));
	//topToolbarLayout->addWidget(_PopulationPyramidOptionsAction.getHelpAction().createWidget(&getWidget()));

	topToolbarLayout->addStretch(0);
	topToolbarWidget->setAutoFillBackground(true);
	topToolbarWidget->setLayout(topToolbarLayout);
	auto layout = new QVBoxLayout();
	layout->setContentsMargins(0, 0, 0, 0);
	layout->setSpacing(0);
	layout->addWidget(topToolbarWidget);
	layout->addWidget(&_PopulationPyramid_viewer, 1);
	getWidget().setLayout(layout);

	_PopulationPyramidOptionsAction.initLoader();
}

void PopulationPyramidViewerPlugin::onDataEvent(mv::DatasetEvent* dataEvent)
{
	if (dataEvent->getType() == mv::EventType::DatasetDataSelectionChanged)
	{


	}
}

void PopulationPyramidViewerPlugin::publishSelectionSpecies1(std::string clusterName)
{

	//qDebug() << QString::fromStdString(selectedIDs);
	//_PopulationPyramidOptionsAction.getCrossSpecies1HeatMapCellAction().setCurrentText("");
	//_PopulationPyramidOptionsAction.getCrossSpecies1HeatMapCellAction().setCurrentText(QString::fromStdString(clusterName));
	auto dataset = _PopulationPyramidOptionsAction.getdeStatsDataset1SelectAction().getCurrentDataset();
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

void PopulationPyramidViewerPlugin::clusterSelection(std::string clusterName)
{
	_PopulationPyramidOptionsAction.getSelectedCrossspeciesclusterFlag() = false;
	if (clusterName == "")
	{
		QString::fromStdString(clusterName);
		_PopulationPyramidOptionsAction.getSelectedCrossspeciescluster().setString("");
	}
	else
	{
		//qDebug() << QString::fromStdString(clusterName);
		_PopulationPyramidOptionsAction.getSelectedCrossspeciescluster().setString(QString::fromStdString(clusterName));
	}


}


void PopulationPyramidViewerPlugin::publishSelectionSpecies2(std::string clusterName)
{

	//qDebug() << QString::fromStdString(selectedIDs);
	//_PopulationPyramidOptionsAction.getCrossSpecies2HeatMapCellAction().setCurrentText("");
	//_PopulationPyramidOptionsAction.getCrossSpecies2HeatMapCellAction().setCurrentText(QString::fromStdString(clusterName));
	auto dataset = _PopulationPyramidOptionsAction.getdeStatsDataset2SelectAction().getCurrentDataset();
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

void PopulationPyramidViewerPlugin::fromVariantMap(const QVariantMap& variantMap)
{
	ViewPlugin::fromVariantMap(variantMap);

	_PopulationPyramidOptionsAction.fromParentVariantMap(variantMap);
}

QVariantMap PopulationPyramidViewerPlugin::toVariantMap() const
{
	QVariantMap variantMap = ViewPlugin::toVariantMap();

	_PopulationPyramidOptionsAction.insertIntoVariantMap(variantMap);

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

//PopulationPyramidViewerPluginFactory::PopulationPyramidViewerPluginFactory() :
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


QIcon PopulationPyramidViewerPluginFactory::getIcon(const QColor& color /*= Qt::black*/) const
{
	return Application::getIconFont("FontAwesome").getIcon("chart-bar", color);
}

ViewPlugin* PopulationPyramidViewerPluginFactory::produce()
{
	return new PopulationPyramidViewerPlugin(this);
}

mv::DataTypes PopulationPyramidViewerPluginFactory::supportedDataTypes() const
{
	DataTypes supportedTypes;
	return supportedTypes;
}


mv::gui::PluginTriggerActions PopulationPyramidViewerPluginFactory::getPluginTriggerActions(const mv::Datasets& datasets) const
{
	PluginTriggerActions pluginTriggerActions;

	const auto getInstance = [this]() -> PopulationPyramidViewerPlugin* {
		return dynamic_cast<PopulationPyramidViewerPlugin*>(plugins().requestPlugin(getKind()));
	};

	const auto numberOfDatasets = datasets.count();

	if (PluginFactory::areAllDatasetsOfTheSameType(datasets, PointType)) {
		if (numberOfDatasets >= 1) {
			if (datasets.first()->getDataType() == PointType) {
				auto pluginTriggerAction = new PluginTriggerAction(const_cast<PopulationPyramidViewerPluginFactory*>(this), this, "PopulationPyramid viewer", "Load dataset in PopulationPyramid viewer", getIcon(), [this, getInstance, datasets](PluginTriggerAction& pluginTriggerAction) -> void {
					for (auto dataset : datasets)
						getInstance()->loadData(Datasets({ dataset }));
					});

				pluginTriggerActions << pluginTriggerAction;
			}
		}
	}

	return pluginTriggerActions;
}


//bool PopulationPyramidViewerPluginFactory::hasHelp()
//{
//	return true;
//}