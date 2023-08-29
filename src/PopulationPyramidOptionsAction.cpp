#include "PopulationPyramidOptionsAction.h"
#include "PopulationPyramidViewerPlugin.h"
#include<string>  
#include <QFileDialog>
#include <QPageLayout>
#include <QWebEngineView>
using namespace hdps;
using namespace hdps::gui;

PopulationPyramidOptionsAction::PopulationPyramidOptionsAction(PopulationPyramidViewerPlugin& PopulationPyramidViewerPlugin) :
	WidgetAction(&PopulationPyramidViewerPlugin,"PopulationPyramidViewerPlugin"),
	_PopulationPyramidViewerPlugin(PopulationPyramidViewerPlugin),
	_core(hdps::core()),
	_deStatsDataset1Action(this, "DE Dataset1"),
	_deStatsDataset2Action(this, "DE Dataset2"),
	_geneNameAction(this, "SelectedID"),
	//_helpAction(this, "Help"),
	//_screenshotAction(this, "Screenshot"),
	_deStatsDataset1SelectionAction(*this),
	_selectedCrossspeciescluster(this, "Selected CrossSpecies Cluster"),
	_species1Name(this, "Species1Name"),
	_species2Name(this, "Species2Name"),
	_selectionColorAction(this, "Selection color")
	//,
	//_crossSpecies1HeatMapCellAction(this, "Link cross-species1 heatmap cell"),
	//_crossSpecies2HeatMapCellAction(this, "Link cross-species2 heatmap cell")
{
	setSerializationName("PopPyramidSettings");
	_deStatsDataset1Action.setSerializationName("Species1(X-axis)");
	_deStatsDataset2Action.setSerializationName("Species2(Y-axis)");
	_geneNameAction.setSerializationName("Gene");
	_species1Name.setSerializationName("Species1Name");
	_species2Name.setSerializationName("Species2Name");
	_selectedCrossspeciescluster.setSerializationName("Selected CrossSpecies Cluster");
	_deStatsDataset1Action.setDatasetsFilterFunction([this](const hdps::Datasets& datasets) ->hdps::Datasets {
		Datasets statsDatasets;

		for (auto dataset : datasets)
			if (dataset->getDataType() == PointType)
			{
				std::string str1 = dataset->getGuiName().toStdString();
				std::string str2 = "DE_Statistics";
				if (strstr(str1.c_str(), str2.c_str()))
				{
					statsDatasets << dataset;
				}
			}
		return statsDatasets;
		});
	_deStatsDataset2Action.setDatasetsFilterFunction([this](const hdps::Datasets& datasets) ->hdps::Datasets {
		Datasets statsDatasets;

		for (auto dataset : datasets)
			if (dataset->getDataType() == PointType)
			{
				std::string str1 = dataset->getGuiName().toStdString();
				std::string str2 = "DE_Statistics";
				if (strstr(str1.c_str(), str2.c_str()))
				{
					statsDatasets << dataset;
				}
			}
		return statsDatasets;
		});
	_eventListener.addSupportedEventType(static_cast<std::uint32_t>(EventType::DatasetAdded));
	_eventListener.addSupportedEventType(static_cast<std::uint32_t>(EventType::DatasetRemoved));
	_eventListener.addSupportedEventType(static_cast<std::uint32_t>(EventType::DatasetChildAdded));
	_eventListener.addSupportedEventType(static_cast<std::uint32_t>(EventType::DatasetChildRemoved));
	_eventListener.addSupportedEventType(static_cast<std::uint32_t>(EventType::DatasetDataChanged));
	//_eventListener.addSupportedEventType(static_cast<std::uint32_t>(EventType::DatasetGuiNameChanged));
	_eventListener.registerDataEventByType(PointType, std::bind(&PopulationPyramidOptionsAction::onDataEvent, this, std::placeholders::_1));
	//_barSettingsAction.setEnabled(false);
	//_deStatsDataset2SelectionAction.setEnabled(false);
	_geneNameAction.setString("A1BG");
	_species1Name.setString("Species1");
	_species2Name.setString("Species2");
	_selectedCrossspeciesclusterFlag = true;
	_selectedCrossspeciescluster.setString("");
	//_helpAction.setDefaultWidgetFlags(TriggerAction::Icon);
	//_screenshotAction.setDefaultWidgetFlags(TriggerAction::Icon);
	//connect(&_helpAction, &TriggerAction::triggered, this, [this]() -> void {
	//	_PopulationPyramidViewerPlugin.getTriggerHelpAction().trigger();
	//	});
	//_crossSpecies1HeatMapCellAction.setDefaultWidgetFlags(OptionAction::ComboBox);
	//_crossSpecies2HeatMapCellAction.setDefaultWidgetFlags(OptionAction::ComboBox);
	//_crossSpecies2HeatMapCellAction.initialize(QStringList({ " ","exc","glia","inh","Astro_2","Astro_3","Astro_4","Chandelier_1","Chandelier_2","Endo_1","Endo_2","L2/3 IT_1","L2/3 IT_2","L2/3 IT_3","L2/3 IT_4","L4 IT_1","L4 IT_2","L4 IT_3","L4 IT_4","L4 IT_5","L5 ET_1","L5 ET_2","L5 ET_3","L5 ET_4","L5 IT_1","L5 IT_2","L5 IT_3","L5/6 NP_1","L5/6 NP_2","L5/6 NP_3","L5/6 NP_4","L6 CT_1","L6 CT_2","L6 IT Car3_1","L6 IT Car3_2","L6 IT Car3_3","L6 IT_1","L6 IT_2","L6 IT_3","L6b_1","L6b_2","L6b_3","L6b_4","L6b_5","L6b_6","Lamp5_1","Lamp5_2","Lamp5_Lhx6_1","Lamp5_Lhx6_2","Micro-PVM_1","Micro-PVM_2","Micro-PVM_3","OPC_1","OPC_2","OPC_3","Oligo_1","Pax6_1","Pax6_2","Pax6_3","Pax6_4","Pvalb_1","Pvalb_2","Pvalb_3","Pvalb_4","Pvalb_5","Pvalb_6","Pvalb_7","Pvalb_8","Sncg_1","Sncg_2","Sncg_3","Sncg_4","Sncg_5","Sncg_6","Sncg_7","Sst Chodl_1","Sst Chodl_2","Sst Chodl_3","Sst_1","Sst_10","Sst_11","Sst_12","Sst_13","Sst_14","Sst_15","Sst_16","Sst_17","Sst_18","Sst_2","Sst_3","Sst_4","Sst_5","Sst_6","Sst_7","Sst_8","Sst_9","VLMC_1","VLMC_2","VLMC_3","VLMC_4","Vip_1","Vip_10","Vip_11","Vip_12","Vip_13","Vip_14","Vip_15","Vip_16","Vip_17","Vip_2","Vip_3","Vip_4","Vip_5","Vip_6","Vip_7","Vip_8","Vip_9","Astro_5","L2/3 IT_10","L2/3 IT_11","L2/3 IT_12","L2/3 IT_13","L2/3 IT_5","L2/3 IT_6","L2/3 IT_7","L2/3 IT_8","L2/3 IT_9","L5 IT_4","L5 IT_5","L5 IT_6","L5 IT_7","L5/6 NP_5","L5/6 NP_6","L6 CT_3","L6 CT_4","Lamp5_3","Lamp5_4","Lamp5_5","Lamp5_6","Oligo_2","Oligo_3","Oligo_4","Pvalb_10","Pvalb_11","Pvalb_12","Pvalb_13","Pvalb_14","Pvalb_15","Pvalb_9","Sncg_8","Sst_19","Sst_20","Sst_21","Sst_22","Sst_23","Sst_24","Sst_25","Sst_26","Vip_18","Vip_19","Vip_20","Vip_21","Vip_22","Vip_23","Endo_3","L4 IT_6","Micro-PVM_4","OPC_4","Sncg_9","L2/3 IT_14","L2/3 IT_15","L5/6 NP_7","L5/6 NP_8","L6 IT_4","Sncg_10","Glutamatergic","Non-Neuronal","Chandelier","Endo","L2/3 IT","L4 IT","L5 ET","L5 IT","L5/6 NP","L6 CT","L6 IT","L6 IT Car3","L6b","Lamp5","Lamp5_Lhx6","Micro-PVM","OPC","Oligo","Pax6","Pvalb","Sncg","Sst","Sst Chodl","VLMC","Vip","G19.32.002","G20.32.001","G20.32.002","H18.30.002","H19.30.001","H19.30.002","H200.1023","bi006","bi007","Q19.26.011","Q19.26.015","C19.32.002","C19.32.003","C19.32.004","C19.32.005","C19.32.006","C19.32.007","H18.30.001","bi005","Q19.26.010","C19.32.001","it_types","l5et_l56np_l6ct_l6b","lamp5_sncg_vip","sst_sst_chodl_pvalb","Astro_1","GABAergic","Astro","G19.32.001" }), " ", " ");
	//_crossSpecies1HeatMapCellAction.initialize(QStringList({ " ","exc","glia","inh","Astro_2","Astro_3","Astro_4","Chandelier_1","Chandelier_2","Endo_1","Endo_2","L2/3 IT_1","L2/3 IT_2","L2/3 IT_3","L2/3 IT_4","L4 IT_1","L4 IT_2","L4 IT_3","L4 IT_4","L4 IT_5","L5 ET_1","L5 ET_2","L5 ET_3","L5 ET_4","L5 IT_1","L5 IT_2","L5 IT_3","L5/6 NP_1","L5/6 NP_2","L5/6 NP_3","L5/6 NP_4","L6 CT_1","L6 CT_2","L6 IT Car3_1","L6 IT Car3_2","L6 IT Car3_3","L6 IT_1","L6 IT_2","L6 IT_3","L6b_1","L6b_2","L6b_3","L6b_4","L6b_5","L6b_6","Lamp5_1","Lamp5_2","Lamp5_Lhx6_1","Lamp5_Lhx6_2","Micro-PVM_1","Micro-PVM_2","Micro-PVM_3","OPC_1","OPC_2","OPC_3","Oligo_1","Pax6_1","Pax6_2","Pax6_3","Pax6_4","Pvalb_1","Pvalb_2","Pvalb_3","Pvalb_4","Pvalb_5","Pvalb_6","Pvalb_7","Pvalb_8","Sncg_1","Sncg_2","Sncg_3","Sncg_4","Sncg_5","Sncg_6","Sncg_7","Sst Chodl_1","Sst Chodl_2","Sst Chodl_3","Sst_1","Sst_10","Sst_11","Sst_12","Sst_13","Sst_14","Sst_15","Sst_16","Sst_17","Sst_18","Sst_2","Sst_3","Sst_4","Sst_5","Sst_6","Sst_7","Sst_8","Sst_9","VLMC_1","VLMC_2","VLMC_3","VLMC_4","Vip_1","Vip_10","Vip_11","Vip_12","Vip_13","Vip_14","Vip_15","Vip_16","Vip_17","Vip_2","Vip_3","Vip_4","Vip_5","Vip_6","Vip_7","Vip_8","Vip_9","Astro_5","L2/3 IT_10","L2/3 IT_11","L2/3 IT_12","L2/3 IT_13","L2/3 IT_5","L2/3 IT_6","L2/3 IT_7","L2/3 IT_8","L2/3 IT_9","L5 IT_4","L5 IT_5","L5 IT_6","L5 IT_7","L5/6 NP_5","L5/6 NP_6","L6 CT_3","L6 CT_4","Lamp5_3","Lamp5_4","Lamp5_5","Lamp5_6","Oligo_2","Oligo_3","Oligo_4","Pvalb_10","Pvalb_11","Pvalb_12","Pvalb_13","Pvalb_14","Pvalb_15","Pvalb_9","Sncg_8","Sst_19","Sst_20","Sst_21","Sst_22","Sst_23","Sst_24","Sst_25","Sst_26","Vip_18","Vip_19","Vip_20","Vip_21","Vip_22","Vip_23","Endo_3","L4 IT_6","Micro-PVM_4","OPC_4","Sncg_9","L2/3 IT_14","L2/3 IT_15","L5/6 NP_7","L5/6 NP_8","L6 IT_4","Sncg_10","Glutamatergic","Non-Neuronal","Chandelier","Endo","L2/3 IT","L4 IT","L5 ET","L5 IT","L5/6 NP","L6 CT","L6 IT","L6 IT Car3","L6b","Lamp5","Lamp5_Lhx6","Micro-PVM","OPC","Oligo","Pax6","Pvalb","Sncg","Sst","Sst Chodl","VLMC","Vip","G19.32.002","G20.32.001","G20.32.002","H18.30.002","H19.30.001","H19.30.002","H200.1023","bi006","bi007","Q19.26.011","Q19.26.015","C19.32.002","C19.32.003","C19.32.004","C19.32.005","C19.32.006","C19.32.007","H18.30.001","bi005","Q19.26.010","C19.32.001","it_types","l5et_l56np_l6ct_l6b","lamp5_sncg_vip","sst_sst_chodl_pvalb","Astro_1","GABAergic","Astro","G19.32.001" }), " ", " ");
	//_screenshotAction.setEnabled(false);
	//_helpAction.setIcon(Application::getIconFont("FontAwesome").getIcon("question"));
	//_screenshotAction.setIcon(Application::getIconFont("FontAwesome").getIcon("camera"));


	//_deStatsDataset1Action.setConnectionPermissionsFlag(ConnectionPermissionFlag::All);
	//_deStatsDataset1Action.publish("Pop Pyramid:: DE Dataset1");
	//_deStatsDataset2Action.setConnectionPermissionsFlag(ConnectionPermissionFlag::All);
	//_deStatsDataset2Action.publish("Pop Pyramid:: DE Dataset2");
	//_selectedCrossspeciescluster.setConnectionPermissionsFlag(ConnectionPermissionFlag::All);
	//_selectedCrossspeciescluster.connectToPublicActionByName("GlobalSelectedCrossspeciesCluster");

	//_species1Name.setConnectionPermissionsFlag(ConnectionPermissionFlag::All);
	//_species1Name.connectToPublicActionByName("Cluster Differential Expression 1::DatasetName1");
	//_species2Name.setConnectionPermissionsFlag(ConnectionPermissionFlag::All);
	//_species2Name.connectToPublicActionByName("Cluster Differential Expression 1::DatasetName2");
	//_geneNameAction.setConnectionPermissionsFlag(ConnectionPermissionFlag::All);
	//_geneNameAction.connectToPublicActionByName("Cluster Differential Expression 1::LastSelectedId");

	//_selectionColorAction.setConnectionPermissionsFlag(ConnectionPermissionFlag::ConnectViaApi);
	//_selectionColorAction.connectToPublicActionByName("GlobalSelectionColor");
	const auto updatedeStatsDataset1 = [this]() -> void
	{

		if (_deStatsDataset1Action.getCurrentDataset().isValid() && _deStatsDataset2Action.getCurrentDataset().isValid())
		{
			updateData();
		}

		//if (_deStatsDataset1Action.getCurrentDataset().isValid())
		//{
		//	//_barSettingsAction.setEnabled(true);
		//	//updateData(jsonData);
		//	if (_deStatsDataset2Action.getCurrentDataset().isValid())
		//	{
		//		//_barSettingsAction.setEnabled(true);
		//		//_screenshotAction.setEnabled(true);
		//		updateData();
		//	}
		//	else
		//	{
		//		//_deStatsDataset2SelectionAction.setEnabled(true);
		//	}
		//}
		//else
		//{
		//	//_barSettingsAction.setEnabled(false);
		//	//_screenshotAction.setEnabled(false);
		//	//_deStatsDataset2SelectionAction.setEnabled(false);
		//}
	};

	const auto updatedeStatsDataset2 = [this]() -> void
	{
		if (_deStatsDataset1Action.getCurrentDataset().isValid() && _deStatsDataset2Action.getCurrentDataset().isValid())
		{
			updateData();
		}


		//if (_deStatsDataset2Action.getCurrentDataset().isValid())
		//{
			//_barSettingsAction.setEnabled(true);
			//updateData(jsonData);
			//if (_deStatsDataset1Action.getCurrentDataset().isValid())
			//{
				//_barSettingsAction.setEnabled(true);
				//_screenshotAction.setEnabled(true);
		updateData();
		//}
		//else
		//{
			//_deStatsDataset2SelectionAction.setEnabled(false);
			//_screenshotAction.setEnabled(false);
			//_barSettingsAction.setEnabled(false);
		//}
	//}
	//else
	//{
		//_barSettingsAction.setEnabled(false);
	//	//_screenshotAction.setEnabled(false);
	//}
	};
	//const auto updateCrossSpeciesHeatMapCell = [this]() -> void
	//{
	//	if (_crossSpecies1HeatMapCellAction.getCurrentText()== _crossSpecies2HeatMapCellAction.getCurrentText())
	//	{
	//		_PopulationPyramidViewerPlugin.getBarChartWidget()->setBarhighlight(_crossSpecies1HeatMapCellAction.getCurrentText());
	//	}

	//};

	//const auto updateCrossSpecies2HeatMapCell = [this]() -> void
	//{

	//};
	//connect(&_crossSpecies1HeatMapCellAction, &OptionAction::currentIndexChanged, this, [this, updateCrossSpeciesHeatMapCell](const std::int32_t& currentIndex)
	//	{
	//		updateCrossSpeciesHeatMapCell();
	//	});
	//connect(&_crossSpecies2HeatMapCellAction, &OptionAction::currentIndexChanged, this, [this, updateCrossSpeciesHeatMapCell](const std::int32_t& currentIndex)
	//	{
	//		updateCrossSpeciesHeatMapCell();
	//	});

	const auto updateGeneName = [this]() -> void
	{
		if (_deStatsDataset1Action.getCurrentDataset().isValid() && _deStatsDataset2Action.getCurrentDataset().isValid())
		{
			updateData();
		}


	};

	const auto updateSpecies1Name = [this]() -> void
	{
		if (_deStatsDataset1Action.getCurrentDataset().isValid() && _deStatsDataset2Action.getCurrentDataset().isValid())
		{
			updateData();
		}
	};
	const auto updateSpecies2Name = [this]() -> void
	{
		if (_deStatsDataset1Action.getCurrentDataset().isValid() && _deStatsDataset2Action.getCurrentDataset().isValid())
		{
			updateData();
		}
	};

	const auto updateSelectedCrossspeciescluster = [this]() -> void
	{
		if (_selectedCrossspeciesclusterFlag)
		{
			_PopulationPyramidViewerPlugin.getBarChartWidget().setSelectedCrossspeciescluster(_selectedCrossspeciescluster.getString());
		}
		_selectedCrossspeciesclusterFlag = true;

	};

	const auto updateSelectionColor = [this]() -> void
	{
		if (_selectionColorAction.getColor().isValid())
		{
			QColor color = _selectionColorAction.getColor();
			QString hexValueColor = "#" + QString::number(color.red(), 16).rightJustified(2, '0')
				+ QString::number(color.green(), 16).rightJustified(2, '0')
				+ QString::number(color.blue(), 16).rightJustified(2, '0');


			_PopulationPyramidViewerPlugin.getBarChartWidget().updateSelectionColor(hexValueColor);


		}

	};

	connect(&_selectionColorAction, &ColorAction::colorChanged, this, updateSelectionColor);
	//const auto generateScreenshot = [this]() -> void {


	//	QFileDialog saveFileDialog;

	//	saveFileDialog.setAcceptMode(QFileDialog::AcceptSave);
	//	saveFileDialog.setDirectory(QDir::home().absolutePath());

	//	saveFileDialog.selectFile("BarchartViewerScreenshot.pdf");
	//	saveFileDialog.setNameFilter(tr("PDF Files (*.pdf)"));

	//	QString fileName;
	//	if (saveFileDialog.exec())
	//	{
	//		fileName = saveFileDialog.selectedFiles().first();



	//		QPageLayout pl;
	//		QPageSize ps;
	//		//qDebug() << "height" << _simianViewerPlugin.getSimianViewerWidget()->height();

	//		int width = _PopulationPyramidViewerPlugin.getBarChartWidget().width();
	//		int height = _PopulationPyramidViewerPlugin.getBarChartWidget().height();
	//		int reducedWidth = static_cast<double>(width) / 100 * 75;
	//		int reducedHeight = static_cast<double>(height) / 100 * 78;
	//		//qDebug() << "width" << width;
	//		//qDebug() << "reduced width" << reducedWidth;
	//		//qDebug() << "height" << height;
	//		//qDebug() << "reduced height" << reducedHeight;
	//		ps = QPageSize(QSizeF(reducedWidth, reducedHeight), QPageSize::Point, QString(), QPageSize::ExactMatch);
	//		pl.setPageSize(ps);
	//		pl.setOrientation(QPageLayout::Portrait);


	//		_PopulationPyramidViewerPlugin.getBarChartWidget().getPage()->printToPdf(fileName, pl);

	//	}
	//	//..getSimianViewerWidget()->getPage()->printToPdf(fileName, pl);

	//};

	connect(&_geneNameAction, &StringAction::stringChanged, this, updateGeneName);
	connect(&_species1Name, &StringAction::stringChanged, this, updateSpecies1Name);
	connect(&_species2Name, &StringAction::stringChanged, this, updateSpecies2Name);
	connect(&_selectedCrossspeciescluster, &StringAction::stringChanged, this, updateSelectedCrossspeciescluster);
	//connect(&_screenshotAction, &TriggerAction::triggered, this, generateScreenshot);

	connect(&_deStatsDataset1Action, &DatasetPickerAction::datasetPicked, this, updatedeStatsDataset1);

	connect(&_deStatsDataset2Action, &DatasetPickerAction::datasetPicked, this, updatedeStatsDataset2);

	//updateDatasetPickerAction();
}


