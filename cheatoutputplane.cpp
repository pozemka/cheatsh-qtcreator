#include "cheatoutputplane.h"

#include <QTextBrowser>
#include <QWebEngineView>
#include <QString>

#include <ansi_esc2html.h>

namespace CheatSh {
namespace Internal {

CheatOutputPlane::CheatOutputPlane(const Settings* settings) :
    settings_(settings),
    ansi2html_(std::make_unique<ANSI_SGR2HTML>())
{

}

CheatOutputPlane::~CheatOutputPlane()
{

}

void CheatOutputPlane::displayResult(const QString& result)
{
    auto sts = ansi2html_->simpleParse(result.toStdString());
    browser_->setHtml(QString::fromUtf8(sts.data(), sts.size()));
}

QWidget*CheatOutputPlane::outputWidget(QWidget* parent)
{
//    browser_ = new QWebEngineView(parent);
//    browser_->setUrl(QUrl::fromUserInput("cheat.sh/cpp/int"));
    browser_ = new QTextBrowser(parent);
    browser_->setHtml(tr("TODO: plugin's own help text"));
    /* Короче, есть гостинный гарнитур из нескольких стульев:
     * 1. грузить ответ в QTextBrowser через setHtml(), так загрузка вешает креатор, т.к. сайт выдаёт много мусора в странице
     * 2. то же, но без подсветки. Мусора меньше и, похоже он не мешает. Если и тормозит, то меньше, нужно смотреть на больших страницах
     * 3. грузить ответ в QWebEngineView. Загружается мгновенно. Так слетает цвет фона. Видимо отсутсвует CSS; Можно ставить свой CSS или грузить как-то с сайта?
     * 4. Схитрить и просто вызывать у QWebEngineView setUrl(). Читерство!
     * Предыдущие два варианта добавляют зависимость от QWebEngine, не факт что она есть у QtCreator уже. Так же они выглядят чуть чужеродно в креаторе. Может с помощью усилий это можно решить.
     * 5. Выставлять QNetworkRequest User-Agent: curl/7.60.0, получать текст, подходящий для консоли и самому его переделывать в нормальный HTML. Хех. см. https://www.geeksforgeeks.org/formatted-text-linux-terminal-using-python/ и https://en.wikipedia.org/wiki/ANSI_escape_code и https://stackoverflow.com/q/245121/149897 и https://github.com/theZiz/aha (будет неплохим развлечением написать аналог. Только она тоже спамит span с мусором, можно сделать лучше)
     * Есть ещё что-то такое, но похоже не то что нужно https://github.com/astoeckel/vtparse
     */

    /* Оказывается там для терминала тоже передаётся не очень чистый текст. Перключается цвет на каждый спец символ или слово, но при этом фактически цвет не меняется. Так что претензия к aha только в том, что она для каждой смены цвета делает span style, если просто задавать цвет - будет компактнее.
     * Или объеденять эти спаны в настоящие стили, но это сложно.
     * Но это всё же лучше чем то что передаётся в браузер там тоже цвет передается, но лесенками из спанов
     * Это не считая огромной простыни из опций для выпадающего списка
     * В консольный браузер (lynx) приходит то же.
     * Надо, кстати посмотреть какой файл в QtCreator присылается. Думаю такой же. И тормозит именно из-за него
     *
     * Сравнительный результат: мой парсер (не законченый): 2,6 КБ
     * aha                                                : 3,5 КБ
     * html из интернета                                  : 102,2 КБ
     */

    return browser_;
}

QList<QWidget*> CheatOutputPlane::toolBarWidgets() const
{
    return QList<QWidget*>();
}

QString CheatOutputPlane::displayName() const
{
    return tr("cheat.sh");
}

int CheatOutputPlane::priorityInStatusBar() const
{
    return 0;
}

void CheatOutputPlane::clearContents()
{

}

void CheatOutputPlane::visibilityChanged(bool visible)
{
    browser_->setVisible(visible);
}

void CheatOutputPlane::setFocus()
{
    browser_->setFocus();
}

bool CheatOutputPlane::hasFocus() const
{
    if(browser_)
        return browser_->hasFocus();

    return false;
}

bool CheatOutputPlane::canFocus() const
{
    return true;
}

bool CheatOutputPlane::canNavigate() const
{
    return false;
}

bool CheatOutputPlane::canNext() const
{
    return false;
}

bool CheatOutputPlane::canPrevious() const
{
    return false;
}

void CheatOutputPlane::goToNext()
{

}

void CheatOutputPlane::goToPrev()
{

}

}   // namespace Internal
}   // namespace CheatSh
