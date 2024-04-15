#pragma once

#include <ViewPlugin.h>
#include "Dataset.h"
#include "PopulationPyramidOptionsAction.h"
#include "SimianViewerPairExpCompWidget.h"
#include "widgets/DropWidget.h"
#include <QBoxLayout>
#include <QLabel>
#include <QStackedWidget>
#include <QList>

using namespace mv::plugin;
using namespace mv::util;

class Points;
//class SimianViewerPairExpCompWidget;
//class PopulationPyramidOptionsAction;

// =============================================================================
// View
// =============================================================================

/**
 * SimianViewerPairExpComp Plugin
 */
class SimianViewerPairExpCompPlugin : public ViewPlugin
{
	Q_OBJECT

public:
	SimianViewerPairExpCompPlugin(const PluginFactory* factory);
	~SimianViewerPairExpCompPlugin(void) override;

	void init() override;

	void onDataEvent(mv::DatasetEvent* dataEvent);

	mv::CoreInterface* getCore() { return _core; }

	SimianViewerPairExpCompWidget& getBarChartWidget() { return _PopulationPyramid_viewer; }
	PopulationPyramidOptionsAction& getPopulationPyramidOptionsAction() { return _PopulationPyramidOptionsAction; }

public: // Serialization

	/**
	 * Load widget action from variant map
	 * @param Variant map representation of the widget action
	 */
	void fromVariantMap(const QVariantMap& variantMap) override;

	/**
	 * Save widget action to variant map
	 * @return Variant map representation of the widget action
	 */
	QVariantMap toVariantMap() const override;

protected slots:


private:

	void publishSelectionSpecies1(std::string selectedIDs);
	void publishSelectionSpecies2(std::string selectedIDs);
	void clusterSelection(std::string selectedIDs);

	SimianViewerPairExpCompWidget _PopulationPyramid_viewer;
	PopulationPyramidOptionsAction _PopulationPyramidOptionsAction;
	/** SimianViewerPairExpComp widget displaying cluster data */

	mv::EventListener     _eventListener;
};

// =============================================================================
// Factory
// =============================================================================

class SimianViewerPairExpCompPluginFactory : public ViewPluginFactory
{
	Q_INTERFACES(mv::plugin::ViewPluginFactory mv::plugin::PluginFactory)
		Q_OBJECT
		Q_PLUGIN_METADATA(IID   "nl.tudelft.SimianViewerPairExpCompPlugin"
			FILE  "SimianViewerPairExpCompPlugin.json")

public:
	SimianViewerPairExpCompPluginFactory(void) {}
	~SimianViewerPairExpCompPluginFactory(void) override {}

	/**
	 * Get plugin icon
	 * @param color Icon color for flat (font) icons
	 * @return Icon
	 */
	QIcon getIcon(const QColor& color = Qt::black) const override;

	ViewPlugin* produce() override;

	mv::DataTypes supportedDataTypes() const override;

	/**
	 * Get plugin trigger actions given \p datasets
	 * @param datasets Vector of input datasets
	 * @return Vector of plugin trigger actions
	 */
	PluginTriggerActions getPluginTriggerActions(const mv::Datasets& datasets) const override;
	//public: // Help
	//
	///**
	// * Get whether the plugin has help information or not
	// * @return Boolean determining whether the plugin has help information or not
	// */
	//	bool hasHelp() override;
};