#ifndef GUI_PLAYBACKWIDGET_H
#define GUI_PLAYBACKWIDGET_H

#include <vector>
#include <functional>
#include <QWidget>
#include <QPushButton>
#include "gui/GUIResources.h"
#include "gui/AudioPlaybackWidget.h"
#include "core/Project.h"

namespace gui {

class PlayBackWidget: public QWidget {
    Q_OBJECT
public:
    enum PushType {
        PushType_Play,
        PushType_Pause,
        PushType_Step,
        PushType_StepBack,
        PushType_Rewind,
        PushType_Loop,
        PushType_NoLoop,
        PushType_Fast
    };
    typedef std::function<void(PushType)> PushDelegate;

    PlayBackWidget(GUIResources& aResources, QWidget* aParent, core::Project& aProject);

    void setPushDelegate(const PushDelegate& aDelegate);
    bool isLoopChecked();
    void checkLoop(bool checkStatus);
    void PlayPause();
    bool isPlaying();
    static int constantWidth() ;
    void pushPauseButton();
    core::Project* aProject;
    QWidget* audioUI = new QWidget(this, Qt::Window);
    std::vector<audioConfig>* aConf = new std::vector<audioConfig>;
    mediaState mediaPlayer;
    AudioPlaybackWidget* audioWidget = new AudioPlaybackWidget;


private:
    QPushButton* createButton(const QString& aName, bool aIsCheckable, int aColumn, const QString& aToolTip);
    GUIResources& mGUIResources;
    std::vector<QPushButton*> mButtons;
    PushDelegate mPushDelegate;
    void onThemeUpdated(theme::Theme&);
};

} // namespace gui

#endif // GUI_PLAYBACKWIDGET_H
