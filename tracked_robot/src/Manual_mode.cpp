#include "ros/ros.h"
#include <cstdio>
#include <cstdlib>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <errno.h>
#include <string.h>
#include <iostream> //lib use in c++
#include "conio.h"
#include "std_msgs/MultiArrayLayout.h"
#include "std_msgs/MultiArrayDimension.h"
#include "std_msgs/Int32MultiArray.h"
#include "std_msgs/Int32.h"
#include "std_msgs/Float64.h"
#include <dynamixel_workbench_msgs/JointCommand.h>


#define PI 3.14

int vv1=1000,vv2=1000,y=0;
int wd1=0,wd2=0,wd3=0;
int act;
float top=-5,bottom=30;
float topp=-5,bottomm=30;
int cnt=0;
int main(int argc, char **argv)
{
   printf("Manual control \n");
	ros::init(argc, argv, "Manual_mode");
  	ros::NodeHandle n;
	ros::Publisher pub1 = n.advertise<std_msgs::Int32MultiArray>("robot_speed", 100);
	ros::Publisher pub2 = n.advertise<std_msgs::Int32MultiArray>("leg_speed", 100);
	ros::Publisher pub3 = n.advertise<std_msgs::Int32MultiArray>("robot_MA", 100);
	ros::Publisher pub4 = n.advertise<std_msgs::Int32MultiArray>("leg_MA", 100);
	ros::Publisher pub5 = n.advertise<std_msgs::Int32MultiArray>("robot_HO", 100);
	ros::Publisher pub6 = n.advertise<std_msgs::Int32MultiArray>("robot_VA", 100);

	ros::Publisher pub7 = n.advertise<std_msgs::Int32>("robot_motion", 100);
	ros::Publisher pub8 = n.advertise<std_msgs::Int32>("leg_motion", 100);

	ros::Publisher pub9 = n.advertise<std_msgs::Int32MultiArray>("leg_HO", 100);
	ros::Publisher pub10 = n.advertise<std_msgs::Int32MultiArray>("leg_VA", 100);
	ros::Publisher pub11 = n.advertise<std_msgs::Int32MultiArray>("robot_MR", 100);

	ros::Publisher pub12 = n.advertise<std_msgs::Float64>("head_top", 100);
	ros::Publisher pub13 = n.advertise<std_msgs::Float64>("head_bottom", 100);

	ros::ServiceClient joint_command_client =
                n.serviceClient<dynamixel_workbench_msgs::JointCommand>("joint_command");
		
//---robot_motion---
//1=fwd
//2=back
//3=left
//4=right
//0=stop
//-------------------	 	 
//---lef_motion---
//1=front up
//2=front down 
//3=back up
//4=back down
//0=stop
//-------------------
	ros::Rate loop_rate(100);

	

	while(ros::ok())
	{
		std_msgs::Int32MultiArray robot_speed,leg_speed,robot_MA,leg_MA,robot_HO,robot_VA,robot_MR,leg_HO,leg_VA;
		std_msgs::Int32 robot_motion,leg_motion;
		std_msgs::Float64 head_top,head_bottom;
		dynamixel_workbench_msgs::JointCommand joint_command;

		robot_speed.data.clear();
		leg_speed.data.clear();
		robot_MA.data.clear();
		leg_MA.data.clear();
		robot_HO.data.clear();
		robot_VA.data.clear();
		robot_MR.data.clear();

				
		
      y=getch();

      if(y==32)
		{
			int rm=0;//robot_motion

			robot_motion.data=rm;

			pub7.publish(robot_motion);
			printf("robot_motion publish\n");
			ros::spinOnce();
			

	      //bodyact("stop");
	      //XtionMotor_stop();
	      //legact("stop","stop");
	      //usleep(50000);
			act = 0;
		}
      else if(y==65)
		{
			int rm=1;//robot_motion

			robot_motion.data=rm;

			pub7.publish(robot_motion);
			printf("robot_motion publish\n");
			ros::spinOnce();
      	//bodyact("fwd");
      	//usleep(50000);
			act = 1;
      }
      else if(y==66)
		{
			int rm=2;//robot_motion

			robot_motion.data=rm;

			pub7.publish(robot_motion);
			printf("robot_motion publish\n");
			ros::spinOnce();

         //bodyact("back");
         //usleep(50000);
			act = 2;
      }
      else if(y==68)
		{
			int rm=3;//robot_motion

			robot_motion.data=rm;

			pub7.publish(robot_motion);
			printf("robot_motion publish\n");
			ros::spinOnce();

			//bodyact("left");
			//usleep(50000);
			act = 3;
      }
      else if(y==67)
		{
			int rm=4;//robot_motion

			robot_motion.data=rm;

			pub7.publish(robot_motion);
			printf("robot_motion publish\n");
			ros::spinOnce();

         //bodyact("right");
			//usleep(50000);
			act = 4;
      }
      else if(y==97||y==65)//A
		{  
      	int lm=1;//leg_motion:front up

			leg_motion.data=lm;

			pub8.publish(leg_motion);
			printf("robot_motion publish\n");
			ros::spinOnce();

         //usleep(50000);
			//legact("","rev");
		}
      else if(y==122||y==90)//Z
      {  
			int lm=2;//leg_motion:front down

			leg_motion.data=lm;

			pub8.publish(leg_motion);
			printf("robot_motion publish\n");
			ros::spinOnce();
			//legma(0,-5000);
      	//legact("","fwd");
		}
      else if(y==83||y==115)//S
      {
			int lm=3;//leg_motion:back up

			leg_motion.data=lm;

			pub8.publish(leg_motion);
			printf("robot_motion publish\n");
			ros::spinOnce();
			
      	//legma(5000,0);
         //legact("rev","");
		}
      else if(y==120||y==88)//X
      {
			int lm=4;//leg_motion:back down

			leg_motion.data=lm;

			pub8.publish(leg_motion);
			printf("robot_motion publish\n");
			ros::spinOnce();
			
			//legma(-5000,0);
         //legact("fwd","");
       
		}
//-------------------------------------------------------
        else if(y==114||y==82)//R reset speed
        {
				int rs[2];//robot_speed
				int ls[2];//leg_speed
				rs[0]=350;
				rs[1]=350;
				ls[0]=100;
				ls[1]=100;
				for (int i = 0; i < 2; i++)
				{
					robot_speed.data.push_back(rs[i]);
					leg_speed.data.push_back(ls[i]);
				}
				pub1.publish(robot_speed);
				pub2.publish(leg_speed);
				
				printf("robot_speed publish\n");
				
				ros::spinOnce();
            //bodyJOGvel(300,300);
            //legJOGvel(100,100);
            vv1=350;
            vv2=350;
        }
        /*else if(y==112)
        {
            XtionMotor_MR(1000,1000);
        }
        else if(y==111)
        {
            XtionMotor_MR(-1000,-1000);
        }*/
        else if(y==102||y==70)//F fast speed
        {
            int rs[2];//robot_speed
				int ls[2];//leg_speed
				rs[0]=1000;
				rs[1]=1000;
				ls[0]=100;
				ls[1]=100;
				for (int i = 0; i < 2; i++)
				{
					robot_speed.data.push_back(rs[i]);
					leg_speed.data.push_back(ls[i]);
				}
				pub1.publish(robot_speed);
				pub2.publish(leg_speed);
				
				printf("robot_speed publish\n");
				
				ros::spinOnce();
			 	//bodyJOGvel(1000,1000);
            //legJOGvel(200,200);
            vv1=1000;
            vv2=1000;
        }
        else if(y==85||y==117)//U add speed
        {
            if(vv1<30000)
                vv1+=500;
            if(vv2<30000)
                vv2+=500;
            
				int rs[2];//robot_speed
				
				rs[0]=vv1;
				rs[1]=vv2;

				for (int i = 0; i < 2; i++)
				{
					robot_speed.data.push_back(rs[i]);
				}
				pub1.publish(robot_speed);
				printf("robot_speed publish\n");
				
				ros::spinOnce();
				//bodyJOGvel(vv1,vv2);

				

				if (act == 1)
				{
					int rm=1;//robot_motion
					robot_motion.data=rm;
					pub7.publish(robot_motion);
					printf("robot_motion publish\n");
					ros::spinOnce();
				}		
				else if (act == 2)
				{
					int rm=2;//robot_motion
					robot_motion.data=rm;
					pub7.publish(robot_motion);
					printf("robot_motion publish\n");
					ros::spinOnce();
				}
				else if (act == 3)
				{
					int rm=3;//robot_motion
					robot_motion.data=rm;
					pub7.publish(robot_motion);
					printf("robot_motion publish\n");
					ros::spinOnce();
				}
				else if (act == 4)
				{
					int rm=4;//robot_motion
					robot_motion.data=rm;
					pub7.publish(robot_motion);
					printf("robot_motion publish\n");
					ros::spinOnce();
				}
				else if (act == 0)
				{						
					int rm=0;//robot_motion
					robot_motion.data=rm;
					pub7.publish(robot_motion);
					printf("robot_motion publish\n");
					ros::spinOnce();
				}

        }
		else if (y == 121)//y slow down
		{
			if (vv1>1000)
				vv1 -= 500;
			if (vv2>1000)
				vv2 -= 500;
//------------------------------------------			
			//bodyJOGvel(vv1, vv2);
			int rs[2];//robot_speed
				
			rs[0]=vv1;
			rs[1]=vv2;
			for (int i = 0; i < 2; i++)
			{
				robot_speed.data.push_back(rs[i]);
			}
			pub1.publish(robot_speed);
			printf("robot_speed publish\n");
			
			ros::spinOnce();
//------------------------------------------		
				
				if (act == 1)
				{
					int rm=1;//robot_motion
					robot_motion.data=rm;
					pub7.publish(robot_motion);
					printf("robot_motion publish\n");
					ros::spinOnce();
				}		
				else if (act == 2)
				{
					int rm=2;//robot_motion
					robot_motion.data=rm;
					pub7.publish(robot_motion);
					printf("robot_motion publish\n");
					ros::spinOnce();
				}
				else if (act == 3)
				{
					int rm=3;//robot_motion
					robot_motion.data=rm;
					pub7.publish(robot_motion);
					printf("robot_motion publish\n");
					ros::spinOnce();
				}
				else if (act == 4)
				{
					int rm=4;//robot_motion
					robot_motion.data=rm;
					pub7.publish(robot_motion);
					printf("robot_motion publish\n");
					ros::spinOnce();
				}
				else if (act == 0)
				{						
					int rm=0;//robot_motion
					robot_motion.data=rm;
					pub7.publish(robot_motion);
					printf("robot_motion publish\n");
					ros::spinOnce();
				}

			/*if (act == 1)
				bodyact("fwd");
			else if (act == 2)
				bodyact("back");
			else if (act == 3)
				bodyact("left");
			else if (act == 4)
				bodyact("right");
			else if (act == 0)
				bodyact("stop");
			*/

		}

      else if(y==101||y==69)//E end for break
      {
          //bodyact("stop");
          //legact("stop","stop");
          break;
      }
		else if(y==106)// J
		{
			int l_MA[2];//leg_MA
				
			l_MA[0]=-26000;
			l_MA[1]=-27000;
			for (int i = 0; i < 2; i++)
			{
				leg_MA.data.push_back(l_MA[i]);
			}
			pub4.publish(leg_MA);
			printf("leg_MA publish\n");
			
			ros::spinOnce();          
			//legma(-26000,-27000); //climb stairs legs initial
      }
      

		else if(y==57)//9	xtion return home
		{
			bottomm=bottom;topp=top;
			joint_command.request.unit = "rad";
 			joint_command.request.id = 1;
  			joint_command.request.goal_position = bottomm*PI/180;
			joint_command_client.call(joint_command);
			joint_command.request.unit = "rad";
 			joint_command.request.id = 2;
  			joint_command.request.goal_position = topp*PI/180;
			joint_command_client.call(joint_command);
			// head_bottom.data=bottom;
			// head_top.data=top;
			// pub13.publish(head_bottom);
			// pub12.publish(head_top);
			printf("xtion pos_init\n");
			ROS_INFO("bottom:%f,top:%f", bottomm,top);
			ros::spinOnce();
		}
		else if(y==105)//i	xtion turn left
		{	
			bottomm=bottomm+10;
			// head_bottom.data=bottomm;
			// head_top.data=topp;
			// pub13.publish(head_bottom);
			// pub12.publish(head_top);
			joint_command.request.unit = "rad";
 			joint_command.request.id = 1;
  			joint_command.request.goal_position = bottomm*PI/180;
			joint_command_client.call(joint_command);
			joint_command.request.unit = "rad";
 			joint_command.request.id = 2;
  			joint_command.request.goal_position = topp*PI/180;
			joint_command_client.call(joint_command);
			printf("xtion turn left\n");
			ROS_INFO("bottom:%f,top:%f", bottomm,top);
			ros::spinOnce();
		}
		else if(y==112)//p	xtion turn right
		{	
			bottomm=bottomm-10;
			joint_command.request.unit = "rad";
 			joint_command.request.id = 1;
  			joint_command.request.goal_position = bottomm*PI/180;
			joint_command_client.call(joint_command);
			joint_command.request.unit = "rad";
 			joint_command.request.id = 2;
  			joint_command.request.goal_position = topp*PI/180;
			joint_command_client.call(joint_command);
			// head_bottom.data=bottomm;
			// head_top.data=topp;
			// pub13.publish(head_bottom);
			// pub12.publish(head_top);
			printf("xtion turn right\n");
			ROS_INFO("bottom:%f,top:%f", bottomm,top);
			ros::spinOnce();
		}
		else if(y==111)//o	xtion turn up
		{
			topp=topp+10;
			joint_command.request.unit = "rad";
 			joint_command.request.id = 1;
  			joint_command.request.goal_position = bottomm*PI/180;
			joint_command_client.call(joint_command);
			joint_command.request.unit = "rad";
 			joint_command.request.id = 2;
  			joint_command.request.goal_position = topp*PI/180;
			joint_command_client.call(joint_command);
			// head_bottom.data=bottomm;
			// head_top.data=topp;
			// pub13.publish(head_bottom);
			// pub12.publish(head_top);
			printf("xtion turn up\n");
			ROS_INFO("bottom:%f,top:%f", bottomm,top);		
			ros::spinOnce();
		}
		else if(y==108)//l	xtion turn down
		{
			topp=topp-10;
			joint_command.request.unit = "rad";
 			joint_command.request.id = 1;
  			joint_command.request.goal_position = bottomm*PI/180;
			joint_command.request.unit = "rad";
 			joint_command.request.id = 2;
  			joint_command.request.goal_position = topp*PI/180;
			joint_command_client.call(joint_command);
			// head_bottom.data=bottomm;
			// head_top.data=topp;
			// pub13.publish(head_bottom);
			// pub12.publish(head_top);
			printf("xtion turn down\n");
			ROS_INFO("bottom:%f,top:%f", bottomm,top);
			ros::spinOnce();
		}
		

		printf("speed_left = %d , speed_right = %d \n",vv1,vv2);
		loop_rate.sleep();
		
	}

	return 0;
}


