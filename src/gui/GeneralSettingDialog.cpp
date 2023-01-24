#include <QApplication>
#include <QSettings>
#include <QGroupBox>
#include <QFormLayout>
#include <QComboBox>
#include <qstandardpaths.h>
#include "gui/GeneralSettingDialog.h"

namespace
{

static const int kLanguageTypeCount = 3;
static const int kTimeFormatTypeCount = 6;
static const int kEasingTypeCount = 12;
static const int kRangeTypeCount = 3;

int languageToIndex(const QString& aLanguage)
{
    if (aLanguage == "Auto") return 0;
    else if (aLanguage == "English") return 1;
    else if (aLanguage == "Japanese") return 2;
    else return 0;
}

int easingToIndex(const QString& aEasing){
    if (aEasing == "None") return 0;
    else if (aEasing == "Linear") return 1;
    else if (aEasing == "Sine") return 2;
    else if (aEasing == "Quad") return 3;
    else if (aEasing == "Cubic") return 4;
    else if (aEasing == "Quart") return 5;
    else if (aEasing == "Quint") return 6;
    else if (aEasing == "Expo") return 7;
    else if (aEasing == "Circ") return 8;
    else if (aEasing == "Back") return 9;
    else if (aEasing == "Elastic") return 10;
    else if (aEasing == "Bounce") return 11;
    else return 1; // Default easing is Linear
}

int rangeToIndex(const QString& aRange){
    if (aRange == "In") return 0;
    else if(aRange == "Out") return 1;
    else if (aRange == "All") return 2;
    else return 2; // Default range is InOut, it is referenced as "All" by Hidefuku
}

QString indexToEasing(int aIndex, bool translated = true){
    if (translated){
        switch(aIndex){
            case 0: return QCoreApplication::translate("GeneralSettingsDialog", "None");
            case 1: return QCoreApplication::translate("GeneralSettingsDialog", "Linear");
            case 2: return QCoreApplication::translate("GeneralSettingsDialog", "Sine");
            case 3: return QCoreApplication::translate("GeneralSettingsDialog", "Quad");
            case 4: return QCoreApplication::translate("GeneralSettingsDialog", "Cubic");
            case 5: return QCoreApplication::translate("GeneralSettingsDialog", "Quart");
            case 6: return QCoreApplication::translate("GeneralSettingsDialog", "Quint");
            case 7: return QCoreApplication::translate("GeneralSettingsDialog", "Expo");
            case 8: return QCoreApplication::translate("GeneralSettingsDialog", "Circ");
            case 9: return QCoreApplication::translate("GeneralSettingsDialog", "Back");
            case 10: return QCoreApplication::translate("GeneralSettingsDialog", "Elastic");
            case 11: return QCoreApplication::translate("GeneralSettingsDialog", "Bounce");
        default: return QCoreApplication::translate("GeneralSettingsDialog", "Linear");
        }
    }
    else{
        switch(aIndex){
            case 0: return QString("None");
            case 1: return QString("Linear");
            case 2: return QString("Sine");
            case 3: return QString("Quad");
            case 4: return QString("Cubic");
            case 5: return QString("Quart");
            case 6: return QString("Quint");
            case 7: return QString("Expo");
            case 8: return QString("Circ");
            case 9: return QString("Back");
            case 10: return QString("Elastic");
            case 11: return QString("Bounce");
        default: return QString("Linear");
    }
  }
}

QString indexToRange(int aRange, bool translated = true){
    if (translated){
        switch(aRange){
            case 0: return QCoreApplication::translate("GeneralSettingsDialog", "In");
            case 1: return QCoreApplication::translate("GeneralSettingsDialog", "Out");
            case 3: return QCoreApplication::translate("GeneralSettingsDialog", "All");
        default: return QCoreApplication::translate("GeneralSettingsDialog", "All");
        }
    }
    else{
        switch(aRange){
            case 0: return QString("In");
            case 1: return QString("Out");
            case 3: return QString("All");
        default: return QString("All");
        }
    }
}

QString indexToLanguage(int aIndex, bool translated = true)
{
    if (translated){
        switch (aIndex){
        case 0: return QCoreApplication::translate("GeneralSettingsDialog", "Auto");
        case 1: return  QCoreApplication::translate("GeneralSettingsDialog", "English");;
        case 2: return  QCoreApplication::translate("GeneralSettingsDialog", "Japanese");;
        default: return  QCoreApplication::translate("GeneralSettingsDialog", "Auto");;
        }
    }
    else{
        switch (aIndex){
        case 0: return QString("Auto");
        case 1: return QString("Enslish");
        case 2: return QString("Japanese");
        default: return QString("Auto");
        }
    }
  }
}

QString indexToTimeFormat(int aIndex)
{
    switch (aIndex)
    {
    case core::TimeFormatType::TimeFormatType_Frames_From0:   return QCoreApplication::translate("GeneralSettingsDialog", "Frame number (from 0)");
    case core::TimeFormatType::TimeFormatType_Frames_From1:   return QCoreApplication::translate("GeneralSettingsDialog", "Frame number (from 1)");
    case core::TimeFormatType::TimeFormatType_Relative_FPS:   return QCoreApplication::translate("GeneralSettingsDialog", "Relative to FPS (1.0 = 60.0)");
    case core::TimeFormatType::TimeFormatType_Seconds_Frames: return QCoreApplication::translate("GeneralSettingsDialog", "Seconds : Frame");
    case core::TimeFormatType::TimeFormatType_Timecode_SMPTE: return QCoreApplication::translate("GeneralSettingsDialog", "Timecode (SMPTE) (HH:MM:SS:FF)");
    case core::TimeFormatType::TimeFormatType_Timecode_HHMMSSmmm: return QCoreApplication::translate("GeneralSettingsDialog", "Timecode (HH:MM:SS:mmm)");
    default: return "";
    }
}


