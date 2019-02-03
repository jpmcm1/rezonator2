#ifndef SCHEMA_WINDOW_H
#define SCHEMA_WINDOW_H

#include "SchemaWindows.h"
#include "core/Schema.h"
#include "core/Element.h"

QT_BEGIN_NAMESPACE
class QMenu;
class QAction;
class QShortcut;
QT_END_NAMESPACE

class CalcManager;

/**
    Basic window containing visual representation of schema (element list, layout)
    and holding actions controlling the schema (append, remove elements, etc.).
*/
class SchemaViewWindow: public SchemaMdiChild, public EditableWindow
{
    Q_OBJECT

public:
    SchemaViewWindow(Schema*, CalcManager*);
    ~SchemaViewWindow() override;

    // inherits from BasicMdiChild
    QList<QMenu*> menus() override { return { menuElement }; }

    // inherits from SchemaListener
    void elementCreated(Schema*, Element*) override;

    // inherits from EditableWindow
    SupportedCommands supportedCommands() override {
        return EditCmd_Copy | EditCmd_Paste | EditCmd_SelectAll; }
    bool canCopy() override;
    bool canPaste() override { return true; }
    void selectAll() override;

public slots:
    void copy() override;
    void paste() override;

protected:
    // SchemaViewWindow is always visible and can't be closed.
    void closeEvent(QCloseEvent *event) override { event->ignore(); }

private:
    QAction *actnElemAdd, *actnElemMoveUp, *actnElemMoveDown, *actnElemProp,
        *actnElemMatr, *actnElemMatrAll, *actnElemDelete, *actnEditCopy, *actnEditPaste;

    QMenu *menuElement, *menuContextElement, *menuContextLastRow;

    QShortcut* shortcutAddFromLastRow;

    class SchemaLayout *_layout;
    class SchemaElemsTable *_table;
    CalcManager* _calculations;

    bool _pasteMode = false;

    void createActions();
    void createMenuBar();
    void createToolBar();

    void editElement(Element* elem);

private slots:
    void actionElemAdd();
    void actionElemMoveUp();
    void actionElemMoveDown();
    void actionElemProp();
    void actionElemDelete();
    void rowDoubleClicked(Element*);
    void currentCellChanged(int curRow, int, int prevRow, int);
};

#endif // SCHEMA_WINDOW_H