PopulationPyramidOptionsAction::Widget::Widget(QWidget* parent, PopulationPyramidOptionsAction* PopulationPyramidOptionsAction) :
	WidgetActionWidget(parent, PopulationPyramidOptionsAction)
{
}

void PopulationPyramidOptionsAction::updateData()
{

	auto deStatsDataset1 = _core->requestDataset<Points>(_deStatsDataset1Action.getCurrentDataset().getDatasetId());
	auto clusterDataset1 = _core->requestDataset<Clusters>(deStatsDataset1->getParent().getDatasetId());
	auto geneNames1 = deStatsDataset1->getDimensionNames();
	std::vector<float> geneColumn1;
	auto it1 = std::find(geneNames1.begin(), geneNames1.end(), _geneNameAction.getString());
	if (it1 == geneNames1.end())
	{
		deStatsDataset1->extractDataForDimension(geneColumn1, 0);//name not in vector
		std::fill(geneColumn1.begin(), geneColumn1.end(), 0.0);
	}
	else
	{
		auto index = std::distance(geneNames1.begin(), it1);
		deStatsDataset1->extractDataForDimension(geneColumn1, index);
	}



	auto clusterList1 = clusterDataset1->getClusters();

	auto deStatsDataset2 = _core->requestDataset<Points>(_deStatsDataset2Action.getCurrentDataset().getDatasetId());
	auto clusterDataset2 = _core->requestDataset<Clusters>(deStatsDataset2->getParent().getDatasetId());
	auto geneNames2 = deStatsDataset2->getDimensionNames();
	std::vector<float> geneColumn2;
	auto it2 = std::find(geneNames2.begin(), geneNames2.end(), _geneNameAction.getString());
	if (it2 == geneNames2.end())
	{
		deStatsDataset2->extractDataForDimension(geneColumn2, 0);
		std::fill(geneColumn2.begin(), geneColumn2.end(), 0.0);
	}
	else
	{
		auto index = std::distance(geneNames2.begin(), it2);
		deStatsDataset2->extractDataForDimension(geneColumn2, index);
	}

	auto clusterList2 = clusterDataset2->getClusters();

	_deStatsDataStorage.clear();
	for (int i = 0; i < clusterList1.size(); i++)
	{
		speciesStorage tempStore;
		tempStore.clusterName = clusterList1.at(i).getName().toStdString();
		tempStore.species1deStatsCount = std::to_string(geneColumn1.at(i));
		tempStore.species2deStatsCount = std::to_string(0);
		tempStore.deStatsColor = clusterList1.at(i).getColor().name().toStdString();
		_deStatsDataStorage.insert(std::pair<std::string, speciesStorage>(clusterList1.at(i).getName().toStdString(), tempStore));
	}
	for (int i = 0; i < clusterList2.size(); i++)
	{
		auto deStatsName = clusterList2.at(i).getName().toStdString();


		std::map<std::string, speciesStorage>::iterator it = _deStatsDataStorage.find(deStatsName);
		if (it != _deStatsDataStorage.end()) {
			it->second.species2deStatsCount = std::to_string(geneColumn2.at(i));
		}
		else
		{
			speciesStorage tempStore;
			tempStore.clusterName = clusterList2.at(i).getName().toStdString();
			tempStore.species2deStatsCount = std::to_string(geneColumn2.at(i));
			tempStore.species1deStatsCount = std::to_string(0);
			tempStore.deStatsColor = clusterList2.at(i).getColor().name().toStdString();
			_deStatsDataStorage.insert(std::pair<std::string, speciesStorage>(clusterList2.at(i).getName().toStdString(), tempStore));
		}

	}

	std::string jsonData = "[";

	for (auto ittr = _deStatsDataStorage.rbegin(); ittr != _deStatsDataStorage.rend(); ++ittr)
	{
		//qDebug() << "\n++++++++++++++++++++++++++++++++++++++++++++++++++\n";
		//qDebug() << "clusterName: "<< QString::fromStdString(ittr->second.clusterName);
		//qDebug() << "species1deStatsCount: " << QString::fromStdString(ittr->second.species1deStatsCount);
		//qDebug() << "species2deStatsCount: " << QString::fromStdString(ittr->second.species2deStatsCount);
		//qDebug() << "deStatsColor: " << QString::fromStdString(ittr->second.deStatsColor);
		//qDebug() << "\n++++++++++++++++++++++++++++++++++++++++++++++++++\n";

		jsonData += "{";

		jsonData += '"';
		jsonData += "clusterName";
		jsonData += '"';
		jsonData += ":";
		jsonData += '"';
		jsonData += ittr->second.clusterName;
		jsonData += '"';
		jsonData += ",";
		jsonData += '"';
		jsonData += "species1ClusterCount";
		jsonData += '"';
		jsonData += ":";
		jsonData += ittr->second.species1deStatsCount;
		jsonData += ",";
		jsonData += '"';
		jsonData += "species2ClusterCount";
		jsonData += '"';
		jsonData += ":";
		jsonData += ittr->second.species2deStatsCount;
		jsonData += ",";
		jsonData += '"';
		jsonData += "clusterColor";
		jsonData += '"';
		jsonData += ":";
		jsonData += '"';
		jsonData += ittr->second.deStatsColor;
		jsonData += '"';
		jsonData += ",";
		jsonData += '"';
		jsonData += "species1Name";
		jsonData += '"';
		jsonData += ":";
		jsonData += '"';
		jsonData += _species1Name.getString().toStdString();
		jsonData += '"';
		jsonData += ",";
		jsonData += '"';
		jsonData += "species2Name";
		jsonData += '"';
		jsonData += ":";
		jsonData += '"';
		jsonData += _species2Name.getString().toStdString();
		jsonData += '"';
		jsonData += ",";
		jsonData += '"';
		jsonData += "geneName";
		jsonData += '"';
		jsonData += ":";
		jsonData += '"';
		jsonData += _geneNameAction.getString().toStdString();
		jsonData += '"';
		jsonData += "}";
		jsonData += ",";
	}

	jsonData.pop_back();
	jsonData += "]";


	_PopulationPyramidViewerPlugin.getBarChartWidget().setData(jsonData);
}

