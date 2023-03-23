#pragma once

//#include "SelectionListener.h"
#include "PointData.h"
#include "widgets/WebWidget.h"
#include <QMouseEvent>
#include <QComboBox>
#include <QList>
#include <QVariant>

class QWebEngineView;
class QWebEnginePage;
class QWebChannel;


class PopulationPyramidViewerWidget;

class PopulationPyramidViewerCommunicationObject : public hdps::gui::WebCommunicationObject
{
	Q_OBJECT
public:
	PopulationPyramidViewerCommunicationObject(PopulationPyramidViewerWidget* parent);

signals:
	void qt_setData(QString data);
	void qt_setSelectedCrossspeciescluster(QString data);
	void qt_addAvailableData(QString name);
	void qt_updateSelectionColor(QString data);
	//void qt_setBarhighlight(QString clusterName);


public slots:
	void js_passSelectionSpecies1ToQt(QString data);
	void js_passSelectionSpecies2ToQt(QString data);
	void js_crossspeciesclusterSelection(QString data);
private:
	PopulationPyramidViewerWidget* _parent;
};

class PopulationPyramidViewerWidget : public hdps::gui::WebWidget
{
	Q_OBJECT
public:
	PopulationPyramidViewerWidget();
	~PopulationPyramidViewerWidget() override;

	void addDataOption(const QString option);
	void setData(std::string visDataContent);
	void setSelectedCrossspeciescluster(QString visDataContent);
	void updateSelectionColor(QString visColorContent);
	//void setBarhighlight(QString clusterName);

protected:


signals:
	void widgetInitialized();
	void passSelectionSpecies1ToQt(std::string selectedIDs);
	void passSelectionSpecies2ToQt(std::string selectedIDs);
	void crossspeciesclusterSelection(std::string selectedIDs);


public:

	void js_passSelectionSpecies1ToQt(std::string selectedIDs);
	void js_passSelectionSpecies2ToQt(std::string selectedIDs);
	void js_crossspeciesclusterSelection(std::string selectedIDs);

private slots:
	void initWebPage() override;

private:
	PopulationPyramidViewerCommunicationObject* _communicationObject;


	/** Whether the web view has loaded and web-functions are ready to be called. */
	bool loaded;
	/** Temporary storage for added data options until webview is loaded */
	QList<QString> dataOptionBuffer;
};
