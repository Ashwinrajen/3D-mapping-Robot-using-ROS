#include<ros.h>
#include<std_msgs/Empty.h>
ros :: NodeHandle nh ;
void messageCb1 ( const  std_msgs :: Empty& toggle_msg1 ) {
analogWrite(8,50);
analogWrite(9,50);
analogWrite(10,0);
analogWrite(11,0);
delay(2000);
analogWrite(8,50);
analogWrite(9,50);
analogWrite(10,0);
analogWrite(11,0);
delay(2000);
}
void messageCb2 ( const  std_msgs :: Empty& toggle_msg2 ) {
analogWrite(10,50);
analogWrite(11,50);
analogWrite(8,0);
analogWrite(9,0);
delay(2000);
analogWrite(10,50);
analogWrite(11,50);
analogWrite(8,0);
analogWrite(9,0);
delay(2000);
}
void messageCb3 ( const  std_msgs :: Empty& toggle_msg3 ) {
analogWrite(8,50);
analogWrite(9,0);
analogWrite(10,0);
analogWrite(11,0);
delay(2000);
analogWrite(8,50);
analogWrite(9,0);
analogWrite(10,0);
analogWrite(11,0);
delay(2000);
}

void messageCb4 ( const  std_msgs :: Empty& toggle_msg4 ) {
analogWrite(8,0);
analogWrite(9,50);
analogWrite(10,0);
analogWrite(11,0);
delay(2000);
analogWrite(8,0);
analogWrite(9,50);
analogWrite(10,0);
analogWrite(11,0);
delay(2000);
}

ros :: Subscriber<std_msgs::Empty>  forward("forward", &messageCb1 );
ros :: Subscriber<std_msgs::Empty>  backward("backward", &messageCb2 );
ros :: Subscriber<std_msgs::Empty>  right("right", &messageCb3 );
ros :: Subscriber<std_msgs::Empty>  left("left", &messageCb4 );
void setup()
{
pinMode(8,OUTPUT);
pinMode(10,OUTPUT);
pinMode(9,OUTPUT);
pinMode(11,OUTPUT);
nh.initNode();
nh.subscribe(forward);
nh.subscribe(backward);
nh.subscribe(right);
nh.subscribe(left);
}
void loop()
{
nh.spinOnce();
delay(1);
}