//void PopulationPyramidOptionsAction::updateDatasetPickerAction()
//{
//	auto datasets = _core->requestAllDataSets(QVector<hdps::DataType> {PointType});
//	auto filteredDEStatsDatasets = datasets;
//	for (auto dataset : datasets)
//	{
//		std::string str1 = dataset->getGuiName().toStdString();
//		std::string str2 = "DE_Statistics";
//		if (strstr(str1.c_str(), str2.c_str()))
//		{
//		}
//		else {
//			filteredDEStatsDatasets.removeOne(dataset);
//		}
//	}
//
//
//	_deStatsDataset1Action.setDatasets(filteredDEStatsDatasets);
//	_deStatsDataset1Action.setPlaceHolderString("deStats dataset1");
//	_deStatsDataset2Action.setDatasets(filteredDEStatsDatasets);
//	_deStatsDataset2Action.setPlaceHolderString("deStats dataset2");
//	if (filteredDEStatsDatasets.isEmpty())
//	{
//		//_barSettingsAction.setEnabled(false);
//	}
//
//}

PopulationPyramidOptionsAction::deStatsDataset1SelectionAction::Widget::Widget(QWidget* parent, deStatsDataset1SelectionAction* deStatsDataset1SelectAction) :
	WidgetActionWidget(parent, deStatsDataset1SelectAction)
{
	auto& PopulationPyramidOptionsAction = deStatsDataset1SelectAction->_PopulationPyramidOptionsAction;

	auto selectiondeStats1Widget = PopulationPyramidOptionsAction._deStatsDataset1Action.createWidget(this);
	selectiondeStats1Widget->findChild<QComboBox*>("ComboBox")->setSizeAdjustPolicy(QComboBox::AdjustToContents);
	//selectiondeStats1Widget->setMaximumWidth(250);

	auto selectiondeStats2Widget = PopulationPyramidOptionsAction._deStatsDataset2Action.createWidget(this);
	selectiondeStats2Widget->findChild<QComboBox*>("ComboBox")->setSizeAdjustPolicy(QComboBox::AdjustToContents);

	auto selectionExampledeStatsOptionLayout = new QFormLayout();
	selectionExampledeStatsOptionLayout->setContentsMargins(0, 0, 0, 0);

	selectionExampledeStatsOptionLayout->addRow(PopulationPyramidOptionsAction._deStatsDataset1Action.createLabelWidget(this), selectiondeStats1Widget);

	selectionExampledeStatsOptionLayout->addRow(PopulationPyramidOptionsAction._deStatsDataset2Action.createLabelWidget(this), selectiondeStats2Widget);

	selectionExampledeStatsOptionLayout->addRow(PopulationPyramidOptionsAction._species1Name.createLabelWidget(this), PopulationPyramidOptionsAction._species1Name.createWidget(this));

	selectionExampledeStatsOptionLayout->addRow(PopulationPyramidOptionsAction._species2Name.createLabelWidget(this), PopulationPyramidOptionsAction._species2Name.createWidget(this));

	selectionExampledeStatsOptionLayout->addRow(PopulationPyramidOptionsAction._selectedCrossspeciescluster.createLabelWidget(this), PopulationPyramidOptionsAction._selectedCrossspeciescluster.createWidget(this));

	selectionExampledeStatsOptionLayout->addRow(PopulationPyramidOptionsAction._geneNameAction.createLabelWidget(this), PopulationPyramidOptionsAction._geneNameAction.createWidget(this));

	setLayout(selectionExampledeStatsOptionLayout);
}

