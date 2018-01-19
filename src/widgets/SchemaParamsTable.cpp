#include "SchemaParamsTable.h"
#include "ElementImagesProvider.h"
#include "PixmapItemDelegate.h"

#include <QHeaderView>
#include <QMenu>

SchemaParamsTable::SchemaParamsTable(Schema *schema, QWidget *parent) : QTableWidget(0, COL_COUNT, parent)
{
    _schema = schema;

    auto iconSize = ElementImagesProvider::instance().iconSize();

    setItemDelegate(new PixmapDelegate(iconSize));
    setContextMenuPolicy(Qt::CustomContextMenu);
    setAlternatingRowColors(true);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    horizontalHeader()->setSectionResizeMode(COL_IMAGE, QHeaderView::Fixed);
    horizontalHeader()->setMinimumSectionSize(iconSize.width()+4);
    horizontalHeader()->resizeSection(COL_IMAGE, iconSize.width()+4);
    horizontalHeader()->setSectionResizeMode(COL_ALIAS, QHeaderView::ResizeToContents);
    horizontalHeader()->setSectionResizeMode(COL_VALUE, QHeaderView::ResizeToContents);
    horizontalHeader()->setSectionResizeMode(COL_ANNOTATION, QHeaderView::Stretch);
    horizontalHeader()->setHighlightSections(false);
    setHorizontalHeaderLabels({ tr("Typ"), tr("Name"), tr("Value"), tr("Annotation") });

    connect(this, SIGNAL(itemDoubleClicked(QTableWidgetItem*)), this, SLOT(doubleClicked(QTableWidgetItem*)));
    connect(this, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(showContextMenu(const QPoint&)));
}

SchemaParamsTable::~SchemaParamsTable()
{
    for (auto p: *(schema()->params()))
        p->removeListener(this);
}

void SchemaParamsTable::adjustColumns()
{
    resizeColumnToContents(COL_ALIAS);
    resizeColumnToContents(COL_VALUE);
}

void SchemaParamsTable::doubleClicked(QTableWidgetItem*)
{
    Z::Parameter* param = selected();
    if (param)
        emit doubleClicked(param);
}

void SchemaParamsTable::showContextMenu(const QPoint& pos)
{
    if (_contextMenu)
        _contextMenu->popup(mapToGlobal(pos));
}

Z::Parameter* SchemaParamsTable::selected() const
{
    return schema()->params()->byIndex(currentRow());
}

void SchemaParamsTable::setSelected(Z::Parameter *param)
{
    setCurrentCell(_schema->params()->indexOf(param), 0);
}

void SchemaParamsTable::populate()
{
    clearContents();
    setRowCount(schema()->params()->size());
    for (int row = 0; row < schema()->params()->size(); row++)
    {
        auto param = schema()->params()->byIndex(row);
        param->addListener(this);
        createRow(param, row);
        populateRow(param, row);
    }
    adjustColumns();
}

void SchemaParamsTable::createRow(Z::Parameter *param, int row)
{
    QTableWidgetItem *it = new QTableWidgetItem();
    //TODO it->setData(0, QPixmap(ElementImagesProvider::instance().iconPath(elem->type())));
    it->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    setItem(row, COL_IMAGE, it);

    it = new QTableWidgetItem();
    auto f = it->font();
    f.setBold(true);
    f.setPointSize(f.pointSize()+2);
    it->setFont(f);
    it->setTextAlignment(Qt::AlignCenter);
    it->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    setItem(row, COL_ALIAS, it);

    it = new QTableWidgetItem();
    it->setTextAlignment(Qt::AlignCenter);
    it->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    setItem(row, COL_VALUE, it);

    it = new QTableWidgetItem();
    it->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    setItem(row, COL_ANNOTATION, it);
}

void SchemaParamsTable::populateRow(Z::Parameter *param, int row)
{
    item(row, COL_ALIAS)->setText(param->alias());
    item(row, COL_VALUE)->setText(param->value().str());
    item(row, COL_ANNOTATION)->setText(param->description());
}

void SchemaParamsTable::schemaLoaded(Schema*)
{
    populate();
}

void SchemaParamsTable::parameterCreated(Z::Parameter *param)
{
    int row = rowCount();
    setRowCount(row+1);
    createRow(param, row);
    populateRow(param, row);
    setSelected(param);
    param->addListener(this);
}

void SchemaParamsTable::parameterChanged(Z::ParameterBase* param)
{
    auto p = dynamic_cast<Z::Parameter*>(param);
    auto row = schema()->params()->indexOf(p);
    if (row >= 0)
        item(row, COL_VALUE)->setText(p->value().str());
}