/*--robot_MA publish--*/
/*
int r_MA[2];//robot_MA
				
r_MA[0]=-26000;
r_MA[1]=-27000;
for (int i = 0; i < 2; i++)
{
	robot_MA.data.push_back(r_MA[i]);
}
pub3.publish(robot_MA);
printf("robot_MA publish\n");
			
ros::spinOnce();
*/

/*--robot_HO publish--*/
/*
int r_HO[2];//robot_HO
				
r_HO[0]=0;
r_HO[1]=0;

for (int i = 0; i < 2; i++)
{
	robot_HO.data.push_back(r_HO[i]);
}
pub5.publish(robot_HO);
printf("robot_HO publish\n");
ros::spinOnce();
*/

/*--robot_VA publish--*/
/*
int r_VA[2];//robot_VA
				
r_VA[0]=300;
r_VA[1]=300;
for (int i = 0; i < 2; i++)
{
	robot_VA.data.push_back(r_VA[i]);
}
pub6.publish(robot_VA);
printf("robot_VA publish\n");
ros::spinOnce();
*/

/*--lef_HO publish--*/
/*
int l_HO[2];//leg_HO
				
l_HO[0]=0;
l_HO[1]=0;

for (int i = 0; i < 2; i++)
{
	leg_HO.data.push_back(l_HO[i]);
}
pub9.publish(leg_HO);
printf("leg_HO publish\n");
ros::spinOnce();
*/

/*--leg_VA publish--*/
/*
int l_VA[2];//leg_VA
				
l_VA[0]=300;
l_VA[1]=300;
for (int i = 0; i < 2; i++)
{
	leg_VA.data.push_back(l_VA[i]);
}
pub10.publish(leg_VA);
printf("leg_VA publish\n");
ros::spinOnce();
*/	

/*--robot_MR publish--*/
/*
int r_MR[2];//robot_MR
				
r_MR[0]=300;
r_MR[1]=300;
for (int i = 0; i < 2; i++)
{
	robot_MR.data.push_back(r_MR[i]);
}
pub11.publish(robot_MR);
printf("robot_MR publish\n");
ros::spinOnce();
*/


