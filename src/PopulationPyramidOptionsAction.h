#pragma once

#include <actions/WidgetAction.h>
#include <actions/IntegralAction.h>
#include <actions/OptionAction.h>
#include <actions/OptionsAction.h>
#include <actions/ToggleAction.h>
#include "actions/DatasetPickerAction.h"
#include "PointData/PointData.h"
#include "ClusterData/ClusterData.h"
#include "event/EventListener.h"
#include "actions/Actions.h"
#include "Plugin.h"
#include "DataHierarchyItem.h"
#include "Set.h"
#include <AnalysisPlugin.h>
#include <memory>
#include "PopulationPyramidViewerWidget.h"
#include <algorithm>    
#include <QDebug>
#include <QLabel>
#include <QComboBox>
#include <QGroupBox>
#include <QPushButton>
#include <QGridLayout>
#include <QFormLayout>
#include <QString>
#include <string>
//#include "PopulationPyramidViewerPlugin.h"
#include <event/Event.h>
#include <QDebug>
#include <QLabel>
#include <string>

using namespace hdps::gui;
class QMenu;
class PopulationPyramidViewerPlugin;
//class PopulationPyramidViewerWidget;
class FetchMetaData;
namespace hdps
{
	class CoreInterface;
}

struct speciesStorage
{
	std::string clusterName;
	std::string species1deStatsCount;
	std::string species2deStatsCount;
	std::string deStatsColor;
};

class PopulationPyramidOptionsAction : public WidgetAction
{
public:
	class deStatsDataset1SelectionAction : public WidgetAction
	{
	protected:
		class Widget : public hdps::gui::WidgetActionWidget {
		public:
			Widget(QWidget* parent, deStatsDataset1SelectionAction* deStatsDataset1SelectAction);

			friend class deStatsDataset1SelectionAction;
		};

		QWidget* getWidget(QWidget* parent, const std::int32_t& widgetFlags) override {
			return new deStatsDataset1SelectionAction::Widget(parent, this);
		};

	public:
		deStatsDataset1SelectionAction(PopulationPyramidOptionsAction& PopulationPyramidOptionsAction);

	protected:
		PopulationPyramidOptionsAction& _PopulationPyramidOptionsAction;

		friend class PopulationPyramidOptionsAction;
	};



public:
	void onDataEvent(hdps::DataEvent* dataEvent);
protected:

	class Widget : public hdps::gui::WidgetActionWidget {
	public:
		Widget(QWidget* parent, PopulationPyramidOptionsAction* PopulationPyramidOptionsAction);
	};

	QWidget* getWidget(QWidget* parent, const std::int32_t& widgetFlags) override {
		return new PopulationPyramidOptionsAction::Widget(parent, this);
	};

public:
	PopulationPyramidOptionsAction(PopulationPyramidViewerPlugin& PopulationPyramidViewerPlugin, hdps::CoreInterface* core);

private:
	void updateData();

protected:
	void updateDatasetPickerAction();

public: // Action getters

	DatasetPickerAction& getdeStatsDataset1SelectAction() { return _deStatsDataset1Action; }
	DatasetPickerAction& getdeStatsDataset2SelectAction() { return _deStatsDataset2Action; }
	deStatsDataset1SelectionAction& getdeStatsDataset1SelectionAction() { return _deStatsDataset1SelectionAction; }
	//TriggerAction& getScreenshotAction() { return _screenshotAction; }
	//TriggerAction& getHelpAction() { return _helpAction; }
	StringAction& getGeneName() { return _geneNameAction; }
	//OptionAction& getCrossSpecies1HeatMapCellAction() { return _crossSpecies1HeatMapCellAction; }
	//OptionAction& getCrossSpecies2HeatMapCellAction() { return _crossSpecies2HeatMapCellAction; }
	StringAction& getSelectedCrossspeciescluster() { return _selectedCrossspeciescluster; }
	StringAction& getSpecies1Name() { return _species1Name; }
	StringAction& getSpecies2Name() { return _species2Name; }
	bool& getSelectedCrossspeciesclusterFlag() { return _selectedCrossspeciesclusterFlag; }
	ColorAction& getSelectionColorAction() { return _selectionColorAction; }
public:
	void initLoader();

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

protected:
	PopulationPyramidViewerPlugin& _PopulationPyramidViewerPlugin;
	DatasetPickerAction                 _deStatsDataset1Action;
	DatasetPickerAction                 _deStatsDataset2Action;
	hdps::CoreInterface* _core;
	FetchMetaData* _metaData;
	std::vector<std::vector<std::string>>                _PopulationPyramidData;
	deStatsDataset1SelectionAction               _deStatsDataset1SelectionAction;
	//OptionAction                 _crossSpecies1HeatMapCellAction;
	//OptionAction                 _crossSpecies2HeatMapCellAction;
	//Actions
	//TriggerAction                _screenshotAction;
	//TriggerAction                _helpAction;
	std::map<std::string, speciesStorage> _deStatsDataStorage;
	StringAction                  _species1Name;
	StringAction                  _species2Name;
	StringAction                  _selectedCrossspeciescluster;
	ColorAction             _selectionColorAction;
	bool _selectedCrossspeciesclusterFlag;
	//std::vector<std::string> glia_Neighborhood = { "Astro_1", "Endo_1", "Micro-PVM_1", "OPC_1", "OPC_2", "Oligo_1", "VLMC_1" };
	//std::vector<std::string> it_types_Neighborhood = { "L2/3 IT_1", "L2/3 IT_2", "L2/3 IT_3", "L4 IT_1", "L4 IT_2", "L5 IT_1", "L5 IT_2", "L6 IT Car3_1", "L6 IT Car3_2", "L6 IT_1" };
	//std::vector<std::string> l5et_l56np_l6ct_l6b_Neighborhood = { "L5 ET_1", "L5 ET_2", "L5/6 NP_1", "L5/6 NP_2", "L6 CT_1", "L6 CT_2", "L6b_1", "L6b_2", "L6b_3" };
	//std::vector<std::string> lamp5_sncg_vip_Neighborhood = { "Lamp5_1", "Lamp5_2", "Lamp5_Lhx6_1", "Pax6_1", "Pax6_2", "Sncg_1", "Sncg_2", "Sncg_3", "Vip_1", "Vip_2", "Vip_3", "Vip_4", "Vip_5", "Vip_6", "Vip_7", "Vip_8" };
	//std::vector<std::string> sst_sst_chodl_pvalb_Neighborhood = { "Chandelier_1", "Pvalb_1", "Pvalb_2", "Pvalb_3", "Pvalb_4", "Sst Chodl_1", "Sst_1", "Sst_2", "Sst_3", "Sst_4", "Sst_5", "Sst_6", "Sst_7", "Sst_8", "Sst_9" };
	StringAction _geneNameAction;
	hdps::EventListener     _eventListener;
	friend class ChannelAction;
};