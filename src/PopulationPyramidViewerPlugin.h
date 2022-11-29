#pragma once

#include <ViewPlugin.h>
#include "Dataset.h"
#include "PopulationPyramidOptionsAction.h"
#include "PopulationPyramidViewerWidget.h"
#include "widgets/DropWidget.h"
#include <QBoxLayout>
#include <QLabel>
#include <QStackedWidget>
#include <QList>

using namespace hdps::plugin;
using namespace hdps::util;

class Points;
class PopulationPyramidViewerWidget;
class PopulationPyramidOptionsAction;

// =============================================================================
// View
// =============================================================================

/**
 * PopulationPyramidViewer Plugin
 */
class PopulationPyramidViewerPlugin : public ViewPlugin
{
	Q_OBJECT

public:
	PopulationPyramidViewerPlugin(const PluginFactory* factory);
	~PopulationPyramidViewerPlugin(void) override;

	void init() override;

	void onDataEvent(hdps::DataEvent* dataEvent);

	hdps::CoreInterface* getCore() { return _core; }

	PopulationPyramidViewerWidget* getBarChartWidget() { return _PopulationPyramid_viewer; }
	PopulationPyramidOptionsAction& getPopulationPyramidOptionsAction() { return *_PopulationPyramidOptionsAction; }

protected slots:


private:

	void publishSelectionSpecies1(std::string selectedIDs);
	void publishSelectionSpecies2(std::string selectedIDs);

	PopulationPyramidOptionsAction* _PopulationPyramidOptionsAction;
	/** PopulationPyramidViewer widget displaying cluster data */
	PopulationPyramidViewerWidget* _PopulationPyramid_viewer;
	hdps::EventListener     _eventListener;
};

// =============================================================================
// Factory
// =============================================================================

class PopulationPyramidViewerPluginFactory : public ViewPluginFactory
{
	Q_INTERFACES(hdps::plugin::ViewPluginFactory hdps::plugin::PluginFactory)
		Q_OBJECT
		Q_PLUGIN_METADATA(IID   "nl.tudelft.PopulationPyramidViewerPlugin"
			FILE  "PopulationPyramidViewerPlugin.json")

public:
	PopulationPyramidViewerPluginFactory(void) {}
	~PopulationPyramidViewerPluginFactory(void) override {}

	/**
	 * Get plugin icon
	 * @param color Icon color for flat (font) icons
	 * @return Icon
	 */
	QIcon getIcon(const QColor& color = Qt::black) const override;

	ViewPlugin* produce() override;

	hdps::DataTypes supportedDataTypes() const override;

	/**
	 * Get plugin trigger actions given \p datasets
	 * @param datasets Vector of input datasets
	 * @return Vector of plugin trigger actions
	 */
	PluginTriggerActions getPluginTriggerActions(const hdps::Datasets& datasets) const override;
//public: // Help
//
///**
// * Get whether the plugin has help information or not
// * @return Boolean determining whether the plugin has help information or not
// */
//	bool hasHelp() override;
};
