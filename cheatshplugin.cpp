#include "cheatshplugin.h"
#include "cheatshconstants.h"
#include "cheatfilter.h"
#include "optionspage.h"

#include <coreplugin/icore.h>
#include <coreplugin/icontext.h>
#include <coreplugin/actionmanager/actionmanager.h>
#include <coreplugin/actionmanager/command.h>
#include <coreplugin/actionmanager/actioncontainer.h>
#include <coreplugin/coreconstants.h>

#include <coreplugin/editormanager/editormanager.h>
#include <coreplugin/editormanager/editorwindow.h>
//#include <coreplugin/editormanager/editorarea.h>
#include <coreplugin/editormanager/ieditor.h>
#include <texteditor/texteditorconstants.h>
#include <texteditor/texteditor.h>
#include <extensionsystem/pluginmanager.h>
#include <cppeditor/cppeditorconstants.h>

#include <coreplugin/locator/locatormanager.h>
#include <coreplugin/locator/locatorconstants.h>
#include <coreplugin/locator/locator.h>
#include <coreplugin/locator/commandlocator.h>
#include <utils/parameteraction.h>

#include <QAction>
#include <QMessageBox>
#include <QMainWindow>
#include <QMenu>

#include <QListWidget>
#include <QString>
#include <QObject>
#include <QDebug>
#include <QTextCursor>

namespace CheatSh {
namespace Internal {

CheatShPlugin::CheatShPlugin()
{
    // Create your members
}

CheatShPlugin::~CheatShPlugin()
{
    // Unregister objects from the plugin manager's object pool
    // Delete members
}

bool CheatShPlugin::initialize(const QStringList &arguments, QString *errorString)
{
    // Register objects in the plugin manager's object pool
    // Load settings
    // Add actions to menus
    // Connect to other plugins' signals
    // In the initialize function, a plugin can be sure that the plugins it
    // depends on have initialized their members.
    Q_UNUSED(arguments)
    Q_UNUSED(errorString)

//    cheat_out_plane_ = new CheatOutputPlane();
//    ExtensionSystem::PluginManager::addObject(cheat_out_plane_);

////    ExtensionSystem::PluginManager *pm = ExtensionSystem::PluginManager::instance();
////    QList<QObject*> objects = pm->allObjects();
////    QListWidget* listWidget = new QListWidget;
////    Q_FOREACH(QObject* obj, objects)
////    {
////        QString objInfo = QString("%1 (%2)")
////        .arg(obj->objectName())
////        .arg(QString::fromUtf8(obj->metaObject()->className()));
////        listWidget->addItem(objInfo);
////    }
////    listWidget->show();


//    Core::Context textContext( TextEditor::Constants::C_TEXTEDITOR );
//    QAction* actionCheatSh = new QAction( tr( "Cheat.sh" ), this );
//    auto cheatShCommand = Core::ActionManager::registerAction(actionCheatSh, Constants::ACTION_ID, textContext);
//    cheatShCommand->setAttribute(Core::Command::CA_UpdateText);   //Зачем?
//    cheatShCommand->setDefaultKeySequence(QKeySequence(tr("Ctrl+Alt+Meta+C")));
//    connect(actionCheatSh, &QAction::triggered, [](){
//        qDebug("Cheat sh");
//    });

//    Core::ActionContainer* menu = Core::ActionManager::createMenu( Constants::MENU_ID );
//    menu->menu()->setTitle( tr( "CheatSh" ) );
//    menu->addAction( cheatShCommand );
//    Core::ActionManager::actionContainer( Core::Constants::M_TOOLS )->addMenu( menu );

//    Core::ActionContainer* editorcontextMenu =
//            Core::ActionManager::createMenu( TextEditor::Constants::M_STANDARDCONTEXTMENU );
//    Core::ActionContainer* contextMenu =
//            //Core::ActionManager::createMenu( TextEditor::Constants::M_STANDARDCONTEXTMENU );
//            Core::ActionManager::createMenu( Constants::CONTEXT_MENU_ID );
//    contextMenu->menu()->setTitle( tr( "CheatSh" ) );
//    contextMenu->addSeparator();
//    contextMenu->addAction( cheatShCommand );
//    contextMenu->addSeparator();
//    editorcontextMenu->addMenu(contextMenu);
////    contextMenu->menu()->setEnabled(true);

////    Core::EditorManager* editorManager = Core::EditorManager::instance();
////    connect(editorManager, &Core::EditorManager::currentEditorChanged, [](){
////        qDebug("edtior changed");
////    });

//    connect(actionCheatSh, &QAction::triggered, [this](){
//        TextEditor::TextEditorWidget* editorWidget =
//                qobject_cast<TextEditor::TextEditorWidget*> (
//                    Core::EditorManager::currentEditor()->widget()
//                );

//        QString selected_text = editorWidget->selectedText();
//        if(selected_text.isEmpty()) {
//            QTextCursor text_cursor = editorWidget->textCursor();
//            text_cursor.select(QTextCursor::WordUnderCursor);
//            selected_text = text_cursor.selectedText();
//        }
//        qDebug("selection: '%s'", qPrintable(selected_text));
//        cheat_out_plane_->find(selected_text);
//    });

    CheatFilter* cheat_filter = new CheatFilter();

    // good code below

    settings_.load(Core::ICore::settings());
    createOptionsPage();
    createOutputPane();

    connect(Core::ICore::instance(), &Core::ICore::saveSettingsRequested,
            this, [this](){ settings_.save(Core::ICore::settings()); });

    return true;
}

void CheatShPlugin::extensionsInitialized()
{
    // Retrieve objects from the plugin manager's object pool
    // In the extensionsInitialized function, a plugin can be sure that all
    // plugins that depend on it are completely initialized.
}

ExtensionSystem::IPlugin::ShutdownFlag CheatShPlugin::aboutToShutdown()
{
    // Save settings
    // Disconnect from signals that are not needed during shutdown
    // Hide UI (if you add UI that is not in the main window directly)
    return SynchronousShutdown;
}

void CheatShPlugin::changeSettings(const Settings& settings)
{
    settings.save(Core::ICore::settings());
    settings_ = settings;

    //TODO: apply settings
//    m_todoItemsProvider->settingsChanged(m_settings);
//    m_todoOutputPane->setScanningScope(m_settings.scanningScope);
//    m_optionsPage->setSettings(m_settings);
}

void CheatShPlugin::triggerAction()
{
    QMessageBox::information(Core::ICore::mainWindow(),
                             tr("Action Triggered"),
                             tr("This is an action from CheatSh."));
}

void CheatShPlugin::createOptionsPage()
{
    options_page_ = new OptionsPage(settings_, this);
    connect(options_page_, &OptionsPage::settingsChanged,
            this, &CheatShPlugin::changeSettings);
}

void CheatShPlugin::createOutputPane()
{
    cheat_out_plane_ = new CheatOutputPlane(&settings_);

//    ExtensionSystem::PluginManager::addObject(cheat_out_plane_); //Похоже не нужно

    //TODO: connections
}

} // namespace Internal
} // namespace CheatSh
