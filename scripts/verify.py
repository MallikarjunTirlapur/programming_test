#!/usr/bin/env python
# This Python file uses the following encoding: utf-8

# Copyright (C) 2015 General Interfaces GmbH
# Maintainer: Raphael Dürscheid <mailto:rd@gi.ai>

# This file is part of *Test the coder*.

# *Test the coder* is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.

# *Test the coder* is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with *Test the coder*.  If not, see <http://www.gnu.org/licenses/>.

import rospy
from std_msgs.msg import String
from programming_test.msg import Solution
import numpy as np

class running_maximum:
    """calculate the running maximum for a given window"""
    def __init__(self, windowsize):
        self.array = np.zeros(windowsize)

    def put(self, number_in):
        np.put(self.array, [0], [number_in])
        self.array = np.roll(self.array,1)
        return True

    def get(self):
        return np.amax(self.array)


def callback(data):
    verify(data)

def verify(data):
    verify.r_max.put(data.input)

    maximum = verify.r_max.get()
    if data.solution == maximum:
        rospy.loginfo(rospy.get_caller_id() + "Maximum is correct: %d", data.solution)
        return True
    else:
        rospy.logerr(rospy.get_caller_id() + "Wrong maximum, should be: %d", maximum)
        return False
verify.r_max = running_maximum(1000)

def listener():

    rospy.init_node('verify')

    rospy.Subscriber("/verify", Solution, callback)

    rospy.spin()

if __name__ == '__main__':
    
    listener()