inline PopulationPyramidOptionsAction::deStatsDataset1SelectionAction::deStatsDataset1SelectionAction(PopulationPyramidOptionsAction& PopulationPyramidOptionsAction) :
	WidgetAction(nullptr, "deStatsDataset1SelectionAction"),
	_PopulationPyramidOptionsAction(PopulationPyramidOptionsAction)
{
	setText("Options");
	setIcon(Application::getIconFont("FontAwesome").getIcon("database"));

}

void PopulationPyramidOptionsAction::onDataEvent(hdps::DatasetEvent* dataEvent)
{
	//if (dataEvent->getType() == hdps::EventType::DataAdded)
	//{
	//	updateDatasetPickerAction();
	//}
	//if (dataEvent->getType() == hdps::EventType::DataRemoved)
	//{
	//	updateDatasetPickerAction();
	//}
	//if (dataEvent->getType() == hdps::EventType::DataChildAdded)
	//{
	//	updateDatasetPickerAction();
	//}
	//if (dataEvent->getType() == hdps::EventType::DataChildRemoved)
	//{
	//	updateDatasetPickerAction();
	//}
	//if (dataEvent->getType() == hdps::EventType::DataChanged)
	//{
	//	updateDatasetPickerAction();
	//}
	//if (dataEvent->getType() == hdps::EventType::DataGuiNameChanged)
	//{
	//	updateDatasetPickerAction();
	//}
}

