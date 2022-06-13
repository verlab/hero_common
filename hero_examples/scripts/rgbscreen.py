#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'rgbscreen.ui'
#
# Created by: PyQt5 UI code generator 5.14.1
#
# WARNING! All changes made in this file will be lost!

import rospy


from PyQt5 import QtCore, QtGui, QtWidgets
from std_msgs.msg import ColorRGBA
import numpy as np
import sys




class Ui_Form(object):
    def setupUi(self, Form):
        Form.setObjectName("Form")
        Form.resize(452, 322)
        self.splitter = QtWidgets.QSplitter(Form)
        self.splitter.setGeometry(QtCore.QRect(30, 40, 361, 241))
        self.splitter.setOrientation(QtCore.Qt.Vertical)
        self.splitter.setObjectName("splitter")
        self.layoutWidget = QtWidgets.QWidget(self.splitter)
        self.layoutWidget.setObjectName("layoutWidget")
        self.horizontalLayout = QtWidgets.QHBoxLayout(self.layoutWidget)
        self.horizontalLayout.setContentsMargins(0, 0, 0, 0)
        self.horizontalLayout.setObjectName("horizontalLayout")
        self.verticalLayout = QtWidgets.QVBoxLayout()
        self.verticalLayout.setObjectName("verticalLayout")
        self.label = QtWidgets.QLabel(self.layoutWidget)
        self.label.setObjectName("label")
        self.verticalLayout.addWidget(self.label)
        self.spinBoxRed = QtWidgets.QSpinBox(self.layoutWidget)
        self.spinBoxRed.setMinimum(1)
        self.spinBoxRed.setMaximum(255)
        self.spinBoxRed.setObjectName("spinBoxRed")
        self.verticalLayout.addWidget(self.spinBoxRed)
        self.verticalSliderRed = QtWidgets.QSlider(self.layoutWidget)
        self.verticalSliderRed.setCursor(QtGui.QCursor(QtCore.Qt.PointingHandCursor))
        self.verticalSliderRed.setMinimum(1)
        self.verticalSliderRed.setMaximum(255)
        self.verticalSliderRed.setProperty("value", 1)
        self.verticalSliderRed.setSliderPosition(1)
        self.verticalSliderRed.setOrientation(QtCore.Qt.Vertical)
        self.verticalSliderRed.setObjectName("verticalSliderRed")
        self.verticalLayout.addWidget(self.verticalSliderRed)
        self.horizontalLayout.addLayout(self.verticalLayout)
        self.verticalLayout_2 = QtWidgets.QVBoxLayout()
        self.verticalLayout_2.setObjectName("verticalLayout_2")
        self.label_2 = QtWidgets.QLabel(self.layoutWidget)
        self.label_2.setObjectName("label_2")
        self.verticalLayout_2.addWidget(self.label_2)
        self.spinBoxGreen = QtWidgets.QSpinBox(self.layoutWidget)
        self.spinBoxGreen.setMinimum(1)
        self.spinBoxGreen.setMaximum(255)
        self.spinBoxGreen.setObjectName("spinBoxGreen")
        self.verticalLayout_2.addWidget(self.spinBoxGreen)
        self.verticalSliderGreen = QtWidgets.QSlider(self.layoutWidget)
        self.verticalSliderGreen.setCursor(QtGui.QCursor(QtCore.Qt.PointingHandCursor))
        self.verticalSliderGreen.setMinimum(1)
        self.verticalSliderGreen.setMaximum(255)
        self.verticalSliderGreen.setProperty("value", 1)
        self.verticalSliderGreen.setSliderPosition(1)
        self.verticalSliderGreen.setOrientation(QtCore.Qt.Vertical)
        self.verticalSliderGreen.setObjectName("verticalSliderGreen")
        self.verticalLayout_2.addWidget(self.verticalSliderGreen)
        self.horizontalLayout.addLayout(self.verticalLayout_2)
        self.verticalLayout_3 = QtWidgets.QVBoxLayout()
        self.verticalLayout_3.setObjectName("verticalLayout_3")
        self.label_3 = QtWidgets.QLabel(self.layoutWidget)
        self.label_3.setObjectName("label_3")
        self.verticalLayout_3.addWidget(self.label_3)
        self.spinBoxBlue = QtWidgets.QSpinBox(self.layoutWidget)
        self.spinBoxBlue.setMinimum(1)
        self.spinBoxBlue.setMaximum(255)
        self.spinBoxBlue.setObjectName("spinBoxBlue")
        self.verticalLayout_3.addWidget(self.spinBoxBlue)
        self.verticalSliderBlue = QtWidgets.QSlider(self.layoutWidget)
        self.verticalSliderBlue.setCursor(QtGui.QCursor(QtCore.Qt.PointingHandCursor))
        self.verticalSliderBlue.setMinimum(1)
        self.verticalSliderBlue.setMaximum(255)
        self.verticalSliderBlue.setProperty("value", 1)
        self.verticalSliderBlue.setSliderPosition(1)
        self.verticalSliderBlue.setOrientation(QtCore.Qt.Vertical)
        self.verticalSliderBlue.setObjectName("verticalSliderBlue")
        self.verticalLayout_3.addWidget(self.verticalSliderBlue)
        self.horizontalLayout.addLayout(self.verticalLayout_3)
        self.verticalLayout_4 = QtWidgets.QVBoxLayout()
        self.verticalLayout_4.setObjectName("verticalLayout_4")
        self.label_4 = QtWidgets.QLabel(self.layoutWidget)
        self.label_4.setObjectName("label_4")
        self.verticalLayout_4.addWidget(self.label_4)
        self.spinBoxAlpha = QtWidgets.QSpinBox(self.layoutWidget)
        self.spinBoxAlpha.setCursor(QtGui.QCursor(QtCore.Qt.ArrowCursor))
        self.spinBoxAlpha.setMinimum(0)
        self.spinBoxAlpha.setMaximum(10)
        self.spinBoxAlpha.setValue(10)
        self.spinBoxAlpha.setObjectName("spinBoxAlpha")
        self.verticalLayout_4.addWidget(self.spinBoxAlpha)
        self.verticalSliderAlpha = QtWidgets.QSlider(self.layoutWidget)
        self.verticalSliderAlpha.setCursor(QtGui.QCursor(QtCore.Qt.PointingHandCursor))
        self.verticalSliderAlpha.setMinimum(0)
        self.verticalSliderAlpha.setMaximum(10)
        self.verticalSliderAlpha.setProperty("value", 10)
        self.verticalSliderAlpha.setSliderPosition(10)
        self.verticalSliderAlpha.setOrientation(QtCore.Qt.Vertical)
        self.verticalSliderAlpha.setObjectName("verticalSliderAlpha")
        self.verticalLayout_4.addWidget(self.verticalSliderAlpha)
        self.horizontalLayout.addLayout(self.verticalLayout_4)
        self.pushButton = QtWidgets.QPushButton(self.splitter)
        self.pushButton.setCursor(QtGui.QCursor(QtCore.Qt.PointingHandCursor))
        self.pushButton.setMouseTracking(True)
        self.pushButton.setCheckable(False)
        self.pushButton.setChecked(False)
        self.pushButton.setAutoRepeat(False)
        self.pushButton.setAutoDefault(False)
        self.pushButton.setDefault(False)
        self.pushButton.setFlat(False)
        self.pushButton.setObjectName("pushButton")

        self.retranslateUi(Form)
        self.verticalSliderRed.valueChanged['int'].connect(self.spinBoxRed.setValue)
        self.spinBoxRed.valueChanged['int'].connect(self.verticalSliderRed.setValue)
        self.spinBoxGreen.valueChanged['int'].connect(self.verticalSliderGreen.setValue)
        self.verticalSliderGreen.valueChanged['int'].connect(self.spinBoxGreen.setValue)
        self.verticalSliderBlue.valueChanged['int'].connect(self.spinBoxBlue.setValue)
        self.spinBoxBlue.valueChanged['int'].connect(self.verticalSliderBlue.setValue)
        self.verticalSliderAlpha.valueChanged['int'].connect(self.spinBoxAlpha.setValue)
        self.spinBoxAlpha.valueChanged['int'].connect(self.verticalSliderAlpha.setValue)
        self.pushButton.clicked.connect(ui.run)
        QtCore.QMetaObject.connectSlotsByName(Form)


    def retranslateUi(self, Form):
        _translate = QtCore.QCoreApplication.translate
        Form.setWindowTitle(_translate("Form", "Form"))
        self.label.setText(_translate("Form", "RED"))
        self.label_2.setText(_translate("Form", "GREEN"))
        self.label_3.setText(_translate("Form", "BLUE"))
        self.label_4.setText(_translate("Form", "ALPHA"))
        self.pushButton.setText(_translate("Form", "Change Color!"))


    def run(self):
        # print("hello")
        rate = rospy.Rate(5)
        rospy.loginfo("[RGBScreen]: Trying to change color!")
        color = ColorRGBA()
        color.r = float(abs(int(self.spinBoxRed.text()) - 256))
        color.g  = float(abs(int(self.spinBoxGreen.text()) - 256))
        color.b = float(abs(int(self.spinBoxBlue.text()) - 256))
        color.a = float(self.spinBoxAlpha.text())/10
        print(color)
        print()
        rate.sleep()
        self.pub.publish(color)
        
        
        
    def __init__(self):
        rospy.init_node('rgbscreen', anonymous=False)
        self.pub = rospy.Publisher('/hero_4/led', ColorRGBA, queue_size=10)



if __name__ == "__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    Form = QtWidgets.QWidget()
    ui = Ui_Form()
    ui.setupUi(Form)
    Form.show()
    sys.exit(app.exec_())
