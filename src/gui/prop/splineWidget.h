/********************************************************************************
** Form generated from reading UI file 'designerOAYGQF.ui'
**
** Created by: Qt User Interface Compiler version 6.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef DESIGNEROAYGQF_H
#define DESIGNEROAYGQF_H

#include "GUIResources.h"


#include <qgraphicsview.h>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>
#include "gui/prop/bezierCurveEditor.h"


QT_BEGIN_NAMESPACE



class Ui_splineWidget
{
public:
    QGridLayout *gridLayout_2;
    QDoubleSpinBox *x1_spin;
    QDoubleSpinBox *x2_spin;
    QDoubleSpinBox *y1_spin;
    QFrame *line;
    BezierCurveEditor* m_editor;
    QToolButton *toolButton_2;
    QToolButton *toolButton;
    QDoubleSpinBox *y2_spin;
    QPushButton *cancel;
    QPushButton *apply;

    void setupUi(QWidget *splineWidget, const gui::GUIResources* guiRes)
    {
        if (splineWidget->objectName().isEmpty())
            splineWidget->setObjectName("splineWidget");
        splineWidget->resize(600, 400);
        gridLayout_2 = new QGridLayout(splineWidget);
        gridLayout_2->setObjectName("gridLayout_2");
        x1_spin = new QDoubleSpinBox(splineWidget);
        x1_spin->setObjectName("x1_spin");

        gridLayout_2->addWidget(x1_spin, 3, 1, 1, 1);

        x2_spin = new QDoubleSpinBox(splineWidget);
        x2_spin->setObjectName("x2_spin");

        gridLayout_2->addWidget(x2_spin, 3, 3, 1, 1);

        y1_spin = new QDoubleSpinBox(splineWidget);
        y1_spin->setObjectName("y1_spin");

        gridLayout_2->addWidget(y1_spin, 3, 2, 1, 1);

        line = new QFrame(splineWidget);
        line->setObjectName("line");
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout_2->addWidget(line, 1, 0, 1, 6);

        m_editor = new BezierCurveEditor();
        m_editor->setObjectName("splineChart");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::MinimumExpanding);
        m_editor->setSizePolicy(sizePolicy);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);

        gridLayout_2->addWidget(m_editor, 0, 0, 1, 6);

        toolButton_2 = new QToolButton(splineWidget);
        toolButton_2->setObjectName("toolButton_2");

        gridLayout_2->addWidget(toolButton_2, 3, 5, 1, 1);

        toolButton = new QToolButton(splineWidget);
        toolButton->setObjectName("toolButton");

        gridLayout_2->addWidget(toolButton, 3, 0, 1, 1);

        y2_spin = new QDoubleSpinBox(splineWidget);
        y2_spin->setObjectName("y2_spin");

        gridLayout_2->addWidget(y2_spin, 3, 4, 1, 1);

        cancel = new QPushButton(splineWidget);
        cancel->setObjectName("cancel");

        gridLayout_2->addWidget(cancel, 6, 0, 1, 3);

        apply = new QPushButton(splineWidget);
        apply->setObjectName("apply");

        gridLayout_2->addWidget(apply, 6, 3, 1, 3);


        retranslateUi(splineWidget);

        QMetaObject::connectSlotsByName(splineWidget);
    } // setupUi

    void retranslateUi(QWidget *splineWidget)
    {
        splineWidget->setWindowTitle(QCoreApplication::translate("splineWidget", "Form", nullptr));
        toolButton_2->setText(QCoreApplication::translate("splineWidget", "Paste", nullptr));
        toolButton->setText(QCoreApplication::translate("splineWidget", "Copy", nullptr));
        cancel->setText(QCoreApplication::translate("splineWidget", "Cancel", nullptr));
        apply->setText(QCoreApplication::translate("splineWidget", "Apply", nullptr));
    } // retranslateUi

};

namespace Ui {
    class splineWidget: public Ui_splineWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // DESIGNEROAYGQF_H
