#include "cheatshplugin.h"
#include "cheatshconstants.h"
#include "cheatfilter.h"
#include "cheatsh.h"
#include "cheatoutputplane.h"
#include "optionspage.h"
#include "updatechecker.h"
#include "cheatsh_global.h"

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
#include <QTranslator>

#include <QDirIterator> //

using namespace Core;

namespace CheatSh {
namespace Internal {

CheatShPlugin::CheatShPlugin()
{
//    QDirIterator it(":", QDirIterator::Subdirectories);
//    while (it.hasNext()) {
//        qDebug() << it.next();
//    }
    // Create your members
    const QLocale locale(ICore::userInterfaceLanguage());
    QTranslator *translator = new QTranslator(this);
    if (translator->load(locale, QLatin1String("cheatsh"), QLatin1String("_"), QLatin1String(":/i18n")))
        QCoreApplication::installTranslator(translator);
    else
        delete translator;
}

CheatShPlugin::~CheatShPlugin()
{
    // Unregister objects from the plugin manager's object pool
    // Delete members
    delete action_cheat_sh_;
    delete out_plane_;
    delete options_page_;
    delete cheat_sh_;
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

    settings_.load(Core::ICore::settings());

    out_plane_ = new CheatOutputPlane(&settings_, this);
    cheat_sh_ = new Cheat(&settings_, this);
    cheat_filter_ = std::make_unique<CheatFilter>();
    options_page_ = new OptionsPage(settings_, this);
    connect(cheat_sh_, &Cheat::found, out_plane_, &CheatOutputPlane::displayResult);
    connect(cheat_filter_.get(), &CheatFilter::query, cheat_sh_, &Cheat::search);
    connect(options_page_, &OptionsPage::settingsChanged, this, &CheatShPlugin::changeSettings);
    createMenus();
    update_checker_ = new UpdateChecker(&settings_, this);

    connect(update_checker_, &UpdateChecker::updateAvaliable, out_plane_, &CheatOutputPlane::displayHtml);

    connect(Core::ICore::instance(), &Core::ICore::saveSettingsRequested,
            this, [this](){ settings_.save(Core::ICore::settings()); });


    return true;
}

void CheatShPlugin::extensionsInitialized()
{
    // Retrieve objects from the plugin manager's object pool
    // In the extensionsInitialized function, a plugin can be sure that all
    // plugins that depend on it are completely initialized.
    update_checker_->checkUpdatesIfPossible();
}

ExtensionSystem::IPlugin::ShutdownFlag CheatShPlugin::aboutToShutdown()
{
    // Save settings
    // Disconnect from signals that are not needed during shutdown
    // Hide UI (if you add UI that is not in the main window directly)
    cheat_filter_->disconnect();
    action_cheat_sh_->disconnect();
    options_page_->disconnect();
    cheat_sh_->disconnect();
    update_checker_->disconnect();
    out_plane_->hide();
    return SynchronousShutdown;
}

void CheatShPlugin::changeSettings(const Settings& settings)
{
    settings.save(Core::ICore::settings());
    settings_ = settings;
}

void CheatShPlugin::createMenus()
{
    // create actions:
    Core::Context textContext( TextEditor::Constants::C_TEXTEDITOR );
    action_cheat_sh_ = new QAction( tr( "Search cheat.sh" ), this );
    Core::Command* cheatShCommand = Core::ActionManager::registerAction(action_cheat_sh_, Constants::ACTION_ID, textContext);
    cheatShCommand->setAttribute(Core::Command::CA_UpdateText);   //Зачем?
    cheatShCommand->setDefaultKeySequence(QKeySequence(tr("Meta+Shift+C")));

    // connect actions
    connect(action_cheat_sh_, &QAction::triggered, [this](){
        TextEditor::TextEditorWidget* editorWidget =
                qobject_cast<TextEditor::TextEditorWidget*> (
                    Core::EditorManager::currentEditor()->widget()
                    );

        QString selected_text = editorWidget->selectedText();
        if(selected_text.isEmpty()) {
            QTextCursor text_cursor = editorWidget->textCursor();
            text_cursor.select(QTextCursor::WordUnderCursor);
            selected_text = text_cursor.selectedText();
        }
//        qDebug("selection: '%s'", qPrintable(selected_text));
        cheat_sh_->search(selected_text);
    });

    // add actions to tools menu
    Core::ActionContainer* menu = Core::ActionManager::createMenu( Constants::MENU_ID );
    menu->menu()->setTitle( tr( "CheatSh" ) );
    menu->addAction( cheatShCommand );
    Core::ActionManager::actionContainer( Core::Constants::M_TOOLS )->addMenu( menu );

    // add actions to context menu

    Core::ActionContainer* editorcontextMenu =
            Core::ActionManager::createMenu( TextEditor::Constants::M_STANDARDCONTEXTMENU );
    Core::ActionContainer* contextMenu =
            //Core::ActionManager::createMenu( TextEditor::Constants::M_STANDARDCONTEXTMENU );
            Core::ActionManager::createMenu( Constants::CONTEXT_MENU_ID );
    contextMenu->menu()->setTitle( tr( "CheatSh" ) );
    contextMenu->addSeparator();
    contextMenu->addAction( cheatShCommand );
    contextMenu->addSeparator();
    //editorcontextMenu->addMenu(contextMenu);  //
    Core::Id group_id(Constants::CONTEXT_MENU_ID);
    editorcontextMenu->appendGroup(group_id);
    editorcontextMenu->addSeparator(group_id);
    editorcontextMenu->addAction(cheatShCommand, group_id);
}

} // namespace Internal
} // namespace CheatSh
