# Test the coder

### Task:
Write a ROS node that calculates the moving maximum (running maximum) over 1000 samples in (soft) realtime of an incoming stream of Uint64s.
Publish your result after processing the incoming number and in addition forward the incoming number to the verifying node.

### Requirements
* a working ROS distribution
* Indigo or Jade
* Python 2.7

#### Steps:

1. Create either a C++ or Python ROS node
  * You can find guidance at the [ROS wiki](http://wiki.ros.org/ROS/Tutorials)
2. Subscribe to the publisher node
  * topic: /numbers
  * type: Int64
3. Advertise your solution topic
  * topic: /verify
  * type: programming_test/Solution
4. Do your magic...
5. Publish your solution after you have incorporated the latest incoming data point. 
Include (forward) the incoming data point on the *input* slot of the message.
6. Add your node to the launch file.




The data structure queue has been used to calculate the moving maximum over 1000 samples in realtime of an incoming stream. 

The window size is 1000. 
The incoming data is en-queued into the queue till queue reaches 1000.
     In the mean time maximum is calculated in the real time from the elements in the growing queue.
     The incoming data and result are published on input and solution slot of the message respectively.        
Once after the size of the queue reaches 1000, The maximum out of 1000 numbers is calculated.
De-queued the oldest number to give a room to the newest number.
The incoming number is published on the input slot  and result on the solution slot of the message.
Process repeated.
