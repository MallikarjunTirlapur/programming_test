#include "ros/ros.h"
#include "std_msgs/Int64.h"
#include <queue>
#include <programming_test/Solution.h>

using namespace std_msgs;
using namespace std;

struct Max {
	int pos;
	Int64 value;
};

/* function prototype */
void getMax(queue<Int64> lQueue, Max &currentMax);

/*Publisher object for publishing messages of type programming_test::Solution*/
ros::Publisher pub;

void callback(const Int64& num) {

	programming_test::Solution lmsg;
	/*Queue container to store incoming numebers*/
	static queue<Int64> myQueue;
	/*initialize pos to -1*/
	static Max currentMax = {-1};

	/*enqueue the data into the queue*/
	myQueue.push(num);

	if (currentMax.pos < 0) { /* First time */
		currentMax.value = num;
		currentMax.pos = 0;
	} else {
		currentMax.pos = currentMax.pos + 1;
	}

	cout << "Size of the queue: "<<myQueue.size() << endl;

	cout<<" pos in callback "<<currentMax.pos<<endl;
	if (myQueue.size() == 1000) {

		if (currentMax.pos == 1000) {
			getMax(myQueue, currentMax);
		} else if (currentMax.value.data < num.data) {
			currentMax.value = num;
			currentMax.pos = 0;
		}
		/*dequeue the data from the queue to maintain the queue size 1000*/
		myQueue.pop();
	 }else if (currentMax.value.data < num.data) {
		currentMax.value = num;
		currentMax.pos = 0;
	}

	/*putting the result on the solution slot of the message*/
	lmsg.solution =  currentMax.value.data;
	/*including the incoming data on the input slot of the message*/
	lmsg.input =  num.data;
	cout << "max number: " << lmsg.solution << endl;
	cout << "in number: " << lmsg.input<< endl;

	/*publish message on the ros network*/
	pub.publish(lmsg);
}

/*********************************************************************
 * Function:        getMax
 *
 * PreCondition:    None
 * Input:           Objects of Queue (call by value) and Max(call by reference).
 * Output:          Updated Max object (new position & max value).
 *
 *
 * Overview:        Calculates the biggest number in the queue.
 *
 *
 * Note:            -
 ********************************************************************/

void getMax(queue<Int64> lQueue, Max &currentMax) {
	int m_len = lQueue.size();
	Int64 m_maximum;
	Int64 dummy;
	/*consider first element as the maximum*/
	currentMax.value.data = lQueue.front().data;
	currentMax.pos = 0;
	lQueue.pop(); //dequeue data from the queue

	/*iterate the process for (queue.size - 1) times to compute the biggest number*/
	for (int i = 1; i < m_len; i++) {
		if (currentMax.value.data < lQueue.front().data) {
			currentMax.value = lQueue.front();
			currentMax.pos = m_len-(i+1);
		}
		lQueue.pop();
	}
}

int main(int argc, char **argv) {

	ros::init(argc, argv, "moving_maximum");
	ros::NodeHandle nh;
	ros::Subscriber sub = nh.subscribe("/numbers", 1, callback);
	pub = nh.advertise<programming_test::Solution>("/verify", 1);
	ros::spin();

	return 0;
}