void PopulationPyramidOptionsAction::initLoader()
{
	if (_deStatsDataset1Action.getCurrentDataset().isValid() && _deStatsDataset2Action.getCurrentDataset().isValid())
	{
		/*qDebug() << "It is here";*/
		updateData();
	}
}

void PopulationPyramidOptionsAction::fromVariantMap(const QVariantMap& variantMap)
{
	WidgetAction::fromVariantMap(variantMap);

	_deStatsDataset1Action.fromParentVariantMap(variantMap);
	_deStatsDataset2Action.fromParentVariantMap(variantMap);
	_geneNameAction.fromParentVariantMap(variantMap);
	_species1Name.fromParentVariantMap(variantMap);
	_species2Name.fromParentVariantMap(variantMap);
	_selectedCrossspeciescluster.fromParentVariantMap(variantMap);

	initLoader();
}

QVariantMap PopulationPyramidOptionsAction::toVariantMap() const
{
	QVariantMap variantMap = WidgetAction::toVariantMap();

	_deStatsDataset1Action.insertIntoVariantMap(variantMap);
	_deStatsDataset2Action.insertIntoVariantMap(variantMap);
	_geneNameAction.insertIntoVariantMap(variantMap);
	_species1Name.insertIntoVariantMap(variantMap);
	_species2Name.insertIntoVariantMap(variantMap);
	_selectedCrossspeciescluster.insertIntoVariantMap(variantMap);

	return variantMap;
}