namespace gui
{

GeneralSettingDialog::GeneralSettingDialog(GUIResources &aGUIResources, QWidget* aParent)
    : EasyDialog(tr("General Settings"), aParent)
    , mInitialLanguageIndex()
    , mLanguageBox()
    , mInitialTimeFormatIndex()
    , mTimeFormatBox()
    , mInitialThemeKey("default")
    , mThemeBox()
    , mGUIResources(aGUIResources)
{
    // read current settings
    {
        QSettings settings;
        auto language = settings.value("generalsettings/language");

        if (language.isValid())
        {
            mInitialLanguageIndex = languageToIndex(language.toString());
        }

        auto easing = settings.value("generalsettings/easing");

        if (easing.isValid()){
            mInitialEasingIndex = easingToIndex(easing.toString());
        }
        else{
            mInitialEasingIndex = easingToIndex("Linear");
        }

        auto range = settings.value("generalsettings/range");

        if (range.isValid()){
            mInitialRangeIndex = rangeToIndex(range.toString());
        }
        else{
            mInitialRangeIndex = rangeToIndex("All");
        }

        auto timeScale = settings.value("generalsettings/ui/timeformat");
        if (timeScale.isValid())
        {
            mInitialTimeFormatIndex = timeScale.toInt();
        }

        auto theme = settings.value("generalsettings/ui/theme");
        if (theme.isValid())
        {
            mInitialThemeKey = theme.toString();
        }
    }

    auto form = new QFormLayout();
    form->setFormAlignment(Qt::AlignHCenter | Qt::AlignTop);
    form->setLabelAlignment(Qt::AlignRight);

    // create inner widgets
    {
        mLanguageBox = new QComboBox();
        for (int i = 0; i < kLanguageTypeCount; ++i)
        {
            mLanguageBox->addItem(indexToLanguage(i));
        }
        mLanguageBox->setCurrentIndex(mInitialLanguageIndex);
        form->addRow(tr("Language (needs restarting) :"), mLanguageBox);

        mEasingBox = new QComboBox();
        for (int i = 0; i < kEasingTypeCount; ++i){
            mEasingBox->addItem(indexToEasing(i));
        }
        mEasingBox->setCurrentIndex(mInitialEasingIndex);
        form->addRow(tr("Default keyframe easing:"), mEasingBox);

        mRangeBox = new QComboBox();
        for (int i = 0; i < kRangeTypeCount; ++i){
            mRangeBox->addItem(indexToRange(i));
        }
        mRangeBox->setCurrentIndex(mInitialRangeIndex);
        form->addRow(tr("Default keyframe range:"), mRangeBox);

        mTimeFormatBox = new QComboBox();
        for (int i = 0; i < kTimeFormatTypeCount; ++i)
        {
            mTimeFormatBox->addItem(indexToTimeFormat(i));
        }
        mTimeFormatBox->setCurrentIndex(mInitialTimeFormatIndex);
        form->addRow(tr("Timeline format :"), mTimeFormatBox);


        mThemeBox = new QComboBox();
        QStringList themeList = mGUIResources.themeList();
        for (int i = 0; i < themeList.size(); ++i)
        {
            mThemeBox->addItem(themeList[i], themeList[i]);
        }
        mThemeBox->setCurrentIndex(mThemeBox->findData(mInitialThemeKey));
        form->addRow(tr("Theme :"), mThemeBox);
    }

    auto group = new QGroupBox(tr("Parameters"));
    group->setLayout(form);
    this->setMainWidget(group);

    this->setOkCancel([=](int aResult)->bool
    {
        if (aResult == 0)
        {
            this->saveSettings();
        }
        return true;
    });
}

bool GeneralSettingDialog::languageHasChanged()
{
    return (mInitialLanguageIndex != mLanguageBox->currentIndex());
}

bool GeneralSettingDialog::easingHasChanged(){
    return (mInitialEasingIndex != mEasingBox->currentIndex());
}

bool GeneralSettingDialog::rangeHasChanged(){
    return (mInitialRangeIndex != mRangeBox->currentIndex());
}

bool GeneralSettingDialog::timeFormatHasChanged()
{
    return (mInitialTimeFormatIndex != mTimeFormatBox->currentIndex());
}

bool GeneralSettingDialog::themeHasChanged()
{
    return (mInitialThemeKey != mThemeBox->currentData());
}

QString GeneralSettingDialog::theme()
{
    return mThemeBox->currentData().toString();
}

void GeneralSettingDialog::saveSettings()
{
    QSettings settings;
    if (languageHasChanged())
        settings.setValue("generalsettings/language", indexToLanguage(mLanguageBox->currentIndex(), false));

    if(easingHasChanged()){
        settings.setValue("generalsettings/easing", indexToEasing(mEasingBox->currentIndex(), false));
    }
    if(rangeHasChanged()){
        settings.setValue("generalsettings/range", indexToRange(mRangeBox->currentIndex(), false));
    }
    if(timeFormatHasChanged())
        settings.setValue("generalsettings/ui/timeformat", mTimeFormatBox->currentIndex());

    if(themeHasChanged())
        settings.setValue("generalsettings/ui/theme", mThemeBox->currentData());
}

} // namespace gui
