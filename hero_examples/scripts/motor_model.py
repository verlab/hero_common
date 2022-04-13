#!/usr/bin/env python
# Potential field to navigate the robot

import rospy
import numpy as np
import time
from hero_common.msg import Motor, Encoder
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

class Model(object):
    def __init__(self):
        rospy.init_node("model_motor", anonymous=False)
        rospy.Subscriber("hero_1/encoder", Encoder, self.encoder_cb)
        self.pub = rospy.Publisher('/hero_1/cmd_motor', Motor, queue_size=1)
        self.model = [] # (PWM, MEAN_VEL, STD_VEL)
        self.vel = []
        self.msg = Motor()
        self.MIN_PWM = 900
        self.MAX_PWM = 2000
        self.pwm = self.MIN_PWM
        self.fig, self.ax = plt.subplots(1, 1)
        self.fig.canvas.mpl_connect('close_event', self.handle_close)
        self.xdata, self.moto1_avg, self.moto1_std, self.moto2_avg, self.moto2_std = [], [], [], [], []
        self.ln1, = self.ax.plot([], [], 'r-')
        self.ln2, = self.ax.plot([], [], 'b-')
        
        ani = FuncAnimation(self.fig, self.update, frames=None, init_func=self.init, blit=False)
        # plt.draw()
        # plt.show(block=False)
        # plt.show()
        # plt.ion()
        rospy.loginfo("Starting building the model:")
        plt.show()

    def init(self):
        self.ax.set_ylim(self.MIN_PWM, self.MAX_PWM)
        self.ax.set_xlim(-0.4, 0.4)
        return self.ln1,self.ln2

    def halt(self):
            self.msg.left_motor_pwm = 1359
            self.msg.right_motor_pwm = 1296
            self.pub.publish(self.msg)

    def update(self, x):
        # rospy.loginfo("PWM: {} VELS:{}".format(self.pwm, len(self.vel)))
        if self.pwm > self.MAX_PWM:
            self.msg.left_motor_pwm = 1330
            self.msg.right_motor_pwm = 1310
            self.pub.publish(self.msg)
            return self.ln1,self.ln2 
        if len(self.vel) > 80:
            self.vel = self.vel[30:80]
            data = np.array(self.vel)
            self.vel = []
            self.model.append([self.pwm, data[:,0].mean(), data[:,0].std(), data[:,1].mean(), data[:,1].std()])
            # print(self.model)
            rospy.loginfo("\33[94mPWM: {} MotorL: ({},{}) MotorR: ({},{})\33[0m".format(self.pwm, data[:,0].mean(), data[:,0].std(), data[:,1].mean(), data[:,1].std()))
            self.pwm += 5
            # self.halt()
            # time.sleep(3)
        self.msg.left_motor_pwm = self.pwm
        self.msg.right_motor_pwm = self.pwm
        self.pub.publish(self.msg)
        if (len(self.model) > 0):
            data = np.array(self.model)
            self.xdata = data[:,0]
            self.moto1_avg = data[:,1] 
            self.moto1_std = data[:,2]
            self.moto2_avg = data[:,3] 
            self.moto2_std = data[:,4]
            self.ln1.set_data(self.moto1_avg, self.xdata)
            self.ln2.set_data(self.moto2_avg, self.xdata)
        return self.ln1,self.ln2

    def handle_close(self, evt):
        self.msg.left_motor_pwm = 1330
        self.msg.right_motor_pwm = 1310
        self.pub.publish(self.msg)
        self.model = np.array(self.model)
        timestr = time.strftime("%Y%m%d-%H%M%S")
        np.save("log_"+timestr+".npy", self.model)

    def encoder_cb(self, msg):
        # self.vel.append([msg.left_speed, msg.right_speed])
        self.vel.append([msg.left_speed_filtered, msg.right_speed_filtered])
        # rospy.loginfo("Getting encoder messages... {}".format(len(self.vel)))

    # def capture(self):
    #     rate = rospy.Rate(1)
    #     rospy.loginfo("Starting building the model:")
    #     while not rospy.is_shutdown() and (self.pwm <= 2200):
    #         rospy.loginfo("Running")
    #         if len(self.vel) > 40:
    #             self.vel = self.vel[:]
    #             data = np.array(self.vel)
    #             self.vel = []
    #             self.model.append([self.pwm, data[:,0].mean(), data[:,0].std(), data[:,1].mean(), data[:,1].std()])
    #             print(self.model)
    #             rospy.loginfo("PWM: {}".format(self.pwm))
    #             self.pwm += 10
    #         self.msg.left_motor_pwm = self.pwm
    #         self.msg.right_motor_pwm = self.pwm
    #         self.pub.publish(self.msg)
    #         rate.sleep()

    #     self.msg.left_motor_pwm = 1330
    #     self.msg.right_motor_pwm = 1310
    #     self.pub.publish(self.msg)
    #     print(self.model)
        

# Main function
if __name__ == '__main__':
    try:
        model = Model()
        # model.capture()
    except rospy.ROSInterruptException:
        rospy.loginfo("[Capturing motor model]: Closed!")
